#include <bits/stdc++.h>
using namespace std;

int t[262145];
int A[250003];
int N,K;
int ans;

void update(int pos, int v){
	t[pos += (1<<16)] += v;
	for(;pos>1; pos/=2) t[pos/2] = t[pos] + t[pos^1];
}
int search(int k){
	int pos = 1;
	while(pos < (1<<16)){
		if(k <= t[2*pos]) pos*=2;
		else k-=t[2*pos], pos=2*pos+1;
	}
	return pos-(1<<16);
}

int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	cin >> N >> K;
	for(int i = 0 ; i < N; i++) cin >> A[i];
	for(int i = 0 ; i < K; i++) update(A[i],1);
	long long sum = 0;
	for(int i = K; i <= N; i++){
		sum += search((K+1)/2);
		if(i==N) break;
		update(A[i],1);
		update(A[i-K],-1);
	}
	cout << sum;
	return 0;
}
