#include <bits/stdc++.h>
using namespace std;

int parent[10000];
int rango[10000];
int sons[10000];

int n;
int m;
map<int,string> jugadores;
map<string,int> posicion;

void init() {
    for(int i=0;  i<= n; i++) {
        parent[i] = i;
        rango[i] = 0;
        sons[i] = 1;
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

void unionRango(int x,int y) { 
    int xRaiz = find(x);
    int yRaiz = find(y);
    if(xRaiz == yRaiz ){
        return;
    }
    if(rango[xRaiz] > rango[yRaiz]) {
        parent[yRaiz] = xRaiz;
        sons[xRaiz] = sons[xRaiz] + sons[yRaiz];
    } else {
        parent[xRaiz] = yRaiz;
        sons[yRaiz] = sons[xRaiz] + sons[yRaiz];
        if(rango[xRaiz] == rango[yRaiz]) {
            rango[yRaiz]++;
        }
    }
}
int main() {
    cin >> n; 
    while(n--) {
        for(int i = 1; i <= n;i++) {
            string nombre;
            cin >> nombre;
            jugadores[i] = nombre;
            posicion[nombre] = i;
        }
    } 
    init();
    while(m--) {
        string x, y;
        cin >> x >> y;
        unionRango(posicion[x],posicion[y]);
    }  
    string jugador;
    cin >> jugador;
    int position = posicion[jugador];
    cout << sons[parent[find(position)]] <<endl;
    return 0;
}