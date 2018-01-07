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

struct Query{
    int l, r, id, lca;
} query[100003];
int N, M;
int kind;
int cnt[1000003];
int dep[100003];
int par[100003][20];
int A[100003];
int S[100003], E[100003];
int cnt_node[100003];
vector<int> G[100003];
vector<int> v;
int ans[100003];
void add(int x){
    if(++cnt[x] == 1) kind++;
}
void erase(int x){
    if(--cnt[x] == 0) kind--;
}
void node_add(int id){
    cnt_node[id]++;
    if(cnt_node[id] == 2) erase(A[id]);
    else if(cnt_node[id] == 1) add(A[id]);
}
void node_erase(int id){
    cnt_node[id]--;
    if(cnt_node[id] == 1) add(A[id]);
    else if(cnt_node[id] == 0) erase(A[id]);
}
void dfs(int cur, int dad){
    S[cur] = sz(v);
    v.pb(cur);
    for(int i = 1; i < 20; i++){
        par[cur][i] = par[par[cur][i - 1]][i - 1];
    }
    for(int nxt : G[cur]){
        if(nxt == dad) continue;
        dep[nxt] = dep[cur] + 1;
        par[nxt][0] = cur;
        dfs(nxt, cur);
    }
    E[cur] = sz(v);
    v.pb(cur);
}
int lca(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i--){
        if((dep[v] - dep[u]) & (1 << i)) v = par[v][i];
    }
    if(u == v) return u;
    for(int i = 19; i >= 0; i--){
        if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    }
    return par[u][0];
}
int main(){
    fastio();
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(0, -1);
    cin >> M;
    for(int i = 0; i < M; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        if(S[u] > S[v]) swap(u, v);
        int p = lca(u, v);
        if(p == u){
            query[i] = Query{S[u], S[v], i, -1};
        }
        else {
            query[i] = Query{E[u], S[v], i, p};
        }
    }
    int sqr = sqrt(sz(v));
    auto srt = [&](Query& a, Query& b){
        int ga = a.r / sqr;
        int gb = b.r / sqr;
        return ga == gb ? a.l < b.l : ga < gb;
    };
    sort(query, query + M, srt);
    int cl = 0, cr = 0;
    node_add(v[0]);
    for(int i = 0; i < M; i++){
        int l = query[i].l;
        int r = query[i].r;
        int p = query[i].lca;
        for(int j = cl - 1; j >= l; j--) node_add(v[j]);
        for(int j = cr + 1; j <= r; j++) node_add(v[j]);
        for(int j = cl; j < l; j++) node_erase(v[j]);
        for(int j = cr; j > r; j--) node_erase(v[j]);
        if(p != -1) add(A[p]);
        ans[query[i].id] = kind;
        if(p != -1) erase(A[p]);
        cl = l, cr = r;
    }
    for(int i = 0; i < M; i++) cout << ans[i] << '\n';
}
