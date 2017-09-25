void countingSort(vector<int>& SA, vector<int>& g, int t){
	int n = sz(SA);
	vector<int> tSA(n), c(max(330, n + 1), 0);
	for(int i = 0 ; i < n; i++) c[i + t < n ? g[i + t] : 0]++;
	for(int i = 0, sum = 0, tmp ; i < max(330, n + 1); tmp = c[i], c[i] = sum, sum += tmp, i++);
	for(int i = 0 ; i < n; i++) tSA[c[SA[i] + t < n ? g[SA[i] + t] : 0]++] = SA[i];
	SA = tSA;
}

vector<int> getSA(string& S){
	int n = (int)S.size();
	vector<int> SA(n), g(n + 1), tg(n + 1);

	for(int i = 0 ; i < n; i++) SA[i] = i;
	for(int i = 0 ; i < n; i++) g[i] = S[i];
	
	for(int t = 1; t < n; t*=2){
		g[n] = 0;
		countingSort(SA, g, t);
		countingSort(SA, g, 0);
		tg[SA[0]] = 1;
		for(int i = 1 ; i < n; i++) {
			int bigger = g[SA[i - 1]] < g[SA[i]] || g[SA[i - 1] + t] < g[SA[i] + t];
			tg[SA[i]] = tg[SA[i-1]] + bigger;
		}
		g = tg;
	}
	return SA;
}

vector<int> getLCP(string& S, vector<int>& SA){
	int n = (int)S.size();	
	vector<int> LCP(n), rank(n);
	for(int i = 0 ; i < n; i++) rank[SA[i]] = i;
	int k = 0;
	for(int i = 0 ; i < n; i++){
		if(k > 0) k--;
		if(!rank[i]) continue;
		int j = SA[rank[i]-1];
		while(i+k < n && j+k < n && S[i+k] == S[j+k]) k++;
		LCP[rank[i]] = k;
	}
	return LCP;
}