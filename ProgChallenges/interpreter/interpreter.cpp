#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

//#define DEBUG(...) printf( __VA_ARGS__ )
#define DEBUG(...)

unsigned int pc;
unsigned int ram[1000];
unsigned int regs[10];
unsigned int cnt;


bool gotoOp(unsigned int d, unsigned int s) {
	DEBUG("  GOTO %u IF %u != 0\n", regs[d], regs[s]);
	if (regs[s] != 0) {
		pc = regs[d];
	}
	return false;
}

bool haltOp(unsigned int op1, unsigned int op2) {
	DEBUG("  HALT\n");
	printf("%u\n", cnt);
	return true;
}

bool setRegOp(unsigned int d, unsigned int n) {
	regs[d] = n % 1000;
	DEBUG("  REG %u = %u\n", d, regs[d]);
	return false;
}

bool addRegOp(unsigned int d, unsigned int n) {
	regs[d] = (regs[d] + n) % 1000;
	DEBUG("  REG %u += %u  -  result: %u\n", d, n, regs[d]);
	return false;
}

bool mulRegOp(unsigned int d, unsigned int n) {
	regs[d] = (regs[d] * n) % 1000;
	DEBUG("  REG %u *= %u  -  result: %u\n", d, n, regs[d]);
	return false;
}

bool setRegRegOp(unsigned int d, unsigned int s) {
	regs[d] = regs[s];
	DEBUG("  REG %u = REG %u  -  result: %u\n", d, s, regs[d]);
	return false;
}

bool addRegRegOp(unsigned int d, unsigned int s) {
	regs[d] = (regs[d] + regs[s]) % 1000;
	DEBUG("  REG %u += REG %u  -  result: %u\n", d, s, regs[d]);
	return false;
}

bool mulRegRegOp(unsigned int d, unsigned int s) {
	regs[d] = (regs[d] * regs[s]) % 1000;
	DEBUG("  REG %u *= REG %u  -  result: %u\n", d, s, regs[d]);
	return false;
}

bool setRegRamOp(unsigned int d, unsigned int a) {
	regs[d] = ram[regs[a] % 1000] % 1000;
	DEBUG("  REG %u = RAM[ REG %u ]  -  result: %u\n", d, a, regs[d]);
	return false;
}

bool setRamRegOp(unsigned int s, unsigned int a) {
	ram[regs[a] % 1000] = regs[s] % 1000;
	DEBUG("  RAM [ REG %u ] = REG %u  -  result: %u\n", a, s, ram[regs[a] % 1000]);
	return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	unsigned int t;
	unsigned int opCode, op1, op2;
	bool halted, first = true;

	scanf("%u", &t);
	while (t--) {
		for(pc = 0; scanf("%u\n", &opCode) == 1; ++pc) {
			ram[pc] = opCode;
			DEBUG("  RAM[ %03u ] = %u\n", pc, opCode);
		}

		if (first == false) {
			printf("\n");
		}

		first = false;
		pc = 0;
		cnt = 0;
		halted = false;

		while (halted == false) {
			opCode = ram[pc];
			op2 = opCode % 10;
			opCode /= 10;
			op1 = opCode % 10;
			opCode /= 10;

			DEBUG("Decoded %u -- %u %u %u\n", pc, opCode, op1, op2);
			++cnt;
			++pc;

			switch (opCode) {
			case 0: halted =      gotoOp(op1, op2); break;
			case 1: halted =      haltOp(op1, op2); break;
			case 2: halted =    setRegOp(op1, op2); break;
			case 3: halted =    addRegOp(op1, op2); break;
			case 4: halted =    mulRegOp(op1, op2); break;
			case 5: halted = setRegRegOp(op1, op2); break;
			case 6: halted = addRegRegOp(op1, op2); break;
			case 7: halted = mulRegRegOp(op1, op2); break;
			case 8: halted = setRegRamOp(op1, op2); break;
			case 9: halted = setRamRegOp(op1, op2); break;
			default:
					DEBUG("Invalid opcode: %d\n", opCode);
					halted = true;
					break;
			}
		}
	}

	return 0;
}
