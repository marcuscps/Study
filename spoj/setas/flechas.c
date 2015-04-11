#include <stdlib.h>
#include <stdio.h>

#define MAXN    8
#define DN      1
#define DS      2
#define DE      4
#define DW      8
#define DNE     16
#define DNW     32
#define DSE     64
#define DSW     128

short m[MAXN][MAXN];
short dirs[4 * MAXN];
short *t;
short *b;
short *l;
short *r;

int instance;
int n;
int ii;
int jj;
void initT() {
	t[0] = DS | DSE;
	for (ii = 0; ii < n - 1; ++ii) {
		t[ii] = DS | DSE | DSW;
	}
	t[n - 1] = DS | DSW;
}

void initB() {
	b[0] = DN | DSE;
	for (ii = 0; ii < n - 1; ++ii) {
		b[ii] = DN | DSE | DSW;
	}
	b[n - 1] = DN | DSW;
}

void initL() {
	l[0] = DE | DSE;
	for (ii = 0; ii < n - 1; ++ii) {
		l[ii] = DE | DNE | DSE;
	}
	l[n - 1] = DW | DSW;
}

void initR() {
	r[0] = DW | DSW;
	for (ii = 0; ii < n - 1; ++ii) {
		r[ii] = DW | DNW | DSW;
	}
	r[n - 1] = DW | DNW;
}

void printCoord(short coord) {
	switch(coord) {
	case DN: printf(" N ");	return;
	case DS: printf(" S "); return;
	case DE:	printf(" E ");	return;
	case DW: printf(" W ");	return;
	case DNE: printf("NE ");	return;
	case DNW: printf("NW ");	return;
	case DSE:	printf("SE ");	return;
	case DSW: printf("SW ");	return;
	default:	printf("?? ");	return;
	}
}

void printResult() {
	printf("   ");
	for (ii = 0; ii < n; ++ii) {
		printCoord(t[ii]);
	}
	printf("\n");
	for (ii = 0; ii < n; ++ii) {
		printCoord(l[ii]);
		for (jj = 0; jj < n; ++jj) {
			printf("% 2d ", m[ii][jj]);
		}
		printCoord(r[ii]);
		printf("\n");
	}
	printf("   ");
	for (ii = 0; ii < n; ++ii) {
		printCoord(b[ii]);
	}
	printf("\n");
}

int zero() {
    t[jj] &= ~DS;
    if (t[jj] == 0) return 1;
    
    b[jj] &= ~DN;
    if (b[jj] == 0) return 1;
    l[ii] &= ~DE;
    if (l[ii] == 0) return 1;
    r[ii] &= ~DW;
    if (r[ii] == 0) return 1;
    if (jj > ii) {
        t[jj - ii - 1] &= ~DSE;
        if (t[jj - ii - 1] == 0) return 1;
        r[n + ii - jj] &= ~DNW;
        if (r[n + ii - jj] == 0) return 1;
    } else if (jj != ii) {
        b[n + ii - jj] &= ~DNW;
        if (b[n + ii - jj] == 0) return 1;
        l[ii + jj - 1] &= ~DSE;
        if (l[ii + jj - 1] == 0) return 1;
    }
    
    if (jj + 1 < n - ii) {
        t[ii + jj + 1] &= ~DSW;
        if (t[ii + jj + 1] == 0) return 1;
        l[ii - jj + 1] &= ~DNE;
        if (l[ii + jj + 1] == 0) return 1;
    } else if (jj + 1 != n - ii) {
        b[ii + jj - n] &= ~DNE;
        if (b[ii + jj - n] == 0) return 1;
        r[ii + jj - n] &= ~DNE;
        if (b[ii + jj - n] == 0) return 1;
    }
    
    return 0;
}

int checkZero() {
	for (ii = 0; ii < n; ++ii) {
		for (jj = 0; jj < n; ++jj) {
			scanf("%d", &m[ii][jj]);
			if (m[ii][jj] == 0) {
	                	if (zero()) {
		                    return 1;
        		        }
			}
		}
	}
}

int checkValidTop(int kk) {
    int it;
    short actionBackup[MAXN];
    int backup;
    int recursive = 1;
    int col;
    
    printf("%d\n", kk);
    
    if (dirs + kk >= l) return 1;
    if (dirs[kk] == 0) return 1;    
    
    if (dirs[kk] & DS != 0) {
        backup = dirs[kk];
        dirs[kk] = DS;
        col = dirs + kk - t;
        for (it = 0; it < n; ++it) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        if (dirs + kk + 1 < l) {
            recursive = checkValidTop(kk + 1);
        } else {
            recursive = checkValidLeft(kk + 1);
        }
        for (it = 0; it < n; ++it) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DSE != 0) {
        backup = dirs[kk];
        dirs[kk] = DSE;
        col = dirs + kk - t + 1;
        for (it = 0; it < n && col < n ; ++it, ++col) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        if (dirs + kk + 1 < l) {
            recursive = checkValidTop(kk + 1);
        } else {
            recursive = checkValidLeft(kk + 1);
        }
        col = dirs + kk - t + 1;
        for (it = 0; it < n && col < n ; ++it, ++col) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DSW != 0) {
        backup = dirs[kk];
        dirs[kk] = DSW;
        col = dirs + kk - t - 1;
        for (it = 0; it < n && col >= 0 ; ++it, --col) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        if (dirs + kk + 1 < l) {
            recursive = checkValidTop(kk + 1);
        } else {
            recursive = checkValidLeft(kk + 1);
        }
        col = dirs + kk - t - 1;
        for (it = 0; it < n && col >= 0 ; ++it, --col) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    return 1;
}

int checkValidLeft(int kk) {
    int it;
    short actionBackup[MAXN];
    int backup;
    int recursive = 1;
    int lin;
    
    printf("%d\n", kk);
    if (dirs + kk >= r) return 1;
    if (dirs[kk] == 0) return 1;    
    
    if (dirs[kk] & DE != 0) {
        backup = dirs[kk];
        dirs[kk] = DE;
        lin = dirs + kk - l;
        for (it = 0; it < n; ++it) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < r) {
            recursive = checkValidLeft(kk + 1);
        } else {
            recursive = checkValidRight(kk + 1);
        }
        for (it = 0; it < n; ++it) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DSE != 0) {
        backup = dirs[kk];
        dirs[kk] = DSE;
        lin = dirs + kk - l + 1;
        for (it = 0; it < n && lin < n ; ++it, ++lin) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < r) {
            recursive = checkValidLeft(kk + 1);
        } else {
            recursive = checkValidRight(kk + 1);
        }
        lin = dirs + kk - l + 1;
        for (it = 0; it < n && lin < n ; ++it, ++lin) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DNE != 0) {
        backup = dirs[kk];
        dirs[kk] = DNE;
        lin = dirs + kk - l - 1;
        for (it = 0; it < n && lin >= 0 ; ++it, --lin) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < r) {
            recursive = checkValidLeft(kk + 1);
        } else {
            recursive = checkValidRight(kk + 1);
        }
        lin = dirs + kk - l - 1;
        for (it = 0; it < n && lin >= 0 ; ++it, --lin) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    return 1;
}

int checkValidRight(int kk) {
    int it;
    short actionBackup[MAXN];
    int backup;
    int recursive = 1;
    int lin;
    
    printf("%d\n", kk);
    if (dirs + kk >= b) return 1;
    if (dirs[kk] == 0) return 1;    
    
    if (dirs[kk] & DW != 0) {
        backup = dirs[kk];
        dirs[kk] = DW;
        lin = dirs + kk - r;
        for (it = n - 1; it >= 0; --it) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < b) {
            recursive = checkValidRight(kk + 1);
        } else {
            recursive = checkValidBottom(kk + 1);
        }
        for (it = n - 1; it >= 0; --it) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DSW != 0) {
        backup = dirs[kk];
        dirs[kk] = DSW;
        lin = dirs + kk - r + 1;
        for (it = n - 1; it >= 0 && lin < n ; --it, ++lin) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < b) {
            recursive = checkValidRight(kk + 1);
        } else {
            recursive = checkValidBottom(kk + 1);
        }
        lin = dirs + kk - r + 1;
        for (it = n - 1; it >= 0 && lin < n ; --it, ++lin) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DNW != 0) {
        backup = dirs[kk];
        dirs[kk] = DNE;
        lin = dirs + kk - r - 1;
        for (it = n - 1; it >= 0 && lin >= 0 ; --it, --lin) {
            actionBackup[it] = m[lin][it];
            --m[lin][it];
        }
        if (dirs + kk + 1 < b) {
            recursive = checkValidRight(kk + 1);
        } else {
            recursive = checkValidBottom(kk + 1);
        }
        lin = dirs + kk - r - 1;
        for (it = n - 1; it >= 0 && lin >= 0 ; --it, --lin) {
            m[lin][it] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    return 1;
}

int checkValidBottom(int kk) {
    int it;
    short actionBackup[MAXN];
    int backup;
    int recursive = 1;
    int col;
    
    printf("%d\n", kk);
    if (kk >= (4 * n)) return 0;
    if (dirs[kk] == 0) return 1;    
    
    if (dirs[kk] & DN != 0) {
        backup = dirs[kk];
        dirs[kk] = DN;
        col = dirs + kk - b;
        for (it = n - 1; it >= 0; --it) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        recursive = checkValidBottom(kk + 1);
        for (it = n - 1; it >= 0; --it) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DNE != 0) {
        backup = dirs[kk];
        dirs[kk] = DNE;
        col = dirs + kk - b + 1;
        for (it = n - 1; it >= 0 && col < n ; --it, ++col) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        recursive = checkValidBottom(kk + 1);
        col = dirs + kk - b + 1;
        for (it = n - 1; it >= 0 && col < n ; --it, ++col) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    if (dirs[kk] & DNW != 0) {
        backup = dirs[kk];
        dirs[kk] = DNW;
        col = dirs + kk - b - 1;
        for (it = n - 1; it >= 0 && col >= 0 ; --it, --col) {
            actionBackup[it] = m[it][col];
            --m[it][col];
        }
        recursive = checkValidBottom(kk + 1);
        col = dirs + kk - b - 1;
        for (it = n - 1; it >= 0 && col >= 0 ; --it, --col) {
            m[it][col] = actionBackup[it];
        }
        dirs[kk] = backup;
        if (recursive == 0) return 0;
    }
    return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	int kk;
	int recursive;
	instance = 1;
	while (1) {
		scanf("%d", &n);
		if (n == 0) break;
	        t = dirs;
	        l = t + n;
	        r = l + n;
	        b = r + n;
        
		initT();
		initB();
		initL();
		initR();

		if (checkZero()) {
			printf("Instancia %d:\nsem solucao\n\n");
	        } else {
			if (checkValidTop(kk)) {
				printf("Instancia %d:\nsem solucao\n\n");
			} else {
				printResult();
				printf("\n");
			}
		}
	}
	return 0;
}

