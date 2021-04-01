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
vector <pair<int, int>> G[200003];
pair<ll, int> dist[200003];
map<int, int> mp;
int size[200003];
int kil[200003];
vector<int> stk;

void get_sz(int cur, int dad) {
    size[cur] = 1;
    for (auto p : G[cur]) {
        int nxt = p.first;
        if (nxt == dad || kil[nxt]) continue;
        get_sz(nxt, cur);
        size[cur] += size[nxt];
    }
}

int get_cent(int cur, int dad, int cap) {
    for (auto p : G[cur]) {
        int nxt = p.first;
        if (nxt == dad || kil[nxt]) continue;
        if (size[nxt] > cap) return get_cent(nxt, cur, cap);
    }
    return cur;
}

void dfs(int cur, int dad) {
    stk.pb(cur);
    for (auto p : G[cur]) {
        int nxt = p.first;
        int cst = p.second;
        if (nxt == dad || kil[nxt]) continue;
        dist[nxt] = {dist[cur].first + cst, dist[cur].second + 1};
        dfs(nxt, cur);
    }
}

int ans;

void go(int root) {
    mp.clear();
    mp[0] = 0;
    get_sz(root, -1);
    int cent = get_cent(root, -1, size[root] / 2);
    kil[cent] = 1;
    for (auto p : G[cent]) {
        stk.clear();
        int ch = p.first;
        int cst = p.second;
        if (kil[ch]) continue;
        dist[ch] = {cst, 1};
        dfs(ch, cent);
        for (int desc : stk) {
            if (dist[desc].first <= K && mp.find(K - dist[desc].first) != mp.end()) {
                ans = min(ans, mp[K - dist[desc].first] + dist[desc].second);
            }
        }
        for (int desc : stk) {
            if (mp.find(dist[desc].first) != mp.end())
                mp[dist[desc].first] = min(mp[dist[desc].first], dist[desc].second);
            else mp[dist[desc].first] = dist[desc].second;
        }
    }
    for (auto p : G[cent]) {
        int ch = p.first;
        if (kil[ch]) continue;
        go(ch);
    }
}

int main() {
    fastio();
    cin >> N >> K;
    ans = N;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    go(0);
    if (ans == N) ans = -1;
    cout << ans;
}
