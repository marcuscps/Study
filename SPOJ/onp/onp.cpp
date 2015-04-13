#include <cstdio>

using namespace std;

int main() {
	char stack[200];
	int stackTop = 0;

	char inputBuf[400];
	char outputBuf[400];

	int t;
	scanf("%d\n", &t);
	while (t--) {
		int in = 0;
		int out = 0;
		fgets(inputBuf, sizeof(inputBuf), stdin);
		while (inputBuf[in] != 0) {
			char c = inputBuf[in++];
			switch (c) {
			case '^':
			case '/':
			case '*':
			case '-':
			case '+':
				stack[stackTop++] = c;
				break;
			case '(':
				break;
			case ')':
				outputBuf[out++] = stack[--stackTop];
				break;
			case '\n':
				break;
			default:
				outputBuf[out++] = c;
				break;
			}
		}
		while (stackTop > 0) {
			outputBuf[out++] = stack[--stackTop];
		}
		outputBuf[out] = 0;
		printf("%s\n", outputBuf);
	}
}
