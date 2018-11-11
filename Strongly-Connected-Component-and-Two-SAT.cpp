/*
주의 사항
1. 생성자에서 size 는 참/거짓을 알고 싶은 변수의 개수를 넣어줘야하며
   addEdge 를 할 때에도 구조체 밖에서 먼저 노드 id에 2배를 해주고 NOT을 해준 뒤에
   인자로 넣어줘야함
2. 2-CNF 식에 따라 addEdge 로 간선 이어줄 때, 각 절 마다 직접 대칭적으로 2개씩 이어줘야함.
   즉, a -> b 를 이으면 무조건 그의 대우인 ~b -> ~a 도 이어줘야 한다는 뜻
3. 그래프 구성해 주고나서 답 구하기 전에 build 먼저 해줘야함.
4. getAns 로 답구하는데 답 없으면 빈 벡터 반환
5. getCompGraph 는 scc 노드 압축이 필요한 경우가 아니라면 안써도 됨
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
		for(int nxt : G[cur]){
			if(order[nxt] == -1) ret = min(ret, dfs(nxt));
			else if(sccId[nxt] == -1) ret = min(ret, order[nxt]);
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
    // 노드 압축이므로 필요하지 않을 경우 안써도 됨
	vector<vector<int> > getCompGraph(){
		vector<vector<int> > compG = vector<vector<int> >(sccCnt);
		for(int cur = 0 ; cur < size; cur++){
			for(int nxt : G[cur]){
				if(sccId[cur] == sccId[nxt]) continue;
				compG[sccId[cur]].push_back(sccId[nxt]);
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
	bool isPoss;
	TwoSAT(int size){
        size *= 2;
		this->size = size;
		scc = SCC(size);
	}
	void buildTwoSAT(){
		scc.buildSCC();
		vector<int> sccId = scc.sccId;
		isPoss = true;
		for(int i = 0 ; i < size; i+=2){
			if(sccId[i] == sccId[i+1]) isPoss = false;
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
		if(!isPoss) return vector<int>();
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
