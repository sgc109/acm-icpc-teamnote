#include <bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define fastio() ios::sync_with_stdio(0),cin.tie(0)
using namespace std;

typedef long long ll;
const int MAX_N = 102;

ll D[5003][5003];
int pSum[5003],K[5003][5003];
int f[5003];
int n;
int T;
int main() {
    fastio();
    for(cin >> T; T--;){
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> f[i];
            pSum[i] = pSum[i - 1] + f[i];
        }
        memset(D,0x3c,sizeof(D));
        for(int i = 1; i <= n; i++) D[i][i + 1] = 0, K[i][i + 1] = i + 1;
        for(int size = 2; size <= n; size++){
            for(int i = 1; i + size <= n + 1; i++){
                int j = i + size;
                for(int k = K[i][j-1]; k <= K[i+1][j]; k++){
                    if(D[i][j] > D[i][k] + D[k][j] + pSum[j-1] - pSum[i-1]) {
                        D[i][j] = D[i][k] + D[k][j] + pSum[j-1] - pSum[i-1];
                        K[i][j] = k;
                    }
                }
            }
        }
        cout << D[1][n + 1] << '\n';
    }
    return 0;
}
