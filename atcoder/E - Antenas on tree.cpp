#include <bits/stdc++.h>
using namespace std;

constexpr int N=1e5+3;
bool vis[N];
vector<int>G[N];

int dp[N]; // w ile antenek da sie zalatwic cale poddrzewo v

void dfs(int x){
    vis[x]=1;

    int ilenieodwiedzonychsasiadow=0;
    int sumapowynikach=0;

	int ileniezerowychdpdzieci=0;

    for (int i=0; i<G[x].size(); i++){
        if (vis[G[x][i]]==0){
			dfs(G[x][i]);
			sumapowynikach+=dp[G[x][i]];
			if (dp[G[x][i]]>0)
				ileniezerowychdpdzieci++;
           ilenieodwiedzonychsasiadow++;}}


    dp[x]=max(ilenieodwiedzonychsasiadow-1,0);

    int ilemoznazalatwic=min(dp[x],ileniezerowychdpdzieci);

    dp[x]=dp[x]-ilemoznazalatwic+sumapowynikach;

    }

int main(){

    int n,a,b;
    cin>>n;

    int ilemaks=0;
    int korzen;
    for (int i=0; i<n-1; i++){
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);}

    for (int i=0; i<n; i++){
        if (G[i].size()>ilemaks){
            ilemaks=G[i].size();
            korzen=i;}}
	dfs(korzen);

    int wynik=dp[korzen];

    if (wynik==0)
        wynik++;
    cout<<wynik;
}
