#include <bits/stdc++.h>
using namespace std;

int dp[101][101];

int calc_sprague (int a, int b, vector<pair<int,int>>&dane){
    if (dp[a][b]!=-1)
        return dp[a][b];

    if (a>=b)
        return dp[a][b]=0;

    vector<int>meks;
    for (int i=0; i<dane.size(); i++){
        int l=dane[i].first;
        int r=dane[i].second;
        if (a<=l && r<=b){
            int pierwszy=calc_sprague(a,l, dane);
            int drugi=calc_sprague(r,b,dane);
            int ksor=pierwszy^drugi;
            meks.push_back(ksor);}}

    if (dp[a][b]!=-1)
        return dp[a][b];

    sort(meks.begin(),meks.end());

    int szukanymeks=0;
    for (int i=0; i<meks.size(); i++){
        if (meks[i]==szukanymeks)
            szukanymeks++; }

    dp[a][b]=szukanymeks;
    return szukanymeks;}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int t;
    cin>>t;

    while (t--){
        int n;
        cin>>n;

        vector<pair<int,int>>przedzialy;

        for (int i=0; i<=100; i++){
            for (int j=0; j<=100; j++)
                dp[i][j]=-1; }

        for (int i=0; i<n; i++){
            int a,b;
            cin>>a>>b;
            przedzialy.push_back({a,b});}

        bool win=(calc_sprague(1,100, przedzialy)!=0);

        if (win)
            cout<<"Alice\n";
        else
            cout<<"Bob\n";}



}
