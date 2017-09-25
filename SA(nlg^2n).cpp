vector<int> getSA(string& S){
	int n = (int)S.size();
	vector<int> SA(n), g(n+1), tg(n+1);

	for(int i = 0 ; i < n; i++) SA[i] = i;
	for(int i = 0 ; i < n; i++) g[i] = S[i];
	
	for(int t = 1; t < n; t*=2){
		g[n] = -1;
		auto cmp = [&](int a, int b)->bool{
            if(g[a] == g[b]) return g[a+t] < g[b+t];
            return g[a] < g[b];
        };
		sort(SA.begin(), SA.end(), cmp);

		tg[SA[0]] = 0;
		for(int i = 1 ; i < n; i++) {
			tg[SA[i]] = tg[SA[i-1]] + cmp(SA[i-1], SA[i]);
		}
		g = tg;
	}
	return SA;
}