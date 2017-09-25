/*

주의 사항
1. 노드 번호는 0번 부터 시작

*/

struct LCA{
	vector<vector<int> > G, par;
	vector<int> dep;
	int root, size, depLog;
	LCA(int size, int root){
		this->root = root;
		this->size = size;
		depLog = 1;
		int sz = 1;
		while(sz <= size) depLog++, sz *= 2;
		par = vector<vector<int> >(size, vector<int>(depLog + 1, -1));
		G = vector<vector<int> >(size);
		dep = vector<int>(size, 0);
	}
	void buildLCA(){
		dfs(root, -1);
	}
	void addEdge(int from, int to){
		G[from].push_back(to);
		G[to].push_back(from);
	}
	void dfs(int cur, int dad){
		for(int i = 1; (1<<i) <= dep[cur]; i++) par[cur][i] = par[par[cur][i-1]][i-1];
		for(int next : G[cur]){
			if(next == dad) continue;
			par[next][0] = cur;
			dep[next] = dep[cur] + 1;
			dfs(next, cur);
		}
	}
	int getLCA(int a, int b){
		if(dep[a] < dep[b]) swap(a, b);
		for(int i = 0; dep[a] != dep[b]; i++){
			int diff = dep[a] - dep[b];
			if(diff & (1<<i)) a = par[a][i];
		}
		for(int i = depLog; i >= 0; i--){
			if(par[a][i] == -1) continue;
			if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i]; 
		}
		if(a == b) return a;
		return par[a][0];
	}
};