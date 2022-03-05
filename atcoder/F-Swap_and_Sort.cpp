#include <bits/stdc++.h>
using namespace std;

constexpr int N=1004;
vector<int>answer;
int rep[N],ile[N], gdzie[N],silniespojna[N];

int Find (int a){
    if (a==rep[a])
        return a;
    return rep[a]=Find(rep[a]);}

void Union (int a, int b){
    a=Find(a);
    b=Find(b);
    if (ile[a]>ile[b])
        swap(a,b);
    ile[a]+=ile[b];
    rep[a]=b;}

vector<int>G[N];
int n, x, nrsilniespojnej=0;
vector<bool>vis(N);
vector<int>toposort;
map<pair<int,int>,int>dane;

void dfs(int x){
    silniespojna[x]=nrsilniespojnej;
    vis[x]=1;
    for (int i=0; i<G[x].size(); i++){
        if (vis[G[x][i]]==0)
            dfs(G[x][i]); }
    toposort.push_back(x);}

void bfs (int skad, int dokad){
    vector<int>ojciec(N,0);
    queue<pair<int,int>>q; //ktory wierzcholek, z ktorego sie weszlo
    q.push({skad,skad});
    bool znaleziono_droge=0;

    while (znaleziono_droge==0){
        int v=q.front().first, skadweszlo=q.front().second;  
        ojciec[v]=skadweszlo;
        if (v==dokad){ 
            znaleziono_droge=1;
            break;}
        for (int i=0; i<G[v].size(); i++){
            if (ojciec[G[v][i]]==0)
                q.push({G[v][i],v});}
        q.pop();}

    int v=q.front().first;
    while (ojciec[v]!=v){ 
        int pozycjav, pozycjaojcav;
        for (int i=1; i<=n; i++){
            if (gdzie[i]==ojciec[v])
                pozycjaojcav=i;}

        swap(gdzie[skad], gdzie[pozycjaojcav]);
        answer.push_back(dane[{v,ojciec[v]}]);
        v=ojciec[v]; } }


int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);


    cin>>n;
    vector<int>p(n+1);

    for (int i=1; i<=n; i++){
        cin>>p[i];
        gdzie[p[i]]=i;}

    int m;
    cin>>m;
    int a,b;

    for (int i=1; i<=n; i++){
        rep[i]=i;
        ile[i]=1;}


    for (int i=1; i<=m; i++){
        cin>>a>>b;
        if (Find(a)!=Find(b)) {
            Union(a,b);
            dane[{a,b}]=i;
            dane[{b,a}]=i;
            G[a].push_back(b);
            G[b].push_back(a);}}


    for (int i=1; i<=n; i++){
        if (vis[i]==0){
            nrsilniespojnej++;
            dfs(i);}}

    bool istniejerozw=1;
    for (int i=1; i<=n; i++)
        istniejerozw=istniejerozw&(gdzie[i]==i || silniespojna[i]==silniespojna[gdzie[i]]);

    if (istniejerozw==0){
        cout<<"-1"; return 0;}
 

    for (int i=0; i<toposort.size(); i++){
        if (gdzie[toposort[i]]!=toposort[i]) {
           bfs(toposort[i], gdzie[toposort[i]]); } }
            
           

    cout<<answer.size()<<"\n";
    for (auto g:answer)
        cout<<g<<" ";
}
