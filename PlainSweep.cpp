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

struct Rect{
    ll x1, y1, x2, y2;
};
struct RNG{
    ll l, r;
};
Rect rs[200003];
ll tr[1600003], cnt[1600003];
vector<pair<int,int> > v;
vector<ll> ys;
vector<RNG> rngs;
int N;
void update(int l, int r, int nl, int nr, int nd, int v){
    if(rngs[nr].l < l || r < rngs[nl].r) return;
    if(l <= rngs[nl].l && rngs[nr].r <= r) {
        cnt[nd] += v;
        if(cnt[nd]) tr[nd] = rngs[nr].r - rngs[nl].l;
        else tr[nd] = (nl == nr ? 0 : tr[2 * nd] + tr[2 * nd + 1]);
        return;
    }
    int nm = nl + nr >> 1;
    update(l, r, nl, nm, 2 * nd, v);
    update(l, r, nm + 1, nr, 2 * nd + 1, v);
    if(cnt[nd]) tr[nd] = rngs[nr].r - rngs[nl].l;
    else tr[nd] = (nl == nr ? 0 : tr[2 * nd] + tr[2 * nd + 1]);
}
int main(){
    fastio();
    cin >> N;
    for(int i = 1; i <= N; i++){
        ll x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        rs[i] = Rect{x1, y1, x2, y2};
        v.pb({x1, i});
        v.pb({x2, -i});
        ys.pb(y1);
        ys.pb(y2);
    }
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    for(int i = 0; i < sz(ys) - 1; i++) rngs.pb(RNG{ys[i], ys[i + 1]});
    sort(all(v));
    ll prv = -1;
    ll ans = 0;
    for(auto p : v){
        ll cur = p.first;
        int isEnd = p.second < 0;
        int id = abs(p.second);
        ans += (cur - prv) * tr[1];
        update(rs[id].y1, rs[id].y2, 0, sz(rngs) - 1, 1, isEnd ? -1 : 1);
        prv = cur;
    }
    cout << ans << '\n';
}
