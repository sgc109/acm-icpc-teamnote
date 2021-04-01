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

int LOW = 0, HIGH = 1e6 + 3;

struct HLD {
    struct MergeSortTree {
        int N;
        vector <vector<int>> tree;

        MergeSortTree(vector<int> &v) {
            N = sz(v);
            tree = vector < vector < int > > (4 * N, vector<int>());
            init(0, N - 1, 1, v);
        }

        void init(int nl, int nr, int nd, vector<int> &v) {
            if (nl == nr) {
                tree[nd].pb(v[nl]);
                return;
            }
            int nm = nl + nr >> 1;
            init(nl, nm, 2 * nd, v);
            init(nm + 1, nr, 2 * nd + 1, v);
            auto &lt = tree[2 * nd];
            auto &rt = tree[2 * nd + 1];
            int pos1 = 0, pos2 = 0;
            while (pos1 < sz(lt) && pos2 < sz(rt)) {
                if (lt[pos1] < rt[pos2]) tree[nd].pb(lt[pos1++]);
                else tree[nd].pb(rt[pos2++]);
            }
            while (pos1 < sz(lt)) tree[nd].pb(lt[pos1++]);
            while (pos2 < sz(rt)) tree[nd].pb(rt[pos2++]);
        }

        int query(int nl, int nr, int l, int r, int nd, int x) {
            if (r < nl || nr < l) return 0;
            if (l <= nl && nr <= r) return upper_bound(all(tree[nd]), x) - tree[nd].begin();
            int nm = nl + nr >> 1;
            return query(nl, nm, l, r, 2 * nd, x) + query(nm + 1, nr, l, r, 2 * nd + 1, x);
        }

        int query(int l, int r, int x) {
            return query(0, N - 1, l, r, 1, x);
        }
    };

    int N;
    vector <vector<int>> G;
    vector<int> accs, dep, grpId, par, cnts;
    vector <vector<int>> grp;
    vector <MergeSortTree> trees;

    HLD(vector<int> &v) {
        N = sz(v);
        G = vector < vector < int > > (N, vector<int>());
        accs = vector<int>(N);
        cnts = vector<int>(N);
        dep = vector<int>(N);
        grpId = vector<int>(N);
        par = vector<int>(N);
        for (int i = 0; i < N; i++) cnts[i] = v[i];
    }

    void dfs(int cur, int dad) {
        accs[cur] = 1;
        for (int nxt : G[cur]) {
            if (nxt == dad) continue;
            dep[nxt] = dep[cur] + 1;
            par[nxt] = cur;
            dfs(nxt, cur);
            accs[cur] += accs[nxt];
        }
    }

    void initChain(int cur, int dad) {
        grpId[cur] = sz(grp) - 1;
        grp.back().pb(cur);
        int idx = -1, w;
        for (int nxt : G[cur]) {
            if (nxt == dad) continue;
            if (accs[nxt] * 2 >= accs[cur]) idx = nxt;
        }
        if (idx != -1) {
            initChain(idx, cur);
        }
        for (int nxt : G[cur]) {
            if (nxt == dad || nxt == idx) continue;
            grp.emplace_back();
            initChain(nxt, cur);
        }
    }

    int query(int u, int v, int x) {
        int hu = grp[grpId[u]][0];
        int hv = grp[grpId[v]][0];
        if (hu == hv) {
            if (dep[u] > dep[v]) swap(u, v), swap(hu, hv);
            return trees[grpId[v]].query(dep[u] - dep[hv], dep[v] - dep[hv], x);
        }
        if (dep[hu] > dep[hv]) swap(u, v), swap(hu, hv);
        return query(u, par[hv], x) + trees[grpId[v]].query(0, dep[v] - dep[hv], x);
    }

    int hld_query(int u, int v, int k) {
        int lo = LOW, hi = HIGH;
        while (lo < hi) {
            int mid = lo + hi >> 1;
            int cnt = query(u, v, mid);
            if (cnt < k) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    void addEdge(int u, int v) {
        G[u].pb(v);
        G[v].pb(u);
    }

    void init() {
        dfs(0, -1);
        grp.emplace_back();
        initChain(0, -1);
        for (auto v : grp) {
            vector<int> tvec;
            for (int num : v) tvec.pb(cnts[num]);
            MergeSortTree tree = MergeSortTree(tvec);
            trees.pb(tree);
        }
    }
};

int N, M;

int main() {
    fastio();
    cin >> N;
    vector<int> v;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        v.pb(a);
    }
    HLD hld(v);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        hld.addEdge(u, v);
    }
    hld.init();
    cin >> M;
    while (M--) {
        int u, v, k;
        cin >> u >> v >> k;
        u--, v--;
        cout << hld.hld_query(u, v, k) << '\n';
    }
}
