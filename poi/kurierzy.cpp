#include <bits/stdc++.h>
using namespace std;


int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
int randint(int l, int r){
    return uniform_int_distribution<int>{l, r}(gen);} 

vector<int>gdzie[500009]; 
vector<int>p; 

bool czylider(int l, int r, int x){   
    vector<int>::iterator pierwszy, ostatni;
    pierwszy = lower_bound(gdzie[x].begin(), gdzie[x].end(), l);
    ostatni = lower_bound(gdzie[x].begin(), gdzie[x].end(), r+1); 
	--ostatni; 
	
	auto ile=(distance(pierwszy,ostatni)); // how many X  in [l,r]
	return (ile+1>(r-l+1)/2); }

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	
	int n,m;
	cin>>n>>m;
	
	p.push_back(0);
	for (int i=1; i<=n; i++){
		int x;
		cin>>x;
		p.push_back(x);
		gdzie[x].push_back(i); }
		 
		
	for (int i=0; i<m; i++){
		int a, b;
		cin>>a>>b;  
		int wynik=0; 
		
		for (int j=0; j<30; j++){
			int kandydat=p[randint(a,b)];	
			if (czylider(a,b,kandydat))
				wynik=kandydat;
			}
				
		cout<<wynik<<endl;}
	
	
}