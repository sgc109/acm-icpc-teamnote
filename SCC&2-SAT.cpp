/*

주의 사항
1. 그래프 구성해 주고나서 답 구하기 전에 build 먼저 해줘야함.
2. getAns 로 답구하는데 답 없으면 빈 벡터 반환
*/

struct SCC{
	vector<vector<int> > G;
	vector<int> sccId, order;
	int visitCnt, sccCnt, size;
	stack<int> stck;
	SCC(){}
	SCC(int size){
		this->size = size;
		G = vector<vector<int> >(size);
	}
	void buildSCC(){
		sccId = vector<int>(size, -1);
		order = vector<int>(size, -1);
		visitCnt = sccCnt = 0;
		for(int i = 0 ; i < size; i++) {
			if(order[i] == -1) dfs(i);
		}
		for(int i = 0 ; i < size; i++) sccId[i] = sccCnt - sccId[i] - 1;
	}
	void addEdge(int from, int to){
		G[from].push_back(to);
	}
	int dfs(int cur){
		stck.push(cur);
		int ret = order[cur] = visitCnt++;
		for(int next : G[cur]){
			if(order[next] == -1) ret = min(ret, dfs(next));
			else if(sccId[next] == -1) ret = min(ret, order[next]);
		}
		if(order[cur] == ret){
			while(1){
				int top = stck.top();
				stck.pop();
				sccId[top] = sccCnt;
				if(top == cur) break;
			}
			sccCnt++;
		}
		return ret;
	}
	vector<vector<int> > getCompGraph(){
		vector<vector<int> > compG = vector<vector<int> >(sccCnt);
		for(int cur = 0 ; cur < size; cur++){
			for(int next : G[cur]){
				if(sccId[cur] == sccId[next]) continue;
				compG[sccId[cur]].push_back(sccId[next]);
			}
		}
		sort(compG.begin(), compG.end());
		for(int i = 0; i < sccCnt; i++) {
			compG[i].erase(unique(compG[i].begin(), compG[i].end()), compG[i].end());
		}
		return compG;
	}
};
struct TwoSAT{
	int size;
	SCC scc;
	vector<int> ans;
	bool isPossible;
	TwoSAT(int size){
		this->size = size;
		scc = SCC(size);
	}
	void buildTwoSAT(){
		scc.buildSCC();
		vector<int> sccId = scc.sccId;
		isPossible = true;
		for(int i = 0 ; i < size; i+=2){
			if(sccId[i] == sccId[i+1]) isPossible = false;
		}
		ans = vector<int>(size / 2, -1);
		for(int i = 0; i < size; i += 2){
			ans[i / 2] = sccId[i] > sccId[i + 1];
		}
	}
	void addEdge(int from, int to){
		scc.addEdge(from, to);
	}
	vector<int> getAns(){
		if(!isPossible) return vector<int>();
		return ans;
	}
};
int NOT(int x){
	return x^1;
}
int TRANS(int x){
	if(x < 0) return NOT((-x-1)*2);
	return (x-1)*2;
}