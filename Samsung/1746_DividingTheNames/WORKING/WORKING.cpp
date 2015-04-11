#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
 
using namespace std;
 
int children[4000];
char ss[20];
int n, cnt, sta;
int nex[4000][26];
int left_sibling[4000]; // left sibling
int rightmost_child[4000]; // last child
int dp[4000][101];
 
void create(int node, int idx) {
  nex[node][idx] = cnt;
  children[cnt] = 0;
  left_sibling[cnt] = -1;
  rightmost_child[cnt] = -1;
 
  if (rightmost_child[node] != -1) left_sibling[cnt] = rightmost_child[node];
  rightmost_child[node] = cnt;
 
  cout << "## node " << node << " " << rightmost_child[node] << endl;
  cnt++;
}
 
void add(char* str) {
  int node = 0;
 
  for (int i = 0; str[i] != '\0'; i++) {
    if (nex[node][str[i]-'A'] == -1) {
      create(node, str[i]-'A');
    }
   
    node = nex[node][str[i]-'A'];
    children[node]++;
  }
}
 
int calc(int v, int tot_st, int level) {
  int& ret = dp[v][tot_st];
  if (ret == -1) {
    ret = 100000000;
 
    for (int st = 0; st <= std::min(tot_st, children[v]); st++) {
      if (left_sibling[v] == -1 && st < tot_st) continue;
     
	  cout << "##  LEVEL: " << level << " - " << (char)('A'+v) << " - Trying " << st << endl;
      int tret = 0;
 
      if (st == 1) {
		  tret += level; // 1 street
		  cout << "##         +1 STREET" << endl;
	  }
      if (children[v] - st == 1) {
		  tret += level; // 1 avenue
		  cout << "##         +1 AVENUE" << endl;
	  }
 
      if (children[v] > 1) {
		  int x = calc(rightmost_child[v], st, level+1);
		  if (x) {
			cout << "##         +" << x << "  --  Rec1" << endl;
		  }
		  tret += x;
 
        if (st == 1) tret -= level+1;
        if (children[v] - st == 1) tret -= level+1;
      }
      if (left_sibling[v] != -1) {
		  int x = calc(left_sibling[v], tot_st - st, level);
		  if (x) {
			cout << "##         +" << x << "  --  Rec2" << endl;
		  }
		  tret += x;
	  }
     
      ret = std::min(ret, tret);
	  cout << "##  LEVEL: " << level << " - " << (char)('A'+v) << " - Trying " << st << " - RESULT = " << ret << endl;
    }
  }
 
  return ret;
}
 
void printArray(std::string info, int *arr, int n) {
  std::cout << "## " << info << ": ";
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << ", ";
  }
 std::cout << std::endl;
}
 
int main() {
  while (scanf("%d", &n) > 0) {
    cnt = 1;
   
    memset(dp,-1,sizeof(dp));
    memset(nex,-1,sizeof(nex));
   
    rightmost_child[0] = -1;
    children[0] = 0;
   
    for (int i = 0; i < 2*n; i++) {
      scanf("%s", ss);
      add(ss);
      children[0]++;
    }
    printArray("rightmost_child", rightmost_child, 20);
    printArray("left_sibling", left_sibling, 20);
    printArray("children", children, 20);
 
    printf("%d\n", n*calc(rightmost_child[0],n,1));
  }
}

