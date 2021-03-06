#include <bits/stdc++.h>
using namespace std;

constexpr int N=2e5+2;

vector<int>G[N];
int wysokosc[N], sygnal[N];
pair<int,int>maksdziecko[N]; // ustawiony sygnal, id
vector<bool>vis(N);
long long wynik, korzen,wysokosckorzenia;

void dfs(int x){
	vis[x]=1;

	if (G[x].size()==1) { //jesli jest lisciem
		sygnal[x]=wysokosc[x];
		wynik+=wysokosc[x];
		maksdziecko[x]={sygnal[x],x};
		if (x!=korzen)
			return;}

	for (int i=0; i<(int)G[x].size(); i++){
		if (vis[G[x][i]]==0){
			dfs(G[x][i]);
			if(! (x==korzen && G[x].size()==1))
				maksdziecko[x]=max(maksdziecko[G[x][i]], maksdziecko[x]);}}


	if (maksdziecko[x].first<wysokosc[x]){

		wynik+=wysokosc[x]-maksdziecko[x].first;
		sygnal[maksdziecko[x].second]+=wysokosc[x]-maksdziecko[x].first;
		maksdziecko[x].first=sygnal[maksdziecko[x].second];}

	if (x==korzen){
		int id_jednego_z_dzieci;
		pair<int,int>pierwsze=maksdziecko[x];
		pair<int,int>drugie={0,0};

		id_jednego_z_dzieci=pierwsze.second;

		for (int i=0; i<(int)G[x].size(); i++){
			if (maksdziecko[G[x][i]].second!=id_jednego_z_dzieci)
				drugie=max(drugie, maksdziecko[G[x][i]]);}

		if (drugie.first<wysokosc[x])
			wynik+=wysokosc[x]-drugie.first;}
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);


	int n;
	cin>>n;


	for (int i=1; i<=n; i++){
		cin>>wysokosc[i];
		if (wysokosc[i]>wysokosckorzenia){
			wysokosckorzenia=wysokosc[i];
			korzen=i; } }



	for (int i=0; i<n-1; i++){
		int a,b;
		cin>>a>>b;
		G[a].push_back(b);
		G[b].push_back(a);}

	dfs(korzen);

	cout<<wynik;



	}
