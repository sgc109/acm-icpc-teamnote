vector<int> getPartial(string& S){
	int len = (int)S.size();
	int matched = 0;
	vector<int> pi = vector<int>(len, 0);
	for(int i = 1 ; i < len; i++){
		while(matched > 0 && S[i] != S[matched]) matched = pi[matched - 1];
		if(S[i] == S[matched]) pi[i] = ++matched;
	}
	return pi;
}

vector<int> KMP(string& A, string& B){
	int matched = 0;
	int aLen = (int)A.size();
	int bLen = (int)B.size();
	vector<int> pi = getPartial(B);
	vector<int> found;
	for(int i = 0 ; i < aLen; i++) {
		while(matched > 0 && A[i] != B[matched]) matched = pi[matched - 1];
		if(A[i] == B[matched]) matched++;
		if(matched == bLen) found.push_back(i - matched + 1), matched = pi[matched - 1];
	}
	return found;
}