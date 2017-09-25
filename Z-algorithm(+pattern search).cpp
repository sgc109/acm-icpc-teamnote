struct Z{
	vector<int> za;
	Z(string S){
		int N = (int)S.size();
		za = vector<int>(N);
		int L = -1, R = -1;
		for(int i = 1; i < N; i++){
			if(i <= R){
				if(za[i - L] < R - i + 1) za[i] = za[i - L];
				else {
					L = i;
					while(R < N && S[R] == S[R - i]) R++;
					za[i] = R - L; R--;
				}
			}
			else {
				L = R = i;
				while(R < N && S[R] == S[R - i]) R++;
				za[i] = R - L; R--;
			}
		}
	}
};

vector<int> findPos(string& S, string& P){
	vector<int> ret;
	string S2 = P + '#' + S;
	Z z(S2);
	for(int i = 0 ; i < sz(S2); i++) if(z.za[i] == sz(P)) ret.pb(i - sz(P) - 1);
	return ret;
}