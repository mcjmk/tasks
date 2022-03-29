#include <bits/stdc++.h>
using namespace std;

long long m;
int n,k;
int binarylifting[3][1000009];

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);

    cin>>n>>k>>m;

    vector<int>dokad(n+1);
    vector<long long>dane(n+1);

    for (int i=1; i<=n; i++){
        long long x;
        cin>>x;
        dane[i]=x;
        }

    int l=1, r=min(k+1,n);
    binarylifting[0][1]=min(k+1,n);

    for (int i=1; i<=n; i++)
        dokad[i]=i;

    for (int i=2; i<=n; i++){

        while (l<i && r<n && dane[i]-dane[l]>dane[r+1]-dane[i]){
            l++;
            r++;
            }

        if (dane[i]-dane[l] >= dane[r] - dane[i])
            binarylifting[0][i]=l;

        else
            binarylifting[0][i]=min(r,n);
        }


    for (long long i=1; i<=63; i++){
        for (int j=1; j<=n; j++){
                binarylifting[i%3][j]=binarylifting[(i+2)%3][binarylifting[(i+2)%3][j]];

            if (m &(1LL<<(i-1))){
                dokad[j]=binarylifting[(i+2)%3][dokad[j]];
            }
        }
    }

    for (int i=1; i<=n; i++)
        cout<<dokad[i]<<" ";


}
