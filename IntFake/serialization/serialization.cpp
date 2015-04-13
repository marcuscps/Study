#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>

#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)		printf("## " __VA_ARGS__)
	#define ODEBUG(...)		std::cout << "## " << __VA_ARGS__
	#define EDEBUG(...)		std::cerr << "## " << __VA_ARGS__

	#define MDEBUG(...)		printf(__VA_ARGS__)
	#define OMDEBUG(...)	std::cout << __VA_ARGS__
	#define EMDEBUG(...)	std::cerr << __VA_ARGS__
#else
	#define DEBUG(...)
	#define ODEBUG(...)
	#define EDEBUG(...)

	#define MDEBUG(...)
	#define OMDEBUG(...)
	#define EMDEBUG(...)
#endif

using namespace std;

typedef std::vector<std::string> vec;

std::string serialize_int(int value) {
  char* char_value = (char*)&value;
  return std::string(char_value, 4);
}

std::string serialize(std::vector<std::string> input) {
    if (input.size() == 0) {
        return "";
    }    
    
    stringstream acc;
    for (vec::const_iterator it = input.begin(); it != input.end(); ++it) {
        std::string str = *it;
        size_t len = str.size();
        acc << len << " " << str;
    }
    
    return acc.str();
}

std::vector<std::string> de_serialize(std::string input) {
	ODEBUG("Deserializing: \"" << input << "\"" << endl);
	vec result;    
    std::istringstream sstr(input);

	int length;

    while (sstr >> length) {
		sstr.ignore(1, ' ');

        char* buffer = new char[length];
        sstr.read(buffer, length);
		string str(buffer, length);

		ODEBUG("Read: " << length << ": \"" << str << "\"" << endl);
        
        result.push_back(std::string(buffer, length));
        delete buffer;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	vector<string> input;
	input.push_back("Test string 1");
	input.push_back("Test longer string 2");
	input.push_back("Test much longer string 3");

	string serialized = serialize(input);
	cout << "\"" << serialized << "\"" << endl;

	vector<string> result = de_serialize(serialized);

	copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}

