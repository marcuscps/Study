std::string get_string(unsigned int position);
bool has_word(std::string word);

using namespace std;

bool has_word(std::string word) {
	if (word == "") return false;
	
	int leftI = 0;
	int rightI = 0;
	int interv = 1;
	
	do {
		string s = get_string(rightI);
		if (s == "") {
			right = (right + left) / 2;
		} else {
			int q = word.compare(s);
			if (q == 0) {
				return true;
			} else if (q < 0) {
				interv *= interv;
				leftl = rightl;
				rightl = interv;
			} else {
				interv = interv / 2;
				right = left + interv;
			}
		}
	} while (leftl < rightl);
	
	return false;	
}

