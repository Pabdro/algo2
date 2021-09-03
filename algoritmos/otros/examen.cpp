#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}
int maxDivisorRango(int a, int b, int l, int tope) {
    int g = gcd(a, b);
    int resto = -1;
    for (int i = l; i * i <= g && i <= tope; i++) {
        if (g % i == 0) {
            resto = max({resto, i, g / i});
        }
    return resto;
}
int main() {
    int a = 5, b = 27, l = 1, tope = 5;
    cout << maxDivisorRango(a, b, l, tope) << endl;
    return 0;
}