struct Segtree{
	vector<ll> tree, lazy;
	int size;
	Segtree(vector<ll>& arr){
		int tmpSize = (int)arr.size();
		size = 1;
		while(size < tmpSize) size *= 2;
		tree = vector<ll>(2 * size, -infl);
		lazy = vector<ll>(2 * size, -infl);

		for(int i = 0 ; i < (int)arr.size(); i++) tree[size + i] = arr[i];
		for(int i = size - 1; i > 0; i--) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
	}
	ll query(int s, int e, int nl, int nr, int nd){
		updateLazy(nl, nr, nd);
		if(s <= nl && nr <= e) return tree[nd];
		if(e < nl || nr < s) return -infl;
		int nm = (nl + nr) / 2;
		ll leftRes = query(s, e, nl, nm, 2 * nd);
		ll rightRes = query(s, e, nm + 1, nr, 2 * nd + 1);
		return max(leftRes, rightRes);
	}
	ll update(int s, int e, int nl, int nr, ll val, int nd){
		updateLazy(nl, nr, nd);
		if(s <= nl && nr <= e) {
			lazy[nd] = max(lazy[nd], val);
			updateLazy(nl, nr, nd);
			return tree[nd];
		}
		if(e < nl || nr < s) return tree[nd];
		int nm = (nl + nr) / 2;
		ll leftRes = update(s, e, nl, nm, val, 2 * nd);
		ll rightRes = update(s, e, nm + 1, nr, val, 2 * nd + 1);
		return tree[nd] = max(leftRes, rightRes);
	}
	void updateLazy(int nl, int nr, int nd){
		if(lazy[nd] != -infl) {
            tree[nd] = max(tree[nd], lazy[nd]);
			if(nd < size) {
                lazy[2 * nd] = max(lazy[2 * nd], lazy[nd]);
                lazy[2 * nd + 1] = max(lazy[2 * nd + 1], lazy[nd]);
			}
			lazy[nd] = -infl;
		}
	}
	ll query(int s, int e){
		return query(s, e, 0, size - 1, 1);
	}
	ll update(int s, int e, ll val){
		return update(s, e, 0, size - 1, val, 1);
	}
};
