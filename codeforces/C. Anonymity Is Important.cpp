#include <bits/stdc++.h>
using namespace std;

constexpr int base=1<<18;
vector<int>tree(base<<1, INT_MAX);

void ustaw(int v, int x){
	v+=base;
	if (tree[v]>x)
		tree[v]=x;
	v=v/2;
	while (v){
		tree[v]=min(tree[2*v],tree[2*v+1]);
		v=v/2; }}

int minimum (int a, int b){
	a+=base-1;
	b+=base+1;
	int res=INT_MAX;

	while (b-a>1){
		if (!(a&1)) res=min(res,tree[a+1]);
		if (b&1)	res=min(res,tree[b-1]);
		a=a>>1; b=b>>1;  }
	return res; }

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

	int n,q;
	cin>>n>>q;

	set<int>potencjalniechorzy;

	for (int i=1; i<=n; i++)
		potencjalniechorzy.insert(i);

	while (q--){
		bool rodzaj;
		cin>>rodzaj;

		if (rodzaj==0){
			int l,r;
			bool ill;
			cin>>l>>r>>ill;
			if (ill==0){
				set<int>::iterator it=potencjalniechorzy.lower_bound(l);
				for (it; (*it<=r && it!=potencjalniechorzy.end());){
					int nowawartosc=*it;
					potencjalniechorzy.erase(it);
					it=potencjalniechorzy.upper_bound(nowawartosc);}}

			else
				ustaw(l, r);}

		else {
			int x;
			cin>>x;

			auto g=potencjalniechorzy.lower_bound(x);
			if (*g!=x)
				cout<<"NO\n";

			else {
				int pierwszymniejszy=0, pierwszywiekszy=n+1;
				set<int>::iterator mniejsze=potencjalniechorzy.lower_bound(x);
				set<int>::iterator wieksze=potencjalniechorzy.lower_bound(x+1);

				if (mniejsze != potencjalniechorzy.begin()){
					--mniejsze;
					pierwszymniejszy=*mniejsze; }

				if (wieksze!=potencjalniechorzy.end())
					pierwszywiekszy=*wieksze;

				if (minimum(pierwszymniejszy+1, x)<pierwszywiekszy)
					cout<<"YES\n";
				else
					cout<<"N/A\n";
				}
			}

		}



}
