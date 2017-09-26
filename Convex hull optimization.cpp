#include <bits/stdc++.h>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,n) for(int i=0;i<n;++i)
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define inp1(a) scanf("%d",&a)
#define inp2(a,b) scanf("%d%d",&a,&b)
#define inp3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define inp4(a,b,c,d) scanf("%d%d%d%d",&a,&b,&c,&d)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pair<int,int> > vii;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > piii;
const double EPSILON = 1e-9;
const double PI = acos(0.0)*2;
const int MOD = 1000000007;
const int INF = 0x3c3c3c3c;
const long long INFL = 0x3c3c3c3c3c3c3c3c;
const int MAX_N = 102;

int N;
ll dp[100003];
ll A[100003],B[100003];
pll stck[100003];
int size=0;
double cross(int a, int b){
	return (double)(stck[b].second-stck[a].second)/(stck[a].first-stck[b].first);
}
void insert(ll a, ll b){
	stck[size]={a,b};
	while(size>1&&cross(size-2,size-1)>cross(size-1,size)){
		stck[size-1]=stck[size];
		size--;
	}
	size++;
}
ll query(ll x){
	int i;
	for(i=0;i<size-1;i++){
		if(cross(i,i+1)>=x) break;
	}
	return stck[i].first*x+stck[i].second;
}
int main() {
	ios_::sync_with_stdio(false);
	cin >> N;
	REP(i,1,N) cin >> A[i];
	REP(i,1,N) cin >> B[i]
	dp[1]=0;
	insert(B[1],0);
	REP(i,2,N){
		dp[i]=query(A[i]);
		insert(B[i],dp[i]);
	}
	cout << dp[N];
	return 0;
}
