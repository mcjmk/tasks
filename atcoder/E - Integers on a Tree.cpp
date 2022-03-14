#include <bits/stdc++.h>
using namespace std;

constexpr int N=1e5+3;

vector<int>G[N];
vector<bool>staly(N);
vector<bool>vis(N);

int main(){

    int n;
    cin>>n;

    for (int i=0; i<n-1; i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a); }

    vector<int>wartosc(N,1000009);

    int k;
    cin>>k;


    priority_queue<pair<int,int>>q;

    for (int i=0; i<k; i++){
        int v,p;
        cin>>v>>p;
        wartosc[v]=p;
        q.push({p,v});
        staly[v]=1;}

    //dijkstra

    while (q.size()){
        int x=q.top().second;
        int odleglosc=q.top().first;
        q.pop();

        if (vis[x])
            continue;
        vis[x]=1;

        for (int i=0; i<G[x].size(); i++){
            if (vis[G[x][i]]==0 && staly[G[x][i]]==0 && odleglosc-1<wartosc[G[x][i]]){
                wartosc[G[x][i]]=odleglosc-1;
                q.push({wartosc[G[x][i]],G[x][i]});}}}


    bool dasie=1;

    auto dfs = [&](auto &dfs, int v, int ojciec)->void{
        for(auto w : G[v]){

            dasie=dasie&&(abs(wartosc[w]-wartosc[v])==1);
            if(w!=ojciec)
                dfs(dfs, w,v);}};

    dfs(dfs, 1, -1);



    if (dasie==0){
        cout<<"No"; return 0; }

    cout<<"Yes"<<endl;
    for (int i=1; i<=n; i++)
        cout<<wartosc[i]<<endl;
}
