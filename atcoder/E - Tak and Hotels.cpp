#include <bits/stdc++.h>
using namespace std;

constexpr int N=2e5+2;

set<int>dane;
map<int,int>nr_miasta; // wspolrzedna x, ktore_miasto
int wspolrzedne[N]; // nr miasta, wspolrzedna miasta

int gdzie[N][30];  //gdzie[x][j]
				   //gdzie dojde najdalej z x-tego po 2^j dniach
int main(){

	int n;
	cin>>n;

	for (int i=1; i<=n; i++){
		int x;
		cin>>x;
		wspolrzedne[i]=x;
		dane.insert(x);
		nr_miasta[{x}]=i;}

	int L;
	cin>>L;

	for (int i=1; i<=n; i++){
		set<int>::iterator it=dane.lower_bound(wspolrzedne[i]+L+1);
		it--;
		gdzie[i][0]=nr_miasta[*it];}

	for (int i=1; i<28; i++){
		for (int j=1; j<=n; j++)
			gdzie[j][i]=gdzie[gdzie[j][i-1]][i-1];}


	int q;
	cin>>q;

	while (q--){
		int a, b;
		cin>>a>>b;

		if (a>b)
			swap(a,b);

		int ile_dni=0;

		while (a<b){

			if (gdzie[a][0]>=b){
				ile_dni++;
				a=gdzie[a][0];
				break;}


			for (int i=1; i<28; i++){
				if (gdzie[a][i]>=b){
					a=gdzie[a][i-1];
					ile_dni+=(1<<(i-1));
					break;}}}

		cout<<ile_dni<<endl; }


		// dopoki nie dojdziesz do miasta ktorego przejscie o 0
		// przekroczy b

		// idz do ostatniego niewiekszego od b



	}
