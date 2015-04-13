#include <iostream>
#include <cstdio>
#include <map>
#include <list>

#ifndef ONLINE_JUDGE
	#define DEBUG_ON
#endif
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

using namespace std;

class Parking {
private:

	struct Info {
		bool vacant;
		size_t size;

		Info(bool vacant, size_t size) : vacant(vacant), size(size) {
		}
	};

	typedef list<Info> InfoList;

private:
	size_t size;
	size_t available;
	unsigned int balance;

	InfoList infos;
	map<int, InfoList::iterator> location;

public:
	Parking(size_t size) : size(size), available(size), balance(0) {
		infos.push_back(Info(true, size));
	}

	unsigned int get_balance() {
		return balance;
	}

	bool add_vehicle(int id, size_t length) {
		ODEBUG("Vehicle arrived: " << id << " - len = " << length << endl);

		if (length > available) {
			ODEBUG("  Not enough spots available. Required " << length << " but have only " << available << " spots." << endl);
			return false;
		}

		for (InfoList::iterator it = infos.begin(); it != infos.end(); ++it) {
			Info &info = *it;
			if (info.vacant == true && info.size >= length) {
				InfoList::iterator space = it;
				if (info.size > length) {
					space = infos.insert(it, Info(false, length));
					info.size -= length;
				}

				space->vacant = false;
				location[id] = space;

				available -= length;
				balance += 10;
				ODEBUG("  Parked at position successfully!  -  Spots free = " << available << "  -  balance = " << balance << endl);
				return true;
			}
		}

		ODEBUG("  Parking spot not available!" << endl);
		return false;
	}

	bool remove_vehicle(int id) {
		auto it = location.find(id);
		if (it == location.end()) {
			ODEBUG("Vehicle not parked here. ERROR?" << endl);
			return false;
		}

		InfoList::iterator lit = it->second;
		Info &info = *lit;
		location.erase(it);

		ODEBUG("Vehicle departed: " << id << "  -  length: " << info.size);
		info.vacant = true;
		available += info.size;

		InfoList::iterator after  = next(lit);
		if (after != infos.end() && after->vacant == true) {
			info.size += after->size;
			infos.erase(after);
			OMDEBUG(" - Merged after");
		}

		InfoList::iterator before = prev(lit);
		if (before != infos.end() && before->vacant == true) {
			info.size += before->size;
			infos.erase(before);
			OMDEBUG(" - Merged before");
		}

		OMDEBUG("  -  Vacant region = " << info.size << "  -  Available = " << available << endl);
		return true;
	}

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	char e;
	size_t c, n, len;
	int id;

	while (cin >> c >> n) {
		ODEBUG("Parking lot size: " << c << " - Events: " << n << endl); 
		Parking pk(c);

		for (size_t ii = 0; ii < n; ++ii) {
			cin >> e;
			switch (e) {
			case 'C': cin >> id >> len; pk.add_vehicle(id, len); break;
			case 'S': cin >> id; pk.remove_vehicle(id); break;
			default:  ODEBUG("Invalid command." << endl);
			}
		}

		cout << pk.get_balance() << endl;
	}

    return 0;
}

