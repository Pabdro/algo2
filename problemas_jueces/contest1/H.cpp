#include <bits/stdc++.h>
using namespace std;
int parent[30000];
int rango[30000];
int elements[30000];
int ans;
void init(int n) {
    for(int i = 0;  i < n; i++) {
        parent[i] = i;
        rango[i] = 0;
        elements[i] = 1;
    }
}
int find(int x) {
    if(x == parent[x]) {
        return x;
    }
    else {
        parent[x] = find(parent[x]);
        return parent[x];
    }
}
bool sameSet(int x, int y){
    return find(x) == find(y);
}
void unionR(int xRaiz,int yRaiz) { 
    if(!sameSet(xRaiz, yRaiz) ){
        if(rango[xRaiz] > rango[yRaiz]) {
            parent[yRaiz] = xRaiz;
            elements[xRaiz] += elements[yRaiz];
            ans = max(ans, elements[xRaiz]);
        } else {
            parent[xRaiz] = yRaiz;
            elements[yRaiz] += elements[xRaiz];
            ans = max(ans, elements[yRaiz]);
            if(rango[xRaiz] == rango[yRaiz]) {
                rango[yRaiz]++;
            }
        }
    }
}
int main() {
    int cases;
    cin >> cases;
    while(cases--) {
        int n, m;
        cin >> n >> m;
        init(n);
        ans = 1;
        while(m--){
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            unionR(find(x),find(y));
        }
        cout << ans << endl;
    }
    return 0;
}