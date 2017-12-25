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

struct Segtree{
	vector<ll> tree;
    int cnt;
	int size;
	Segtree(vector<ll>& arr){
		int tmpSize = (int)arr.size();
        cnt = tmpSize;
		size = 1;
		while(size < tmpSize) size *= 2;
		tree = vector<ll>(2 * size, -infl);

		for(int i = 0 ; i < (int)arr.size(); i++) tree[size + i] = arr[i];
		for(int i = size - 1; i > 0; i--) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	ll query(int s, int e, int nl, int nr, int nd){
		if(s <= nl && nr <= e) return tree[nd];
		if(e < nl || nr < s) return -infl;
		int nm = (nl + nr) / 2;
		ll leftRes = query(s, e, nl, nm, 2 * nd);
		ll rightRes = query(s, e, nm + 1, nr, 2 * nd + 1);
		return max(leftRes, rightRes);
	}
	ll update(int pos, int nl, int nr, ll val, int nd){
		if(pos <= nl && nr <= pos) return tree[nd] = val;
		if(pos < nl || nr < pos) return tree[nd];
		int nm = (nl + nr) / 2;
		ll leftRes = update(pos, nl, nm, val, 2 * nd);
		ll rightRes = update(pos, nm + 1, nr, val, 2 * nd + 1);
		return tree[nd] = max(leftRes, rightRes);
	}
	ll query(int s, int e){
		return query(s, e, 0, size - 1, 1);
	}
	ll update(int pos, ll val){
		return update(pos, 0, size - 1, val, 1);
	}
};

int N; // 노드의 개수
int M; // 간선의 개수
vector<vector<pair<int,int> > > G; // 그래프
vector<int> cnts; // 서브 트리 노드 수
vector<int> dep; // 루트와의 거리
vector<vector<int> > chain; // 각 노드들을 그룹으로 묶어준 2차원 벡터
vector<int> grpId; // 노드가 속한 체인
vector<Segtree> segs; // 세그트리들
vector<ll> parW; // 각 노드마다 자신의 부모를 잇는 간선의 가중치
vector<int> par;
vector<pair<int,int> > edges;

void dfs(int cur, int dad){
    cnts[cur] = 1;
    for(auto p : G[cur]){
        int nxt = p.first;
        int cst = p.second;
        if(nxt == dad) continue;
        dep[nxt] = dep[cur] + 1;
        par[nxt] = cur;
        parW[nxt] = cst;
        dfs(nxt, cur);
        cnts[cur] += cnts[nxt];
    }
}

void initChain(int cur, int dad){
    grpId[cur] = sz(chain) - 1;
    chain.back().pb(cur);
    int idx = -1;
    int w;
    for(auto p : G[cur]){
        int nxt = p.first;
        int cst = p.second;
        if(nxt == dad) continue;
        if(idx == -1 || cnts[idx] < cnts[nxt]) idx = nxt, w = cst;
    }
    if(idx != -1) {
        initChain(idx, cur);
    }
    for(auto p : G[cur]){
        int nxt = p.first;
        int cst = p.second;
        if(nxt == dad || nxt == idx) continue;
        chain.emplace_back();
        initChain(nxt, cur); // 그룹의 시작 노드 = 그룹의 번호 가 되도록 설계했다.
    }
}


ll query(int u, int v){ // 루트노드는 par 가 0 이기 때문에 이 때 따로 처리해줘야할수도!
    ll ret = 0;
    while(1){
        int hu = chain[grpId[u]][0];
        int hv = chain[grpId[v]][0];
        if(hu == hv) break; // 같은 체인에 속하면
        if(dep[hu] < dep[hv]){
            ret = max(ret, segs[grpId[hv]].query(0, dep[v] - dep[hv]));
            v = par[hv];
        }
        else {
            ret = max(ret, segs[grpId[hu]].query(0, dep[u] - dep[hu]));
            u = par[hu];
        }
    }
    if(u == v) return ret;
    if(dep[u] > dep[v]) swap(u, v);
    int depHead = dep[chain[grpId[u]][0]];
    int l = dep[u] - depHead + 1;
    int r = dep[v] - depHead;
    ret = max(ret, segs[grpId[u]].query(l, r));

    return ret;
}
void update(int id, ll val){
    int depHead = dep[chain[grpId[id]][0]];
    int idx = dep[id] - depHead;
    segs[grpId[id]].update(idx, val);
}
int main(){
    //fastio();
    cin >> N;
    G = vector<vector<pair<int,int> > >(N, vector<pair<int,int> >());
    cnts = vector<int>(N);
    dep = vector<int>(N);
    grpId = vector<int>(N);
    par = vector<int>(N);
    parW = vector<ll>(N);
    for(int i = 0; i < N - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].pb({v, w});
        G[v].pb({u, w});
        edges.pb({u, v});
    }
    dfs(0, -1);
    chain.emplace_back();
    initChain(0, -1);
    for(auto v : chain){
        vector<ll> tvec;
        for(int nd : v) tvec.pb(parW[nd]);
        Segtree seg = Segtree(tvec);
        segs.pb(seg);
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        int o, u, v, id;
        ll w;
        cin >> o;
        if(o == 1){
            cin >> id >> w;
            id--;
            auto e = edges[id];
            u = e.first, v = e.second;
            if(dep[u] > dep[v]) swap(u, v);
            update(v, w);
        }
        else {
            cin >> u >> v;
            u--, v--;
            cout << query(u, v) << '\n';
        }
    }
}
