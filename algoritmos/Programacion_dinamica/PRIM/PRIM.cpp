#include <bits/stdc++.h> 
#define inf 0x7fffffff
using namespace std;
const int maxn = 2510;
int vis[maxn];
int n;
int mp[maxn][maxn];
int dis[maxn];
struct node {
    int u, v;
} ans[maxn];
bool cmp(node a, node b) {
    if (a.u != b.u) {
        return a.u < b.u;
    } else {
        return a.v < b.u;
    }
}
void prim() {
    int i, j, k, tp;
    for (i = 1; i <= n; i++) {
        dis[i] = inf;
    }
    dis[1] = 0;
    for (i = 1; i <= n; i++) {
        tp = inf;
        for (j = 1; j <= n; j++) {
            if (!vis[j] && tp > dis[j]) {
                tp = dis[j];
                k = j;
            }
        }
        vis[k] = 1;
        for (j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] > mp[k][j]) {
                dis[j] = mp[k][j];
                ans[j].u = min(k, j);
                ans[j].v = max(k, j);
            }
        }
    }
}
int main() {
    memset(vis, 0, sizeof(vis));
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &mp[i][j]);
        }
    }
    prim();
    sort (ans + 1, ans + 1 + n, cmp);
    for (int i = 2; i <= n; i++) {
        printf ("%d %d\n", ans[i].u, ans[i].v);
    }
    return 0;
}