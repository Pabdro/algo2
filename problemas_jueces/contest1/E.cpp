#include <bits/stdc++.h> 
using namespace std;
struct Trie {
    int values;
    Trie *child[10];
    Trie() {
        values=0;
        memset(child,NULL,sizeof(child));
    }
}*trie;
bool f;
int ans=0;
void create (string s) {
    Trie *x=trie;
    for(int i=0; i<s.length();i++) {
        int d=s[i]-'0';
        if(x->child[d]==NULL) {
            x->child[d]=new Trie;
        }
        x=x->child[d];
                 if (x-> values != 0) {
            f=false;
            break;
        }
    }
    x->values++;
         for (int i = 0; i <10; i ++) {
        if(x->child[i]!=NULL) {
            f=false;
            return;
        }
    }
}
 void deleteTrie (Trie * x) {
    if(x==NULL)
        return;
    for(int i=0; i<10; i++) {
        if(x->child[i]!=NULL) {
            deleteTrie(x->child[i]);
        }
    }
    delete x;
}
int main() {
    int T,n,f1,k;
    string s;
    cin>>T;
    while(T--) {
        cin>>n;
        trie=new Trie;
        f=true;
        k=n;
        while(n--) {
            cin>>s;
            create(s);
        }
        if(f==false) {
            cout<<"NO\n";
        }
        if(f==true)
            cout<<"YES\n";
        deleteTrie(trie);
    }
}