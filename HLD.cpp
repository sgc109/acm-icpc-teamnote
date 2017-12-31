/*
   1. 노드의 개수로 생성자 호출
   2. addEdge 로 트리 구성
   3. 쿼리나 업뎃하기 전 꼭 init() 호출해서 초기화
*/
struct HLD{
    struct Segtree{
        vector<int> tree;
        int size;
        Segtree(vector<int>& v){
            for(size = 1; size < sz(v); size *= 2);
            tree = vector<int>(2 * size, -inf);
            for(int i = 0; i < sz(v); i++) tree[size + i] = v[i];
            for(int i = size - 1; i >= 1; i--) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
        void update(int pos, int val){
            for(tree[pos += size] = val; pos > 1; pos /= 2){
                tree[pos / 2] = max(tree[pos], tree[pos ^ 1]);
            }
        }
        int query(int l, int r){
            int ret = 0;
            for(l += size, r += size; l <= r; l /= 2, r /= 2){
                if(l & 1) ret = max(ret, tree[l++]);
                if(~r & 1) ret = max(ret, tree[r--]);
            }
            return ret;
        }
    };
    int N;
    vector<vector<pair<int,int> > > G;
    vector<int> cnts, dep, grpId, parW, par;
    vector<vector<int> > grp;
    vector<Segtree> segs;
    HLD(int size) : N(size){
        G = vector<vector<pair<int,int> > >(N, vector<pair<int,int> >());
        cnts = vector<int>(N);
        dep = vector<int>(N);
        grpId = vector<int>(N);
        par = vector<int>(N);
        parW = vector<int>(N);
    }
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
        grpId[cur] = sz(grp) - 1;
        grp.back().pb(cur);
        int idx = -1, w;
        for(auto p : G[cur]){
            int nxt = p.first;
            int cst = p.second;
            if(nxt == dad) continue;
            if(cnts[nxt] * 2 >= cnts[cur]) idx = nxt, w = cst;
        }
        if(idx != -1) {
            initChain(idx, cur);
        }
        for(auto p : G[cur]){
            int nxt = p.first;
            int cst = p.second;
            if(nxt == dad || nxt == idx) continue;
            grp.emplace_back();
            initChain(nxt, cur);
        }
    }

    int query(int u, int v){
        int hu = grp[grpId[u]][0];
        int hv = grp[grpId[v]][0];
        if(hu == hv){
            if(u == v) return -inf;
            if(dep[u] > dep[v]) swap(u, v), swap(hu, hv);
            return segs[grpId[v]].query(dep[u] - dep[hv] + 1, dep[v] - dep[hv]);
        }
        if(dep[hu] > dep[hv]) swap(u, v), swap(hu, hv);
        return max(query(u, par[hv]), segs[grpId[v]].query(0, dep[v] - dep[hv]));
    }

    void update(int id, int val){
        int depHead = dep[grp[grpId[id]][0]];
        int idx = dep[id] - depHead;
        segs[grpId[id]].update(idx, val);
    }

    void addEdge(int u, int v, int w){
        G[u].pb({v, w});
        G[v].pb({u, w});
    }

    void init(){
        dfs(0, -1);
        grp.emplace_back();
        initChain(0, -1);
        for(auto v : grp){
            vector<int> tvec;
            for(int nd : v) tvec.pb(parW[nd]);
            Segtree seg = Segtree(tvec);
            segs.pb(seg);
        }
    }
};

vector<pair<int,int> > edges;

int main(){
    fastio();
    int N, M;
    cin >> N;
    HLD hld(N);
    for(int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        hld.addEdge(u, v, w);
        edges.pb({u, v});
    }
    hld.init();
    cin >> M;
    for(int i = 0; i < M; i++){
        int o, u, v, id;
        int w;
        cin >> o;
        if(o == 1){
            cin >> id >> w;
            id--;
            auto e = edges[id];
            u = e.first, v = e.second;
            if(hld.dep[u] > hld.dep[v]) swap(u, v);
            hld.update(v, w);
        }
        else {
            cin >> u >> v;
            u--, v--;
            cout << hld.query(u, v) << '\n';
        }
    }
}
