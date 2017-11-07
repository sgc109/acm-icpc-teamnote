/*
   새로운 소스와 싱크 s' 와 t' 를 만든다.

   새로운 유량 그래프에서 최대 유량을 구할 땐
   s' 가 소스가 되고 t'가 싱크가 된다.

   기존의 그래프의 각각의 노드 v에 대하여
   s' -> v 로 간선을 하나씩 이어주는데
   이 때의 용량은 v로 들어가는 모든 엣지들의
   demand 유량의 합이다.

   기존의 그래프의 각각의 노드 v에 대하여
   v -> t' 로 간선을 하나씩 이어주는데
   이 때의 용량은 v에서 나가는 모든 엣지들의
   demand 유량의 합이다.

   t -> s 로 무한대 용량의 간선을 만들어준다.

   기존의 모든 엣지들의 용량들에 대해 
   자신의 demand 유량만큼 빼준다.

   maximum-flow 돌린 후에
   각 간선에 흐르는 유량에 그 간선의 demand 유량을
   더하면 원래 그래프에서 실제로 흐르는 유량이 됨

   그리고 LR-circulation 이 feasible 한지 판별하는것은
   위와 같이 maximum-flow 를 돌린후 최대유량이
   모든 간선들의 demand 유량의 합과 같으면 feasible,
   다르면 unfeasible!
 */
struct Dinic{
	struct edge{
		int to, cap, rev;
	};
	int size, src, sink;
	vector<vector<edge> > G;
	vector<int> level, iter;
	Dinic(){}
	Dinic(int size, int src, int sink) {
		this->size = size;
		this->src = src;
		this->sink = sink;
		G = vector<vector<edge> >(size);
		level = vector<int>(size, -1);
		iter = vector<int>(size, 0);
	}
	void addEdge(int from, int to, int cap){
		G[from].push_back({to, cap, (int)G[to].size()});
		G[to].push_back({from, 0, (int)G[from].size()-1});
	}
	bool bfs(int src, int sink){
		queue<int> q;
		q.push(src);
		level[src] = 0;
		while(!q.empty() && level[sink] == -1){
			int here = q.front();
			q.pop();
			for(auto e : G[here]){
				if(e.cap <= 0 || level[e.to] != -1) continue;
				level[e.to] = level[here] + 1;
				q.push(e.to);
			}
		}
		return level[sink] != -1;
	}

	int dfs(int here, int minFlow, int sink){
		if(here == sink) return minFlow;
		for(int& i = iter[here]; i < (int)G[here].size(); i++){
			auto& e = G[here][i];
			if(e.cap == 0 || level[e.to] != level[here] + 1) continue;
			int f = dfs(e.to, min(minFlow, e.cap), sink);
			if(f > 0){
				e.cap -= f;
				G[e.to][e.rev].cap += f;
				return f;
			}
		}
		return 0;
	}
	
	int getMaxflow(){
		int ret = 0;
		while(1){
			level = vector<int>(size, -1);
			iter = vector<int>(size, 0);
			if(!bfs(src, sink)) break;
			while(int f = dfs(src, inf, sink)) ret += f;
		}
		return ret;
	}
};

struct LRMaxFlow{
	Dinic dinic;
	int size, src, sink, fsrc, fsink;
	vector<int> inSum, outSum;
	LRMaxFlow(int size, int src, int sink){
		this->size = size;
		this->src = src;
		this->sink = sink;
		fsrc = size;
		fsink = size + 1;
		dinic = Dinic(size + 2, fsrc, fsink);
		inSum = vector<int>(size, 0);
		outSum = vector<int>(size, 0);
	}
	void addEdge(int from, int to, int cap, int lower){
		dinic.addEdge(from, to, cap);
		inSum[to] += lower;
		outSum[from] += lower;
	}
	int getMaxflow(){
		for(int i = 0 ; i < size; i++) if(inSum[i]) dinic.addEdge(fsrc, i, inSum[i]);
		for(int i = 0 ; i < size; i++) if(outSum[i]) dinic.addEdge(i, fsink, outSum[i]);
		dinic.addEdge(sink, src, inf);
		return dinic.getMaxflow();
	}
};
