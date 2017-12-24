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
int acc; // 노드 순서 부여할 때 쓰는 누적변수
vector<vector<pair<int, pair<int,int> > > > G; // 그래프
vector<int> cnts; // 서브 트리 노드 수
vector<int> dep; // 루트와의 거리
vector<int> ords; // 노드 방문 순서
vector<int> grp; // 노드가 속한 체인
vector<int> segId; // 각 체인의 간선들의 정보를 담은 세그트리 id
vector<Segtree> segs; // 세그트리들
vector<int> tail; // 체인의 끝 노드
vector<ll> parW; // 각 노드마다 자신의 부모를 잇는 간선의 가중치
vector<int> par;
vector<int> edg2nd; // 에지 번호를 받으면 (0을 루트로 했을 때) 자식인 노드 번호를 반환(문제에서 에지 번호로 업데이트 할 때만 필요)

void dfs(int cur, int dad){
    cnts[cur] = 1;
    for(auto p : G[cur]){
        int nxt = p.first;
        int idx = p.second.second;
        if(nxt == dad) continue;
        dep[nxt] = dep[cur] + 1;
        edg2nd[idx] = nxt;
        par[nxt] = cur;
        dfs(nxt, cur);
        cnts[cur] += cnts[nxt];
    }
}

void initChain(int cur, int dad, int grpId){
    tail[grpId] = acc;
    grp[acc] = grpId;
    ords[cur] = acc++;
    int idx = -1;
    int w;
    for(auto p : G[cur]){
        int nxt = p.first;
        int cst = p.second.first;
        if(nxt == dad) continue;
        if(idx == -1 || cnts[idx] < cnts[nxt]) idx = nxt, w = cst;
    }
    if(idx != -1) {
        parW[acc] = w; // 나중에 세그트리 구성할 때 각 노드의 ords 들을 순회하며 가중치를 넣어야 하므로 백업해둬야함
        initChain(idx, cur, grpId);
    }
    for(auto p : G[cur]){
        int nxt = p.first;
        int cst = p.second.first;
        if(nxt == dad || nxt == idx) continue;
        parW[acc] = cst;
        initChain(nxt, cur, nxt); // 그룹의 시작 노드 = 그룹의 번호 가 되도록 설계했다.
    }
    int g = grp[ords[cur]];
    assert((tail[g] == ords[cur]) == (idx == -1)); // 그룹의 끝부분인지 판별하는 두 식이 같은지 체크(좀 더 짧은 걸로 하려고)
    if(idx == -1){ // 현재 노드가 그룹의 끝부분이라면 세그트리 만들어준다.
        vector<ll> tvec;
        for(int i = ords[g]; i <= tail[g]; i++){
            tvec.pb(parW[i]);
        }
        segId[g] = sz(segs);
        Segtree seg(tvec); 
        segs.pb(seg);
    }
}

void init(){
    dfs(0, -1);
    initChain(0, -1, 0);
}

ll query(int u, int v){ // 루트노드는 par 가 0 이기 때문에 이 때 따로 처리해줘야할수도!
    ll ret = -infl;
    while(1){
        int hu = grp[ords[u]];
        int hv = grp[ords[v]];
        if(hu == hv) break; // 같은 체인에 속하면
        if(dep[hu] < dep[hv]){
            ret = max(ret, segs[segId[hv]].query(0, ords[v] - ords[hv]));
            v = par[hv];
        }
        else {
            ret = max(ret, segs[segId[hu]].query(0, ords[u] - ords[hu]));
            u = par[hu];
        }
    }
    if(u == v) return ret;
    if(dep[u] > dep[v]) swap(u, v);
    int g = grp[ords[u]];
    int l = ords[u] - g + 1;
    int r = ords[v] - g;
    ret = max(ret, segs[segId[g]].query(l, r));

    return ret;
}
void update(int id, ll val){
    int nd = ords[edg2nd[id]];
    int g = grp[nd];
    int idx = nd - ords[g];
    segs[segId[g]].update(idx, val);
}
int main(){
    fastio();
    cin >> N;
    G = vector<vector<pair<int, pair<int,int> > > >(N, vector<pair<int, pair<int,int> > >());
    cnts = vector<int>(N);
    dep = vector<int>(N);
    ords = vector<int>(N);
    grp = vector<int>(N);
    segId = vector<int>(N);
    tail = vector<int>(N);
    par = vector<int>(N);
    parW = vector<ll>(N);
    edg2nd = vector<int>(N);
    for(int i = 0; i < N - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].pb({v, {w, i}});
        G[v].pb({u, {w, i}});
    }
    init();
    cin >> M;
    for(int i = 0; i < M; i++){
        int o;
        cin >> o;
        if(o == 1){
            int id;
            ll w;
            cin >> id >> w;
            id--;
            update(id, w);
        }
        else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << query(u, v) << '\n';
        }
    }
}
