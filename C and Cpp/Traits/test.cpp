#include <iostream>

using namespace std;


//==================================================================================================
template< typename T > 
struct supports_optimised_implementation {
	static const bool value = false;
};


//==================================================================================================
template< bool b >
struct algorithm_selector { 
	template< typename T >
	static inline void implementation( T& object ) { 
		//implement the alorithm operating on "object" here 
		cout << "default implementation" << endl;
	} 
};


template<> struct algorithm_selector< true > {
	template< typename T>
	static inline void implementation( T& object ) {
		object.optimised_implementation();
	}
};


//==================================================================================================
template< typename T >
void algorithm( T& object ) {
	algorithm_selector< supports_optimised_implementation< T >::value >::implementation(object);
}


//==================================================================================================
class ObjectA {
};


//==================================================================================================
class ObjectB {
	public:
		inline void optimised_implementation() {
			cout << "ObjectB::optimised_implementation" << endl;
		}
};

template<> struct supports_optimised_implementation< ObjectB > {
	static const bool value = true;
};


//==================================================================================================
int main(int argc, char* argv[]) { 
	ObjectA a; 
	algorithm( a ); 
	// calls default implementation 
	ObjectB b; 
	algorithm( b ); 
	// calls 
	// ObjectB::optimised_implementation(); 
	return 0; 
}
