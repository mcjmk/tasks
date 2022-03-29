#include <bits/stdc++.h>
using namespace std;

int n,m;

short wagakrawedzipion[1001][1001];
short wagakrawedzipoz[1001][1001];

bool ukladpion[1001][1001];
bool ukladpoziom[1001][1001];

pair<int,int>rep[1001][1001];
int ile[1001][1001];


queue<pair<int, pair<int,int>>>q;
int ilecisu, iletui;

pair <int,int>Find (pair<int,int>A){
    if (rep[A.first][A.second]==A)
        return A;
    return rep[A.first][A.second]=Find(rep[A.first][A.second]);
}

void Union(pair<int,int>A, pair<int,int>B){
    A=Find(A);
    B=Find(B);
    if (ile[A.first][A.second]>ile[B.first][B.second])
        swap(A,B);
    ile[B.first][B.second]+=ile[A.first][A.second];
    rep[A.first][A.second]=B;
}

void mst (int srodek) {
    priority_queue<pair<int,pair<pair<int,int>, pair<int,int>>>>q; //waga, {y1,x1 }, {x2,y2}

    q.push({wagakrawedzipion[n][srodek-1],{{n, srodek}, {n, srodek-1}}});
    q.push({wagakrawedzipion[n][srodek],{{n, srodek}, {n, srodek+1}}});
    q.push({wagakrawedzipoz[n-1][srodek],{{n, srodek}, {n-1, srodek}}});

    while (q.size()){
        int waga=q.top().first;

        int y1=q.top().second.first.first;
        int x1=q.top().second.first.second;
        int y2=q.top().second.second.first;
        int x2=q.top().second.second.second;

        q.pop();


        if (Find({y1,x1})==Find({y2,x2}))
            continue;

        Union({y1,x1},{y2,x2});

        if (abs(y1-y2)) {
            if (y1>y2)
            ukladpoziom[y2][x2]=0;
            else
                ukladpoziom[y1][x2]=0;
            }


        else {
            if (x1>x2)
                ukladpion[y1][x2]=0;
            else
                ukladpion[y1][x1]=0;
            }

        if (x2<=m-1)
            q.push({wagakrawedzipion[y2][x2],{{y2,x2},{y2,x2+1}}});

        if (x2-1>=1)
            q.push({wagakrawedzipion[y2][x2-1],{{y2,x2},{y2, x2-1}}});

        if (y2<=n-1)
            q.push({wagakrawedzipoz[y2][x2],{{y2,x2},{y2+1,x2}}});

        if (y2-1>=1)

        q.push({wagakrawedzipoz[y2-1][x2],{{y2,x2},{y2-1,x2}}});
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    cin>>n>>m;
    char czar;

    for (int i=1; i<=n; i++){
        for (int j=1; j<=m-1; j++){
            cin>>czar;
            ukladpion[i][j]=1;
            if (czar=='C')
                wagakrawedzipion[i][j]=0;
            else
                wagakrawedzipion[i][j]=1;
        }
    }

    for (int i=1; i<=n-1; i++) {
        for (int j=1; j<=m; j++){
            cin>>czar;
            ukladpoziom[i][j]=1;
            if (czar=='C')
                wagakrawedzipoz[i][j]=0;
            else
                wagakrawedzipoz[i][j]=1;
        }
    }

    //n - ilosc wierszy,  m - ilosc kolumn
    // {y, x}

    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            rep[i][j]={i,j};
            ile[i][j]=1;
        }
    }

    ilecisu=0;
    iletui=0;

    int srodek=(m+1)/2;

    mst(srodek);

    for (int i=1; i<=n; i++){
        for (int j=1; j<=m-1; j++){
            if (ukladpion[i][j]){
                if (wagakrawedzipion[i][j]==0)
                    ilecisu++;
                else
                    iletui++;
            }
        }
    }


    for (int i=1; i<=n-1; i++){
        for (int j=1; j<=m; j++){
            if (ukladpoziom[i][j]){
                if (wagakrawedzipoz[i][j]==0)
                    ilecisu++;
                else
                    iletui++;
            }
        }
    }

    cout<<iletui+ilecisu<<" "<<ilecisu<<endl;


    for (int i=1; i<=n; i++){
        for (int j=1; j<=m-1; j++){
            if (ukladpion[i][j]!=0)
                cout<<'Z';
           else
                cout<<'.';
        }
        cout<<endl;
    }


    for (int i=1; i<=n-1; i++){
        for (int j=1; j<=m; j++){
           if (ukladpoziom[i][j]!=0)
                 cout<<'Z';
            else
                cout<<'.';
        }
        cout<<endl;
    }


    return 0;

}
