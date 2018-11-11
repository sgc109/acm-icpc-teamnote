#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define fastio() ios_base::sync_with_stdio(false),cin.tie(NULL)
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int inf = 0x3c3c3c3c;
const long long infl = 0x3c3c3c3c3c3c3c3c;

struct query{
	int l, r, a;
};
int N, M, K;
ll tr[300003];
int lo[300003], hi[300003];
int need[300003];
query Q[300003];
vector<int> qry[300003];
vector<int> terr[300003];
void update(int pos, int val){
	while(pos <= M){
		tr[pos] += val;
		pos += pos & -pos;
	}
}
ll query(int pos){
	ll ret = 0;
	while(pos > 0){
		ret += tr[pos];
		pos -= pos & -pos;
	}
	return ret;
}

int main() {
	fastio();
	cin >> N >> M;
	for(int i = 1 ; i <= M; i++){
		int a;
		cin >> a;
		terr[a].pb(i);
	}
	for(int i = 1 ; i <= N; i++) cin >> need[i];
	cin >> K;
	for(int i = 1 ; i <= K; i++){
		int l, r, a;
		cin >> l >> r >> a;
		Q[i] = {l, r, a};
	}
	for(int i = 1; i <= N; i++) lo[i] = 1, hi[i] = K + 1;
	while(1){
		int isEnd = 1;
		for(int i = 1 ; i <= N; i++) {
			if(lo[i] < hi[i]) {
				isEnd = 0;
				int mid = (lo[i] + hi[i]) / 2;
				qry[mid].pb(i);
			}
		}
		if(isEnd) break;
		memset(tr,0,sizeof(tr));
		for(int i = 1; i <= K; i++){
			auto q = Q[i];
			if(q.l > q.r) {
				update(q.l, q.a);
				update(1, q.a);
				update(q.r + 1, -q.a);
			}
			else{
				update(q.l, q.a);
				update(q.r + 1, -q.a);
			}
			while(sz(qry[i])){
				int id = qry[i].back();
				qry[i].pop_back();
				ll sum = 0;
				for(int nd : terr[id]) {
					sum += query(nd);
					if(sum >= need[id]) break;
				}
				if(sum >= need[id]) hi[id] = i;
				else lo[id] = i + 1;
			}
		}
	}
	for(int i = 1; i <= N; i++) {
		if(lo[i] == K + 1) cout << "NIE\n";
		else cout << lo[i] << '\n';
	}
	return 0;
}
