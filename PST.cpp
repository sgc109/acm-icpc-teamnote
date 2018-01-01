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

struct Node{
    Node *l, *r;
    int v;
    Node() :l(0), r(0), v(0){};
};
set<int> st;
vector<int> comp;
int w[100003];
int N, M;
vector<int> G[100003];
Node *tree[100003];
int par[100003][20];
int dep[100003];
Node *makeTree(int nl, int nr, int idx, Node *now){
    if(nr < idx || idx < nl) return now;
    Node *ret = new Node();
    if(nl == nr){
        ret->v = now->v + 1;
        return ret;
    }
    int nm = nl + nr >> 1;
    ret->l = makeTree(nl, nm, idx, now->l);
    ret->r = makeTree(nm + 1, nr, idx, now->r);
    ret->v = ret->l->v + ret->r->v;
    return ret;
}
int query(int nl, int nr, vector<Node *>& pv, int k){
    if(nl == nr) return nl;
    int sum = pv[0]->l->v + pv[1]->l->v - pv[2]->l->v - pv[3]->l->v;
    int nm = nl + nr >> 1;
    vector<Node *> npv;
    if(k > sum) {
        for(auto p : pv) npv.pb(p->r);
        return query(nm + 1, nr, npv, k - sum);
    }
    for(auto p : pv) npv.pb(p->l);
    return query(nl, nm, npv, k);
}
void dfs(int cur, int dad){
    int idx = lower_bound(all(comp), w[cur]) - comp.begin();
    tree[cur] = makeTree(0, sz(comp) - 1, idx, tree[dad]);
    for(int i = 1; i <= 17; i++) {
        par[cur][i] = par[par[cur][i - 1]][i - 1];
    }
    for(int nxt : G[cur]){
        if(nxt == dad) continue;
        par[nxt][0] = cur;
        dep[nxt] = dep[cur] + 1;
        dfs(nxt, cur);
    }
}
int lca(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 0; i <= 17; i++) {
        if((dep[v] - dep[u]) & (1 << i)) v = par[v][i];
    }
    if(u == v) return u;
    for(int i = 17; i >= 0; i--){
        if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    }
    return par[u][0];
}
int main(){
    fastio();
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> w[i];
        st.insert(w[i]);
    }
    comp.assign(all(st));
    for(int i = 0; i < N - 1; i++){
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }
    tree[0] = new Node();
    tree[0]->l = tree[0];
    tree[0]->r = tree[0];
    dfs(1, 0);
    while(M--){
        int u, v, k;
        cin >> u >> v >> k;
        int l = lca(u, v);
        vector<Node *> pv;
        pv.pb(tree[u]);
        pv.pb(tree[v]);
        pv.pb(tree[l]);
        pv.pb(tree[par[l][0]]);
        int idx = query(0, sz(comp) - 1, pv, k);
        cout << comp[idx] << '\n';
    }
}
