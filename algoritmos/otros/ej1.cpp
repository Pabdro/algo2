#include <bits/stdc++.h>
using namespace std;
long long n; 
bool f(long long number) {
    return number*number <= n;
}
bool bs() {
    int ini = 0;
    int fin = 1000000000;
    while(ini<fin){
        int mid = (ini+fin)/2;
        if(f(mid)){
            fin = mid;
        }
        else{
            ini = mid+1;
        }
    }
    return f(ini);
}
int main() {
    while(cin>>n){
        cout<< bs() <<endl;
    }
    return 0;
}