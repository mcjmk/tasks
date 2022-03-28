#include <bits/stdc++.h>
using namespace std;

constexpr int N=100003;
int n,k;
vector<int>G[N];
bool odpowiedz[N], usunietyzcentroidu[N];
long long rzutowanie[N], wartosc[N];
int wielkoscpoddrzewa[N];
stack<pair<long long, int>>wrzucenie;
set<pair<long long, int>>jakiemoznauzyskac;

int seed = 2137213;
mt19937 gen(seed);

long long randint(long long l, long long r){
    return uniform_int_distribution<long long>{l, r}(gen);}

int znajdzcentroid (int v, int wielkoscdrzewa){
    for (int i=0; i<G[v].size(); i++){
        if (usunietyzcentroidu[G[v][i]]==0 && 2*wielkoscpoddrzewa[G[v][i]]>wielkoscdrzewa){
            wielkoscpoddrzewa[v]-=wielkoscpoddrzewa[G[v][i]];
            wielkoscpoddrzewa[G[v][i]]=wielkoscdrzewa;
            v=znajdzcentroid(G[v][i], wielkoscdrzewa);}}
    return v;}

void policz_wielkosci_poddrzew (int v, int parent){
    wielkoscpoddrzewa[v]=1;
    for (int i=0; i<G[v].size(); i++){
        if (usunietyzcentroidu[G[v][i]]==0 && G[v][i] != parent){
            policz_wielkosci_poddrzew(G[v][i], v);
            wielkoscpoddrzewa[v]+=wielkoscpoddrzewa[G[v][i]];}}}

bool dfs_magic (int x, int parent, int glebokosc, long long wartosc_wchodzaca, long long wartosc_centroidu){
    long long wartoscobecnego=wartosc_wchodzaca+wartosc[x];
    wrzucenie.push({wartoscobecnego, glebokosc});
    bool jakiessieudalo=0;

	if (wartoscobecnego==0){
		odpowiedz[x]=1;
		jakiessieudalo=1; }

    long long szukanawartosc=(wartosc_centroidu-wartoscobecnego);
    int szukanadrugaglebokosc=k-glebokosc+1;

	pair<long long, int>szukanapara={szukanawartosc,szukanadrugaglebokosc};

	if (jakiemoznauzyskac.find(szukanapara)!=jakiemoznauzyskac.end()){
        odpowiedz[x]=1;
		jakiessieudalo=1;}

    if (glebokosc<k){
		int sajz=G[x].size();

        for (int i=0; i<sajz; i++){
            if (usunietyzcentroidu[G[x][i]]==0 && G[x][i]!=parent)
                jakiessieudalo=dfs_magic(G[x][i], x, glebokosc+1, wartoscobecnego, wartosc_centroidu)|| jakiessieudalo;
            //chamski zmniejszanie grafu
			else {
				if (usunietyzcentroidu[G[x][i]] && sajz>0){
					swap(G[x][i], G[x][sajz-1]);
					sajz--;
					G[x].pop_back();
					if (sajz!=0)
						i--; }}

				}
            }
	odpowiedz[x]=odpowiedz[x]||jakiessieudalo;

    return jakiessieudalo;}


void policz(int v) {

    policz_wielkosci_poddrzew(v, -1);
    int wielkosc=wielkoscpoddrzewa[v];
    v=znajdzcentroid(v, wielkosc);

    long long wartosc_centroidu=wartosc[v];
	bool jakiessieudalo=0;



    int sajz=G[v].size();

    for (int i=0; i<sajz; i++){
        if (usunietyzcentroidu[G[v][i]]==0) {
			jakiessieudalo=dfs_magic(G[v][i], v, 2,wartosc_centroidu, wartosc_centroidu) || jakiessieudalo;
            while (wrzucenie.size()){
                pair<long long,int> gora=wrzucenie.top();
                wrzucenie.pop();
                jakiemoznauzyskac.insert(gora);}}

        //chamskie zmniejszanie grafu
		else {
			swap(G[v][i], G[v][sajz-1]);
			G[v].pop_back();
			sajz--;
			if (sajz!=0)
				i--;}
        }

    if (jakiessieudalo)
		odpowiedz[v]=1;


    jakiemoznauzyskac.clear();
	jakiessieudalo=0;

    for (int i=G[v].size()-1; i>=0; i--){
        if (usunietyzcentroidu[G[v][i]]==0) {
			jakiessieudalo= dfs_magic(G[v][i], v, 2,wartosc_centroidu, wartosc_centroidu) || jakiessieudalo;
            while (wrzucenie.size()){
                pair<long long,int> gora=wrzucenie.top();
                wrzucenie.pop();
                jakiemoznauzyskac.insert(gora);}}}

    if (jakiessieudalo)
		odpowiedz[v]=1;

    jakiemoznauzyskac.clear();

    usunietyzcentroidu[v]=1;
    sajz=G[v].size();
    for (int i=0; i<sajz; i++){
        if (usunietyzcentroidu[G[v][i]]==0)
            policz(G[v][i]);

        //chamskie zmniejszanie grafu
        else if (sajz>1){
			swap(G[v][i], G[v][sajz-1]);
			sajz--;
			G[v].pop_back();
			if (sajz !=0)
				i--; }

            }
}

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);


    int q;
    cin>>n>>k>>q;

    long long suma=0;

    for (int i=1; i<=k-1; i++){
        rzutowanie[i]=randint(1,100000000);
        suma+=rzutowanie[i];}

    rzutowanie[k]=-1*suma;

    for (int i=1; i<=n; i++){
        int a;
        cin>>a;
        wartosc[i]=rzutowanie[a];}


    for (int i=0; i<n-1; i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);}

    policz(1);


    while (q--){
        int x;
        cin>>x;
        if (k==1 )
			cout<<"YES\n";
		else {


        if (odpowiedz[x])
            cout<<"YES\n";
        else
            cout<<"NO\n"; } }
}
