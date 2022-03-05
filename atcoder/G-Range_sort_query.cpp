#include <bits/stdc++.h>
using namespace std;

constexpr int base=1<<19;


pair<int,int>tree[base<<1];
int zaileodpowiada[base<<1];
vector<int>star(base<<1, -1);

void push (int v){
	if (star[v]==0){
		tree[2*v]={zaileodpowiada[2*v],0};
		tree[2*v+1]={zaileodpowiada[2*v],0};
		star[2*v]=star[v];
		star[2*v+1]=star[v];
		star[v]=-1;}

	else if (star[v]==2){
		tree[2*v]={0,zaileodpowiada[2*v]};
		tree[2*v+1]={0,zaileodpowiada[2*v]};
		star[2*v]=star[v];
		star[2*v+1]=star[v];
		star[v]=-1;}}

pair<int,int> suma (int v, int a, int b, int p, int k){
	pair<int,int>odp={0,0};
	if (k<a || p>b) return {0,0};
	else if (p<=a && b<=k)
		return tree[v];
	else {
		if (star[v]!=-1)
			push(v);
		int lewy=2*v, prawy=2*v+1, avg=(a+b)/2;
		pair<int,int>p1=suma(lewy, a, avg, p, k);
		pair<int,int>p2=suma(prawy,avg+1,b,p,k);
		odp={p1.first+p2.first,p1.second+p2.second};
		return odp;}}

void update (int v, int a, int b, int p, int k, int rodzaj){
	if (k<a || p>b) return;
	else if(p<=a && b<=k) {
		star[v]=rodzaj;
		if (rodzaj==0)
			tree[v]={zaileodpowiada[v],0};

		else if (rodzaj==1)
			tree[v]={0,0};

		else if (rodzaj==2)
			tree[v]={0,zaileodpowiada[v]};}

	else {
		push(v);
		int lewy=2*v, prawy=2*v+1, avg=(a+b)/2;
		update(lewy, a, avg, p, k,rodzaj);
		update(prawy, avg+1, b, p, k,rodzaj);
		tree[v]={tree[2*v].first+tree[2*v+1].first, tree[2*v].second+tree[2*v+1].second};}}


int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

	int n,q,x;
	cin>>n>>q>>x;
	int wynik;

	for (int i=0; i<n; i++){
		int p;
		cin>>p;
		if (p<x)
			tree[i+base]={1,0};
		else if (p>x)
			tree[i+base]={0,1};
		else
			wynik=i;
		zaileodpowiada[i+base]=1;}

	for (int i=base-1; i>=0; i--){
		tree[i]={tree[2*i].first+tree[2*i+1].first,tree[2*i].second+tree[2*i+1].second};
		zaileodpowiada[i]=zaileodpowiada[2*i]+zaileodpowiada[2*i+1];}

	while (q--){
		int rodzaj, a,b;
		cin>>rodzaj>>a>>b;
		a--; b--;

	 	pair<int,int> ile=suma(1,0,base-1,a,b);
		int przedzial=(b-a)+1;

		int ilemniejszych=ile.first;
		int ilewiekszych=ile.second;
		int czyx=(przedzial!=ile.first+ile.second);

		if (rodzaj==1){
			if (ilemniejszych>0)
				update(1,0,base-1, a, a+ilemniejszych-1, 0);

			if (czyx) {
				update(1,0,base-1,a+ilemniejszych, a+ilemniejszych, 1);
				wynik=a+ilemniejszych;}

			if (ilewiekszych>0)
				update(1,0,base-1,b-ilewiekszych+1,b,2);}

		else {
			if (ilewiekszych>0)
				update(1,0,base-1, a, a+ilewiekszych-1, 2);

			if (czyx){
				update(1,0,base-1,a+ilewiekszych, a+ilewiekszych, 1);
				wynik=a+ilewiekszych;}

			if (ilemniejszych>0)
			update(1,0,base-1,b-ilemniejszych+1,b,0);}}

	cout<<wynik+1;

}
