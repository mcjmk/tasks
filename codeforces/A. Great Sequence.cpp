#include <bits/stdc++.h>
using namespace std;


int main(){
    int t;
    cin>>t;

    while (t--){
        int n; long long x, ai;
        cin>>n>>x;
        vector<long long>a;

        for (int i=0; i<n; i++){
            cin>>ai;
            a.push_back(ai);}

        sort(a.begin(),a.end());

        int ans=0;

        map<long long,int>available;

        for (int i=0; i<a.size(); i++)
            available[a[i]]++;

        for (int i=0; i<a.size(); i++){
            if (available[a[i]] && available[x*a[i]]){
                available[a[i]]--;
                available[x*a[i]]--; }
            else if (available[a[i]]){
                available[a[i]]--;
                ans++; } }
        cout<<ans<<"\n"; }





}
