int N,M;
int A[8003];
ll pSum[8003];
ll D[803][8003];
int K[803][8003];
ll C(int l, int r){
	return (pSum[r] - pSum[l - 1]) * (r - l + 1);
}
void DC(int i, int l, int r, int p, int q){
	if(l > r) return;
	int mid = (l + r) >> 1;
	D[i][mid] = infl;
	for(int k = p; k <= q && k < mid; k++){
		if(D[i][mid] > D[i - 1][k] + C(k + 1, mid)) D[i][mid] = D[i - 1][k] + C(k + 1, mid),K[i][mid] = k;
	}
	DC(i, l, mid - 1, p, K[i][mid]);
	DC(i, mid + 1, r, K[i][mid], q);
}
int main() {
	memset(D,0x3c,sizeof(D));
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        pSum[i] = pSum[i - 1] + A[i];
    }

	if(N<=M) return !printf("%lld", pSum[N]);

	D[0][0] = 0;
    for(int i = 1; i <= M; i++) DC(i, 1, N, 0, N - 1);
    cout << D[M][N];

	return 0;
}
