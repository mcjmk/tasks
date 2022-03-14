#include <bits/stdc++.h>
using namespace std;

constexpr int N=6e5+3;

 // v, waga
vector<pair<int,long long>>G[N];

int main () {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int t;
    cin>>t;

    while (t--){
        int k;
        cin>>k;

        int N=2*k;

        for (int i=0; i<N-1; i++){
            int a,b; long long c;
            cin>>a>>b>>c;
            G[a].push_back({b,c});
            G[b].push_back({a,c});}


        long long minimum=0, maximum=0;

        vector<int>wielkosc_poddrzewa(N+5,1);

        // obliczenie wielkosci poddrzew
        auto dfs = [&] (auto &dfs, int x, int parent) -> void {
            for (int i=0; i<G[x].size(); i++){
                if (G[x][i].first!=parent){
                    dfs(dfs,G[x][i].first,x);
                    wielkosc_poddrzewa[x]+=wielkosc_poddrzewa[G[x][i].first];
                }
            }
        };
        dfs(dfs,1,-1);


        // jesli w poddrzewie jest nieparzyscie to dodaj krawedz, w przeciwnym razie - nie
        auto oblicz_min= [&] (auto &oblicz_min, int x, int parent) -> void {
            for (int i=0; i<G[x].size(); i++){
                if (G[x][i].first!=parent){
                    oblicz_min(oblicz_min,G[x][i].first,x);
                    minimum+=(wielkosc_poddrzewa[G[x][i].first]%2==1)*G[x][i].second;}
                }
            };

        oblicz_min(oblicz_min,1,-1);

        auto oblicz_max = [&] (auto &oblicz_max, int x, int parent) -> void {
            for (int i=0; i<G[x].size(); i++){
                if (G[x][i].first!=parent){
                    oblicz_max(oblicz_max,G[x][i].first,x);
                    maximum+=min(wielkosc_poddrzewa[G[x][i].first],N-wielkosc_poddrzewa[G[x][i].first])*G[x][i].second;}
                }
            };
        oblicz_max(oblicz_max,1,-1);

        cout<<minimum<<" "<<maximum<<"\n";
        for (int i=1; i<=N; i++)
            G[i].resize(0);}









}
