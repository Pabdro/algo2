#include <bits/stdc++.h> 
using namespace std; 
int n;
string graph[1010];
void solve(int fila, int columna) {
    if(fila>=0 && fila<n && columna>=0 && columna<n && graph[fila][columna]=='1') {
        graph[fila][columna] = '0';
        solve(fila+1, columna); 
        solve(fila-1, columna); 
        solve(fila, columna+1); 
        solve(fila, columna-1); 
        solve(fila+1, columna+1); 
        solve(fila-1, columna-1); 
        solve(fila-1, columna+1); 
        solve(fila+1, columna-1); 
    }
    return;
}
int main () {
    while(cin>>n) {
        for(int i = 0; i<n; i++) {
            cin>>graph[i];
        }
        int nroIslas = 0;
        for(int i = 0; i<n; i++) {
            for(int j = 0; j<n; j++) {
                if(graph[i][j] == '1') {
                    solve(i,j);
                    nroIslas++;
                }
            }
        }
        cout<<nroIslas<<endl;
    }
}