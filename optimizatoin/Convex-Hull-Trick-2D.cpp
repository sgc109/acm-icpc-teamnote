#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
#define fastio() ios::sync_with_stdio(0),cin.tie(0);
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int inf = 0x3c3c3c3c;
const ll infl = 0x3c3c3c3c3c3c3c3c;

int N, K;
int par[203][100003];
ll lid[100003], la[100003], lb[100003];
ll D[2][100003];
ll C[100003];
int A[100003];
int frt, bck;
void insert(ll a, ll b, int id){
    if(bck - frt > 0 && la[bck - 1] == a){
        if(lb[bck - 1] <= b) return; 
        bck--;
    }
    while(bck - frt > 1 && (b - lb[bck - 1]) * (la[bck - 2] - a) <= (b - lb[bck - 2]) * (la[bck - 1] - a)) bck--;
    lid[bck] = id;
    la[bck] = a;
    lb[bck++] = b;
}
pair<ll, int> query(ll x){
    while(bck - frt > 1 && lb[frt + 1] - lb[frt] <= x * (la[frt] - la[frt + 1])) frt++;
    return {la[frt] * x + lb[frt], lid[frt]};
}
int main(){
    fastio();
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) C[i] = C[i - 1] + A[i];
    for(int i = 2; i <= K + 1; i++){
        frt = bck = 0;
        insert(-C[i - 1], C[i - 1] * C[i - 1] - D[~i & 1][i - 1], i - 1);
        for(int j = i; j <= N; j++){
            auto res = query(C[j]);
            D[i & 1][j] = -res.first;
            par[i][j] = res.second;
            insert(-C[j], C[j] * C[j] - D[~i & 1][j], j);
        }
    }
    cout << D[~K & 1][N] << '\n';
    int p = N;
    for(int i = K + 1; i >= 2; i--){
        p = par[i][p];
        cout << p << ' ';
    }
}
