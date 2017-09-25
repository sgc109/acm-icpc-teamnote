struct Segtree{
	vector<ll> tree, lazy;
	int size;
	Segtree(vector<ll>& arr){
		int tmpSize = (int)arr.size();
		size = 1;
		while(size < tmpSize) size *= 2;
		tree = vector<ll>(2*size, 0);
		lazy = vector<ll>(2*size, 0);

		for(int i = 0 ; i < (int)arr.size(); i++) tree[size + i] = arr[i];
		for(int i = size - 1; i > 0; i--) tree[i] = tree[2*i] + tree[2*i + 1];
	}
	ll query(int s, int e, int nodeL, int nodeR, int node){
		updateLazy(nodeL, nodeR, node);
		if(s <= nodeL && nodeR <= e) return tree[node];
		if(e < nodeL || nodeR < s) return 0;
		int nodeM = (nodeL + nodeR) / 2;
		ll leftRes = query(s, e, nodeL, nodeM, 2*node);
		ll rightRes = query(s, e, nodeM + 1, nodeR, 2*node + 1);
		return leftRes + rightRes;
	}
	ll update(int s, int e, int nodeL, int nodeR, ll val, int node){
		updateLazy(nodeL, nodeR, node);
		if(s <= nodeL && nodeR <= e) {
			lazy[node] += val;
			updateLazy(nodeL, nodeR, node);
			return tree[node];
		}
		if(e < nodeL || nodeR < s) return tree[node];
		int nodeM = (nodeL + nodeR) / 2;
		ll leftRes = update(s, e, nodeL, nodeM, val, 2*node);
		ll rightRes = update(s, e, nodeM + 1, nodeR, val, 2*node + 1);
		return tree[node] = leftRes + rightRes;
	}
	void updateLazy(int nodeL, int nodeR, int node){
		if(lazy[node]) {
			tree[node] += (nodeR - nodeL + 1) * lazy[node];
			if(node < size) lazy[2*node] += lazy[node], lazy[2*node + 1] += lazy[node];
			lazy[node] = 0;
		}
	}
	ll query(int s, int e){
		return query(s, e, 0, size - 1, 1);
	}
	ll update(int s, int e, ll val){
		return update(s, e, 0, size - 1, val, 1);
	}
};