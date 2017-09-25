#include <bits/stdc++.h>
#define fastio() ios_base::sync_with_stdio(false),cin.tie(NULL)

using namespace std;
typedef long long ll;
const int INF = 0x3c3c3c3c;
const long long INFL = 0x3c3c3c3c3c3c3c3c;
const int base = 257;
ll mod[2] = {(ll)1e9+9999, (ll)1e9+99999};
ll poww[2];
int main() {
	fastio();

	string A, B;
	getline(cin, A);
	getline(cin, B);

	int aLen = (int)A.size();
	int bLen = (int)B.size();

	for(int k = 0 ; k < 2; k++){
		poww[k] = 1;
		for(int i = 0 ; i < bLen - 1; i++) {
			poww[k] = (poww[k] * base) % mod[k];
		}
	}

	ll h[2] = {0, 0};
	for(int k = 0 ; k < 2; k++) {
		for(int i = 0 ; i < bLen; i++) {
			h[k] = (h[k] * base + B[i]) % mod[k];
		}
	}

	ll acc[2] = {0, 0};
	for(int k = 0 ; k < 2; k++){
		for(int i = 0 ; i < bLen; i++){
			acc[k] = (acc[k] * base + A[i]) % mod[k];
		}
	}

	vector<int> ans;

	for(int i = bLen; i <= aLen; i++){
		if(acc[0] == h[0] && acc[1] == h[1]) ans.push_back(i - bLen);
		if(i == aLen) break;
		for(int k = 0 ; k < 2; k++){
			acc[k] = (acc[k] - A[i - bLen] * poww[k] + base * mod[k]) % mod[k];
			acc[k] = (acc[k] * base + A[i]) % mod[k];
		}
	}

	printf("%d\n", (int)ans.size());
	for(int a : ans) printf("%d\n", a+1);


	return 0;
}