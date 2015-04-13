#include <iostream>
#include <cstdio>

#include <map>
#include <list>
#include <memory>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG_ST(x)		x
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
#else
	#define DEBUG_ST(x)
	#define DEBUG(...)
	#define ODEBUG(...)
	#define MDEBUG(...)
	#define OMDEBUG(...)
#endif

/**
 * Cache template.
 *
 * It is a generic LRU (Least Recentrly Used) Cache implementation in which
 * objects are accessed by key, just like a hash map/table does.
 *
 * When the number of elements cached exceed the capacity, elements will be
 * released from the cache in order of the least recently used element.
 * In other words, the element destroyed would be the one which has not been
 * accessed for the longest time.
 *
 * It is necessary to pass a ResourceManager instance to the constructor,
 * together with the desired capcity. The Resource Manager would be responsible
 * for creating new instances on cache misses.
 *
 * Runtime and space efficiency info:
 *		Seeking:				O(1)
 *		Overflow item deletion: O(1)
 *		Space:					O(n), where n is the number of items in the cache.
 */
template<class key_type, class obj_type>
class Cache {
public:

	typedef std::shared_ptr<obj_type> obj_ref;

	/**
	 * Resource Manager base class.
	 * Users need to provide a concrete implementation to the Cache constructor.
	 */
	class ResourceManager {
	public:
		virtual ~ResourceManager() { }
		virtual obj_type & create( key_type key ) = 0;
	};

	/**
	 * @fn Cache(ResourceManager &manager, size_t capacity)
	 * @brief Constructor
	 *
	 * @param	[in] manager : Reference to the Resource Manager instance.
	 * @param	[in] capacity : The number of elements to keep in cache.
	 */
	Cache( ResourceManager &manager, size_t capacity ) :
		manager(manager),
		max_capacity(capacity)
	{
	}

	/**
	 * @fn ~Cache()
	 * @brief Destructor
	 */
	~Cache() {
	}

	/**
	 * @fn size_t capacity()
	 * @brief Return the maximum number of items to be cached.
	 *
	 * @return the maximum number of items to be cached.
	 */
	size_t capacity() const {
		return max_capacity;
	}

	/**
	 * @fn void set_capacity( size_t capacity )
	 * @brief Set the maximum capacity. It may cause elements to be removed from cache.
	 *
	 * @param	[IN] capacity : the new capacity.
	 */
	void set_capacity( size_t capacity ) {
		max_capacity = capacity;
		check_capacity();
	}

	/**
	 * @fn size_t size()
	 * @brief Return the number of cached items.
	 *
	 * @return the number of cached items.
	 */
	size_t size() const {
		return obj_map.size();
	}

	/**
	 * @fn obj_ref get(key_type key)
	 * @brief Get an object associated with the given key. It may be created through
	 * the Resource Manager.
	 *
	 * @param	[IN] key : the key to find the element.
	 * @return	Object reference to the desired element (it may be created).
	 */
	obj_ref get( key_type key ) {
		auto it = obj_map.find(key);
		if (it != obj_map.end()) {
			typename LRUList::iterator lit = it->second;
			Item item = *lit;
			lru_list.erase(lit);
			lru_list.push_front(item);
			lit = lru_list.begin();
			obj_map[key] = lit;
			return item.ref;
		}

		obj_ref ref(&manager.create(key));
		lru_list.push_front(Item(key, ref));
		obj_map[key] = lru_list.begin();

		check_capacity();

		return ref;
	}

	/**
	 * @fn obj_ref remove(key_type key)
	 * @brief Force remove from the cache the element with a given key.
	 *
	 * @param	[IN] key : the key to find the element.
	 * @return	Object reference to the removed element, nullptr if not found.
	 */
	obj_ref remove( key_type key ) {
		auto it = obj_map.find(key);
		if (it == obj_map.end()) {
			ODEBUG("Key \"" << key << "\" does not reference a valid object." << std::endl);
			return nullptr;
		}

		typename LRUList::iterator lit = it->second;
		Item item = *lit;
		lru_list.erase(lit);
		obj_map.erase(item.key);
	
		return item.ref;
	}

	/**
	 * @fn friend std::ostream& operator<<(std::ostream& o, const Cache &p)
	 * @brief Debugging output stream wrapper.
	 */
	friend std::ostream& operator<<( std::ostream& o, const Cache &p ) {
		o << "ratio = " << p.size() << "/" << p.capacity() << ": HEAD";
		for (typename Cache<key_type, obj_type>::LRUList::const_iterator it = p.lru_list.begin(); it != p.lru_list.end(); ++it) {
			o << " -> " << (*it).ref;
		}
		return o;
	}

private:

	Cache( const Cache& other ); // non construction-copyable
	Cache& operator=( const Cache& ); // non copyable
	Cache( Cache&& ); // non movable

	/**
	 * Internal object used to keep the key in the linked list, instead of simply
	 * keeping the object.
	 */
	struct Item {
		key_type key;
		obj_ref ref;

		/**
		 * @fn Item(key_type key, obj_ref ref)
		 * @brief Constructor
		 *
		 * @param	[IN] key : The object key
		 * @param	[IN] ref : The object reference
		 */
		Item( key_type key, obj_ref ref ) :
			key(key),
			ref(ref)
		{
		}
	};

	/*
	 * Useful type definitions.
	 */
	typedef std::list<Item> LRUList;
	typedef std::map<key_type, typename LRUList::iterator> ObjMap;

	/**
	 * @fn void check_capacity()
	 * @brief Ensure the cache is not holding more objects than it should.
	 */
	void check_capacity() {
		while (obj_map.size() > max_capacity) {
			typename LRUList::reverse_iterator it = lru_list.rbegin();
			Item item = *it;
			lru_list.erase(--(it.base()));
			obj_map.erase(item.key);
		}
	}

	// The resource Manager
	ResourceManager &manager;
	// Capacity
	size_t max_capacity;

	// Map to hold references to linked list nodes.
	ObjMap  obj_map;
	// Linked list to hold elements in order of access. Last is the older.
	LRUList lru_list;
	
};


/**
 * Example object (to be stored in the cache.
 */
class MyObj {
public:
	MyObj( std::string name ) : name(name) { std::cout << "MyObj created: " << name << std::endl; }
	~MyObj() { std::cout << "MyObj destroyed: " << name << std::endl; }
	friend std::ostream& operator<<( std::ostream& o, const MyObj* p ) { o << p->name; return o; }

private:
	std::string name;

};


/**
 * Resource Manager to handle MyObj creation.
 */
class MyObjManager : public Cache<std::string, MyObj>::ResourceManager {
public:
	MyObj & create( std::string key ) { return *(new MyObj(key)); }
};


/**
 * Testing program.
 */
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

	MyObjManager manager;
	Cache<std::string, MyObj> cache(manager, 5);

	std::string cmd;
	while (true) {
		std::cin >> cmd;
		if (cmd == "q") {
			ODEBUG("Quiting..." << std::endl);
			break;
		} else if (cmd == "c") {
			int capacity;
			std::cin >> capacity;
			ODEBUG("Setting capacity: " << capacity << std::endl);
			cache.set_capacity(capacity);
		} else if (cmd == "g") {
			std::string key;
			std::cin >> key;
			ODEBUG("Getting object with key \"" << key << "\"" << std::endl);
			auto obj = cache.get(key);
			std::cout << "Got \"" << obj << "\"  -  List: " << cache << std::endl;
		} else if (cmd == "r" ) {
			std::string key;
			std::cin >> key;
			ODEBUG("Removing object with key \"" << key << "\"" << std::endl);
			auto obj = cache.remove(key);
			if (obj == nullptr) {
				std::cout << "Can NOT remove! INVALID OBJECT  -  List: " << cache << std::endl;
			} else {
				std::cout << "Removed \"" << obj << "\"  -  List: " << cache << std::endl;
			}
		}
	}

	return 0;
}

