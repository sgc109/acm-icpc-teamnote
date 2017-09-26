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
#define FOR(i,n) REP(i,0,n)
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

ll D[5003][5003];
int pSum[5003],K[5003][5003];
int f[5003];
int n;
int T;
int main() {
	for(inp1(T);T--;){
		inp1(n);
		REP(i,1,n) inp1(f[i]),pSum[i]=pSum[i-1]+f[i];
		memset(D,0x3c,sizeof(D));
		REP(i,1,n) D[i][i+1]=0,K[i][i+1]=i+1;
		REP(size,2,n){
			for(int i=1;i+size<=n+1;i++){
				int j=i+size;
				for(int k=K[i][j-1];k<=K[i+1][j];k++){
					if(D[i][j]>D[i][k]+D[k][j]+pSum[j-1]-pSum[i-1]) D[i][j]=D[i][k]+D[k][j]+pSum[j-1]-pSum[i-1],K[i][j]=k;
				}
			}
		}
		printf("%lld\n",D[1][n+1]);
	}
	return 0;
}
