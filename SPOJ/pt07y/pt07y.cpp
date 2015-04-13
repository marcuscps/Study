#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct node {
    node *parent;
    
    node() : parent(NULL) {
    }
    
    node * getRoot() {
        node *p = this;
        while (p->parent != NULL) {
            p = p->parent;
        }
        return p;
    }
    
    void connect(node *p) {
        p->parent = this;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input.txt", "r", stdin);

    vector<node> nodes;
    int n, m;
    int o, d;
    
    scanf("%d %d", &n, &m);    
    if (m != n - 1) {
        printf("NO\n");
        return 0;
    }

    nodes.reserve(n);
    for (int ii = 0; ii < n; ++ii) {
        nodes.push_back(node());
    }
    
    for (int ii = 0; ii < m; ++ii) {
        scanf("%d %d", &o, &d);
        
        node *a = nodes[--o].getRoot();
        node *b = nodes[--d].getRoot();
        
        if (a == b) {
            printf("NO\n");
            return 0;
        }

        a->connect(b);
    }

    printf("YES\n");
    return 0;
}
