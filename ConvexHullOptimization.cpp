#include <bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define fastio() ios::sync_with_stdio(0),cin.tie(0)
using namespace std;
typedef long long ll;

int N;
ll dp[100003];
ll A[100003],B[100003];
pair<ll, ll> stck[100003];
int size=0;
double cross(int a, int b){
	return (double)(stck[b].second - stck[a].second) / (stck[a].first - stck[b].first);
}
void insert(ll a, ll b){
	stck[size] = {a, b};
	while(size > 1 && cross(size - 2, size - 1) > cross(size - 1, size)){
		stck[size - 1] = stck[size];
		size--;
	}
	size++;
}
ll query(ll x){
	int i;
	for(i = 0; i < size - 1; i++){
		if(cross(i, i + 1) >= x) break;
	}
	return stck[i].first * x + stck[i].second;
}
int main() {
    fastio();
	cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) cin >> B[i];
	dp[1] = 0;
	insert(B[1], 0);
    for(int i = 2; i <= N; i++){
		dp[i] = query(A[i]);
		insert(B[i], dp[i]);
	}
	cout << dp[N];
	return 0;
}
