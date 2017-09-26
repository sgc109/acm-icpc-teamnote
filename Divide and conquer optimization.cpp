	#include <iostream>
	#include <cstdio>
	#include <vector>
	#include <algorithm>
	#include <queue>
	#include <utility>
	#include <stack>
	#include <cstring>
	#include <cstdlib>
	#include <string>
	#include <set>
	#include <cmath>
	#include <deque>
	// #include <unordered_set>
	// #include <map>
	#define REP(i,a,b) for(int i = a; i <= b;++i)
	#define FOR(i,n) REP(i,0,n-1)
	#define mp make_pair
	#define pb push_back
	#define all(v) (v).begin(),(v).end()
	#define inp1(a) scanf("%d",&a)
	#define inp2(a,b) scanf("%d%d",&a,&b)
	#define inp3(a,b,c) scanf("%d%d%d",&a,&b,&c)
	#define inp4(a,b,c,d) scanf("%d%d%d%d",&a,&b,&c,&d)

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > piii;
typedef queue<int> QU;

const double EPSILON = 1e-9;
const double PI = acos(0.0)*2;
const int MOD = 1000000007;
const int INF = 0x3c3c3c3c;
const long long INFL = 0x3c3c3c3c3c3c3c3c;
const int MAX_N = 102;

int N,M;
int A[8003];
ll pSum[8003];
ll D[803][8003];
int K[803][8003];
ll C(int l, int r){
	return (pSum[r]-pSum[l-1])*(r-l+1);
}
void DC(int i, int l, int r, int p, int q){
	if(l>r) return;
	int mid=(l+r)>>1;
	D[i][mid]=INFL;
	for(int k=p;k<=q&&k<mid;k++){
		if(D[i][mid]>D[i-1][k]+C(k+1,mid)) D[i][mid]=D[i-1][k]+C(k+1,mid),K[i][mid]=k;
	}
	DC(i,l,mid-1,p,K[i][mid]);
	DC(i,mid+1,r,K[i][mid],q);
}
int main() {
	memset(D,0x3c,sizeof(D));
	inp2(N,M);
	REP(i,1,N) inp1(A[i]),pSum[i]=pSum[i-1]+A[i];
	if(N<=M) {
		printf("%lld",pSum[N]);
		return 0;
	}
	D[0][0]=0;
	// REP(i,1,M){
	// 	REP(j,1,N){
	// 		if(i>j) continue;
	// 		REP(k,i-1,j-1){
	// 			if(D[i][j]>D[i-1][k]+C(k+1,j)) D[i][j]=D[i-1][k]+C(k+1,j),K[i][j]=k;
	// 		}
	// 	}
	// }
	REP(i,1,M) DC(i,1,N,0,N-1);
	printf("%lld",D[M][N]);

	return 0;
}
