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
Rect rs[200003];
ll tr[1200003], cnt[1200003];
vector<pair<int,int> > v;
vector<ll> ys;
int N;
void update(int l, int r, int nl, int nr, int nd, int v){
//    printf("nl : %d, nr : %d\n", nl, nr);
    if(nr <= l || r <= nl) return;
    if(l <= nl && nr <= r) {
        cnt[nd] += v;
        if(cnt[nd]) tr[nd] = ys[nr] - ys[nl];
        else tr[nd] = tr[2 * nd] + tr[2 * nd + 1];
        return;
    }
    if(nl + 1 == nr) return;
    int nm = nl + nr >> 1;
    update(l, r, nl, nm, 2 * nd, v);
    update(l, r, nm, nr, 2 * nd + 1, v);
    if(cnt[nd]) tr[nd] = ys[nr] - ys[nl];
    else tr[nd] = tr[2 * nd] + tr[2 * nd + 1];
//    printf("tr[%d] : %lld\n", nd, tr[nd]);
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
    sort(all(v));
    ll prv = -1;
    ll ans = 0;
    for(auto p : v){
//        cout << "tr[1] : " << tr[1] << endl;
        ll cur = p.first;
        int isEnd = p.second < 0;
        int id = abs(p.second);
        ans += (cur - prv) * tr[1];
        ll l = lower_bound(all(ys), rs[id].y1) - ys.begin();
        ll r = lower_bound(all(ys), rs[id].y2) - ys.begin();
//        printf("l : %lld, r : %lld\n", l, r);
        update(l, r, 0, sz(ys) - 1, 1, isEnd ? -1 : 1);
        prv = cur;
//        printf("prv : %lld\n", prv);
    }
    cout << ans;
}
