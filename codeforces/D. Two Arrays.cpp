#include <bits/stdc++.h>
using namespace std;

constexpr int INF=INT_MAX;

int seed = chrono::high_resolution_clock::now().time_since_epoch().count();

mt19937 gen(seed);
int randint(int l, int r){
    return uniform_int_distribution<int>{l, r}(gen);}

int ktorybit[500009];
bool istniejewynik=0;
int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);


	int n,m;
	cin>>n>>m;

	vector<int>a[n+1];
	vector<int>dane[n+1];

	vector<int>skalowanie;
	map<int,int>nowawartosc;
	vector<long long>wartosc;

	for (int i=0; i<n; i++){
		for (int j=0; j<m; j++){
			int x;
			cin>>x;
			a[i].push_back(x);
			skalowanie.push_back(x);}
		long long w;
		cin>>w;
		wartosc.push_back(w);}

	sort(skalowanie.begin(),skalowanie.end());
	skalowanie.erase(unique(skalowanie.begin(),skalowanie.end()),skalowanie.end());

	for (int i=0; i<(int)skalowanie.size(); i++)
		nowawartosc[{skalowanie[i]}]=i;

	for (int i=0; i<n; i++){
		for (int j=0; j<m; j++)
			dane[i].push_back(nowawartosc[a[i][j]]);}


	int wynik=INF;


	while (clock() <= 2.6 * CLOCKS_PER_SEC){
		//wylosuj liczbom nr bitow w masce
		for (int i=0; i<(int)skalowanie.size(); i++)
			ktorybit[i]=randint(0,19);


		vector<long long>dp(1<<20, INF);

		for (int i=0; i<n; i++){
			int maska=0;
			for (int j=0; j<m; j++)
				maska=maska|(1<<(ktorybit[dane[i][j]]));
		 	dp[maska]=min(dp[maska],wartosc[i]); }



		for (int j=0; j<20; j++){
			for (int maska=0; maska<(1<<20); ++maska)
				if (maska&(1<<j))
					dp[maska]=min(dp[maska], dp[maska ^ (1<<j)]);}

		long long temp=INF;

		for (int i=0; i<n; i++){
			long long maska=0;

			for (int j=0; j<m; j++)
				maska=maska|(1<<(ktorybit[dane[i][j]]));

			long long negacjamaski=maska^((long long)(1<<20)-1);


			temp=min(temp, wartosc[i]+dp[negacjamaski]);}

		if (temp<wynik){
			wynik=temp;

			  }}


	if (wynik==INF)
		cout<<-1;
	else {
		cout<<wynik;}

	}
