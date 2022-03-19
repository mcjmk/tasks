#include <bits/stdc++.h>
using namespace std;


constexpr long long base=1<<18;
long long tree[base<<1+3];
vector<int>numery;
void upd ( long long  v,  long long x)  {
    v+=base;
    tree[v]=x;
    v/=2;
    while (v){
        tree[v]=tree[v*2]+tree[v*2 +1];
        v=v/2;
    }
}

long long query (long long a, long long b) { //przedzial od a do b
    long long  res=0;
    a=a+base-1;
    b=b+base+1;
    while (b-a>1) {
        if (!(a&1))
            res+=tree[a+1];
        if (b&1)
            res+=tree[b-1];
        a/=2;
        b/=2;
    }
    return res;
}

bool ktore;
long long  v,wartosc, a,b;
int n,q;
long long towar[250009],zamow[250009];

vector <pair<int,int>>zamowienia;
set<int>id;

int main () {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    cin>>n;


    for (int i=1; i<=n; i++){
        cin>>towar[i];
        upd(i, towar[i]);
        if (towar[i]>0)
            id.insert(i);}

    for (int i=1; i<=n; i++){
        cin>>zamow[i];
        zamowienia.push_back({zamow[i],i});}


	sort(zamowienia.begin(), zamowienia.end());

    for (int i=0; i<zamowienia.size(); i++) {
        long long koszt=zamowienia[i].first;
        int nr=zamowienia[i].second;
        if(query(1,nr)>=koszt){
            numery.push_back(nr);

            while (koszt>0){
                set<int>::iterator it=id.lower_bound(nr+1);
                --it;
                nr=*it;

                int j=nr;

                int bylo=tree[j+base];
                if (bylo>0) {
                    upd(j, max(bylo-koszt, (long long) 0));

                    if (bylo>=koszt)
                        koszt=0;
                    else if (bylo<koszt){
                        koszt-=bylo;}}
                if (tree[j+base]==0)
                    id.erase(j);}
        }
}




    sort(numery.begin(),numery.end());

    cout<<numery.size()<<endl;
    for (auto g: numery)
        cout<<g<<" ";

    return 0;
 }
