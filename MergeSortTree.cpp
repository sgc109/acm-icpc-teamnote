/*
   Time Complexity : O(Nlg^3Q)
*/
struct MergeSortTree{
    int N;
    int LOW = -1e9 - 3, HIGH = 1e9 + 3;
    vector<vector<int> > tree;
    MergeSortTree(vector<int>& v){
        N = sz(v);
        tree = vector<vector<int> >(4 * N, vector<int>());
        init(0, N - 1, 1, v);
    }
    void init(int nl, int nr, int nd, vector<int>& v){
        if(nl == nr){
            tree[nd].pb(v[nl]);
            return;
        }
        int nm = nl + nr >> 1;
        init(nl, nm, 2 * nd, v);
        init(nm + 1, nr, 2 * nd + 1, v);
        auto& lt = tree[2 * nd];
        auto& rt = tree[2 * nd + 1];
        tree[nd].resize(sz(lt) + sz(rt));
        merge(all(lt), all(rt), tree[nd].begin());
    }
    int query(int nl, int nr, int l, int r, int nd, int x){
        if(r < nl || nr < l) return 0;
        if(l <= nl && nr <= r) return upper_bound(all(tree[nd]), x) - tree[nd].begin();
        int nm = nl + nr >> 1;
        return query(nl, nm, l, r, 2 * nd, x) + query(nm + 1, nr, l, r, 2 * nd + 1, x);
    }
    int query(int l, int r, int k){
        int lo = LOW, hi = HIGH;
        while(lo < hi){
            int mid = lo + hi >> 1;
            int cnt = query(0, N - 1, l, r, 1, mid);
            if(cnt < k) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};
