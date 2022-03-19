#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;



int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);


int n,m;
struct pojazd {
	ull start, koniec, zuzyciepaliwa, iledoladowan; };

vector<pojazd>dane;
vector<ull>odleglosc;


bool czy_sie_da (int nr, ull V){
	ull ile_doladowan_mozna=dane[nr].iledoladowan;
	ull miasto_obecne=dane[nr].start, miasto_docelowe=dane[nr].koniec;
	ull paliwanakm=dane[nr].zuzyciepaliwa;

	ull ile_w_baku=V;
	ull ile_zrobiono_doladowan=0;

	while (miasto_obecne<miasto_docelowe && ile_zrobiono_doladowan<=ile_doladowan_mozna){
		if ((odleglosc[miasto_obecne+1]-odleglosc[miasto_obecne])*paliwanakm > ile_w_baku){
			ile_w_baku=V;
			ile_zrobiono_doladowan++;
			if ((odleglosc[miasto_obecne+1]-odleglosc[miasto_obecne])*paliwanakm > ile_w_baku)
				break;}

		else {
			ile_w_baku-=(odleglosc[miasto_obecne+1]-odleglosc[miasto_obecne])*paliwanakm;
			miasto_obecne++;}}

	return (miasto_obecne == miasto_docelowe && ile_zrobiono_doladowan <= ile_doladowan_mozna);}




ull minimalne_v(int nr, ull poc){

	if (czy_sie_da(nr, poc)==1)
		return poc;

	else {
		ull kon=LLONG_MAX, avg;

		while (kon-poc>1){
			avg=(kon+poc)/2;
			if (czy_sie_da(nr, avg))
				kon=avg;
			else
				poc=avg;}

		return kon; }}


int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);

	cin>>n>>m;
	odleglosc.resize(n+1);


	for (int i=1; i<=n; i++)
		cin>>odleglosc[i];


	for (int i=0; i<m; i++){
		long long startowy,koncowy,paliwanakm, doladowan;
		cin>>startowy>>koncowy>>paliwanakm>>doladowan;

		pojazd temp;
		temp.start=startowy;
		temp.koniec=koncowy;
		temp.zuzyciepaliwa=paliwanakm;
		temp.iledoladowan=doladowan;
		dane.push_back(temp);}


	ull V=1;


	shuffle(dane.begin(),dane.end(),gen);


	for (int i=0; i<m; i++)
		V=minimalne_v(i, V);


	cout<<V;


	}
