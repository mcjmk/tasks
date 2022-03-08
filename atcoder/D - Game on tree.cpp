#include <bits/stdc++.h>
using namespace std;

constexpr int N=1e5+3;

vector<int>G[N];
bool vis[N];

int dfs(int x){
    vis[x]=1;
    int ksor=0;

    for (int i=0; i<G[x].size(); i++){
        if (vis[G[x][i]]==0)
            ksor=ksor^(dfs(G[x][i])+1);}
    return ksor; }

int main(){
    int n;
    cin>>n;

    for (int i=0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);}

    int wartosc=dfs(1);
    bool wygralaAlicja=(wartosc!=0);

    if (wygralaAlicja)
        cout<<"Alice";
    else
        cout<<"Bob";

}
