#include <bits/stdc++.h> 
using namespace std;
int length[3]; 
int N;
int dp[100000];
int solve_dp(int tamanioBarra) { 
    if(tamanioBarra == 0) {
        return 0;
    }
    if(dp[tamanioBarra] == -1) {
        int gananciaMaxima = -1; 
        for(int i = 0; i < sizeof(length)/sizeof(length[0]); i++) { 
            if(tamanioBarra >= length[i]) { 
                gananciaMaxima = max(gananciaMaxima,1 + solve_dp(tamanioBarra - length[i]));
            }
        }
        dp[tamanioBarra] = gananciaMaxima;
    }
    return dp[tamanioBarra];
}
int main() {
    while(cin>>N){
        for(int i = 0 ;i<3;i++){
            cin>>length[i];
        }
        memset(dp, -1, sizeof(dp));
        cout<<solve_dp(N)<<endl;
    }
    
}   