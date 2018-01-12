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

int N;
ll a, b, c;
int A[1000003];
ll C[1000003], D[1000003];
ll la[1000003], lb[1000003];
int frt, bck;
void insert(ll a, ll b){
    while(bck - frt > 1 && (lb[bck - 2] - b) * (a - la[bck - 1]) >= (lb[bck - 1] - b) * (a - la[bck - 2])) bck--;
    la[bck] = a;
    lb[bck++] = b;
}
ll query(ll x){
    while(bck - frt > 1 && lb[frt + 1] - lb[frt] <= x * (la[frt] - la[frt + 1])) frt++;
    return la[frt] * x + lb[frt];
}
ll f(ll x){
    return a * x * x + b * x + c;
}
int main(){
    fastio();
    cin >> N;
    cin >> a >> b >> c;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) C[i] = C[i - 1] + A[i];
    for(int i = 1; i <= N; i++){
        if(i == 1) D[i] = f(C[i]);
        else D[i] = -query(C[i]) + a * C[i] * C[i] + b * C[i] + c;
        D[i] = max(D[i], f(C[i]));
        insert(2 * a * C[i], -D[i] - a * C[i] * C[i] + b * C[i]);
    }
    cout << D[N];
}
