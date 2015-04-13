#include <iostream>
#include <string>
#include <map>
#include <list>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

//================================================================================================
struct Author;
typedef vector<Author *>      VAuthor;
typedef list<Author *>        LAuthor;
typedef map<string, Author *> MAuthor;

//================================================================================================
struct Author {
    string name;
    LAuthor links;
    Author *parent;
    int d;
    
    Author(string name) :
		name(name), parent(NULL), d(numeric_limits<int>::max())
	{
    }
    
    void addLink(Author *author) {
        links.push_back(author);
    }
};

//================================================================================================
struct CompareAuthor {
    bool operator()(Author *t1, Author *t2) const {
       return t1->d < t2->d;
    }
};


//================================================================================================
int main() {
    int t, p, n;
    const string erdos = "Erdos, P.";
    
    cin >> t;
    while (t--) {
        MAuthor authors;
        LAuthor findMe;
        string article;
        Author *source;

        cin >> p >> n;
        getline(std::cin, article);
        for (int ii = 0; ii < p; ++ii) {
            getline(std::cin, article);
            int sep = article.find(":");
            article = article.substr(0, sep + 1);
			article[article.size() - 1] = ',';
            
			// Parse authors of the article
            LAuthor artAuthors;
            int s = 0, e;
            while((e = article.find(",", s)) != -1) {
				// Find the comma between last name and initial(s).
                e = article.find(",", e + 1);
				// Get the last name + initials.
				// Beware second param is a length, not an index.
                string name = article.substr(s, e - s);
				// Skip the comma and space following the author.
				s = e + 2;
				
				// Create new authors (unique in the scenario)
				// Recover it if not new.
                MAuthor::iterator it = authors.find(name);
                Author *author = NULL;
                if (it != authors.end()) {
                    author = it->second;
                } else {
                    author = new Author(name);
                    authors[name] = author;
                    if (erdos == author->name) {
                        source = author;
                    }
                }
				// Keep the article authors in a list to allow linking them ahead.
                artAuthors.push_back(author);
            }
            
			// Link author of the article.
			for (LAuthor::iterator it1 = artAuthors.begin(); it1 != artAuthors.end(); ++it1) {
                LAuthor::iterator it2 = it1;
				for (++it2; it2 != artAuthors.end(); ++it2) {
					(*it1)->addLink(*it2);
					(*it2)->addLink(*it1);
                }
            }
        }

		// Dijkistra using min binary heap
		VAuthor queue;
		queue.reserve(authors.size());
        source->d = 0;
        queue.push_back(source);
        while (queue.empty() == false) {
			// Pop the vertice with the minimum key
			Author *current = queue.back();
			queue.pop_back();
			pop_heap(queue.begin(), queue.end(), CompareAuthor());
			
			// Relax edges to all linked authors
            for (LAuthor::iterator it = current->links.begin(); it != current->links.end(); ++it) {
				Author *target = *it;
                if (current->d + 1 < target->d) {
					if (target->d == numeric_limits<int>::max()) {
						target->d = current->d + 1;
	                    queue.push_back(target);
						push_heap(queue.begin(), queue.end(), CompareAuthor());
					} else {
						target->d = current->d + 1;
					}
				}
            }
			// Update the queue. This is O(n) but can be improved to O(log2 N).
            make_heap(queue.begin(), queue.end(), CompareAuthor());
        }
		
		// Read wanted authors
		cout << "Scenario " << t + 1 << endl;
		string name;
        getline(std::cin, name);
		while (name.size() > 0) {
			// Recover the Author from the scenario map.
			MAuthor::iterator it = authors.find(name);
			if (it != authors.end()) {
				Author *wanted = it->second;
				cout << wanted->name << " ";
				if (wanted->d == numeric_limits<int>::max()) {
					// Unvisited vertices.
					cout << "infinity" << endl;
				} else {
					cout << wanted->d << endl;
				}
			}
			getline(std::cin, name);
		}

		// Release resources.
        for (MAuthor::iterator it = authors.begin(); it != authors.end(); ++it) {
            delete it->second;
        }
    }
    
    return 0;
}

