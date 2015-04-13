#include <iostream>
#include <cstdio>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	const string cards[] = {
		"2", "3", "4", "5", "6", "7", "8", "9", "10",
		"Jack", "Queen", "King", "Ace"
	};
	const string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
 
    int t, n, s;
    int shuffle[100][53];
    int adeck1[53], adeck2[53];
    int *deck1, *deck2, *result;
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int ii = 0; ii < n; ++ii) {
            for (int si = 1; si <= 52; ++si) {
                scanf("%d", &shuffle[ii][si]);
            }
        }
         
        for (int ii = 0; ii < n; ++ii) {
			DEBUG("Shuffle %d:\n", ii);
            for (int si = 1; si <= 52; ++si) {
				DEBUG("%d ", shuffle[ii][si]);
			}
			DEBUG("\n");
		}
		
        deck1 = adeck1;
        deck2 = adeck2;
        result = deck1;

		DEBUG("Initializing deck...\n");
        for (int ii = 1; ii <= 52; ++ii) {
            deck1[ii] = ii;            
        }
        
		DEBUG("Initial deck:\n");
        for (int ii = 1; ii <= 52; ++ii) {
            DEBUG("%d ", deck1[ii]);
		}
		DEBUG("\n");
		
        while (true) {
            if (scanf("%d", &s) != 1) {
                break;
            }
            
			DEBUG("Applying shuffle %d..\n", s);
            int *sh = shuffle[s - 1];
            for (int ii = 1; ii <= 52; ++ii) {
                DEBUG("deck2[%d] = deck1[%d]\n", ii, sh[ii]);
                deck2[ii] = deck1[sh[ii]];
            }
            
            result = deck2;
            swap(deck1, deck2);
        }        
       
        for (int ii = 1; ii <= 52; ++ii) {
            printf("%s of %s\n", cards[((result[ii] - 1) % 13)].c_str(),
					suits[((result[ii] - 1) / 13)].c_str());
        }
        printf("\n");
    }
    
    return 0;
}
