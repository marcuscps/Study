#include <iostream>
#include <cstdio>

//#define DEBUG_ON
#ifdef DEBUG_ON
	#define DEBUG(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
#endif

using namespace std;

typedef struct Cube {
	int cube;		// Cube #
	int faceUp;		// Which face is UP
	int top;		// Top collor
	int bot;		// Bottom collor

	int height;		// Height in the tower
	Cube *bottom;	// Cube below this one

	Cube(int cube, int faceUp, int top, int bot) : cube(cube), faceUp(faceUp), top(top), bot(bot), height(1), bottom(NULL) {
		DEBUG("  New cube: %d, %d, %d, %d\n", cube, faceUp, top, bot);
	}

} Cube;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int caseN = 1;
	int n;
	Cube *tower[101];
	Cube *cubes[500][7];
	int fr, ba, le, ri, to, bo; 

	while (true) {
		scanf("%d", &n);
		if (n == 0) break;

		DEBUG("Initializing tower\n");
		for (int ii = 0; ii < 101; ++ii) tower[ii] = NULL;

		for (int ii = 0; ii < n; ++ii) {
			int cubeN = ii + 1;
			int k = 0;
			scanf("%d %d %d %d %d %d", &fr, &ba, &le, &ri, &to, &bo);
			DEBUG("Reading cube: %d  -  %d %d %d %d %d %d\n", cubeN, fr, ba, le, ri, to, bo);
			cubes[ii][k++] = new Cube(cubeN, 0, fr, ba);
			if (fr != ba) cubes[ii][k++] = new Cube(cubeN, 1, ba, fr);
			cubes[ii][k++] = new Cube(cubeN, 2, le, ri);
			if (le != ri) cubes[ii][k++] = new Cube(cubeN, 3, ri, le);
			cubes[ii][k++] = new Cube(cubeN, 4, to, bo);
			if (to != bo) cubes[ii][k++] = new Cube(cubeN, 5, bo, to);
			cubes[ii][k] = NULL;
		}

		Cube *maxCube = NULL;
		int maxHeight = 0;
		for (int ii = n - 1; ii >= 0; --ii) {
			DEBUG("Testing cube at level %d\n", ii + 1);
			Cube **cubeLine = cubes[ii];
			Cube *toAdd[7];
			int k = 0;
			for (int jj = 0; cubeLine[jj] != NULL; ++jj) {
				Cube *cube = cubeLine[jj];
				cube->height = 1;
				Cube *bottom = tower[cube->bot];

				if (bottom != NULL) {
					cube->height += bottom->height;
					cube->bottom = bottom;
				}
				toAdd[k++] = cube;
			}
			for (--k; k >= 0; --k) {
				Cube *cube = toAdd[k];
				Cube *towerTop = tower[cube->top];

				if ((towerTop == NULL) || (cube->height > towerTop->height)) {
					tower[cube->top] = cube;
					DEBUG("Cube added to tower top at pos %03d: %d %d  (%d)  -  H: %d\n",
							cube->top, cube->top, cube->bot, cube->faceUp, cube->height);
				}
				if (cube->height > maxHeight) {
					maxHeight = cube->height;
					maxCube = cube;
				}
			}
		}

		printf("Case #%d\n", caseN++);
		printf("%d\n", maxHeight);
		while (maxCube != NULL) {
			printf("%d ", maxCube->cube);
			switch (maxCube->faceUp) {
				case 0: printf("front\n");	break;
				case 1: printf("back\n");	break;
				case 2: printf("left\n");	break;
				case 3: printf("right\n");	break;
				case 4: printf("top\n");	break;
				case 5: printf("bottom\n"); break;
			}
			maxCube = maxCube->bottom;
		}
		printf("\n");

		for (int ii = 0; ii < n; ++ii) {
			Cube **cubeLine = cubes[ii];
			for (int jj = 0; cubeLine[jj] != NULL; ++jj) {
				delete cubeLine[jj];
			}
		}
	}

    return 0;
}
