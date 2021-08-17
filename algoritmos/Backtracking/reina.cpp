#include <bits/stdc++.h>
using namespace std;
bool revisionDeReinas(int arcidriche[8][8], int fila, int columna) {
    for(int i = 0; i<columna; i++) {
        if(arcidriche[fila][i]) { 
            return false;
        }
    }
    for(int j = 0; j<columna; j++) {
        if(arcidriche[fila][j]) { 
            return false;
        }
    }
    return true;
}