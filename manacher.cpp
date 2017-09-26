#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long unsigned llu;
typedef long double ld;

const int inf = 0x3c3c3c3c;
const ll infl = 0x3c3c3c3c3c3c3c3c;

/*
2017-09-26 edited 
res[i] = i번째 문자에서 시작했을 때의 팰린드롬의 
홀수 길이의 팰린드롬을 반환
a b a b b
0 1 1 0 0 
짝수 길이의 팰린드롬도 필요할 경우 각 문자 사이에 '#'를 추가
#번째 문자가 속한 위치에 짝수 길이의 팰린드롬이 계산됨
i가 홀수일 경우에 res[i] / 2이 팰린드롬의 길이
i가 짝수일 경우에 res[i] / 2 + 1이 팰린드롬의 길이 
a # b # a # b # b #
0 0 2 0 3 0 1 1 0 0
created by cprayer
*/

vector<int> manacher(string &S){
	int sLen = (int)S.size();
	vector<int> res(sLen);
	int r = 0, c = 0;
	for(int i = 0; i < sLen; i++){
		if(c * 2 - i >= 1){
			res[i] = min(r - i, res[i * 2 - 1]);
		}
		while(i - res[i] - 1 >= 0 && i + res[i] + 1 < sLen && S[i - res[i] - 1] == S[i + res[i] + 1]) res[i]++;
		if(r < i + res[i]){
			r = i + res[i];
			c = i;
		}
	}
	return res;
}

int main(){
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int N;
	cin >> N;
	string s;
	for(int i = 0; i < N; i++){
		char ch;
		cin >> ch;
		s += ch;
		s += '#';
	}
	vector<int> arr = manacher(s);
	for(int v : arr) printf("%d ", v);
	printf("\n");
	int M;
	cin >> M;
	while(M--){
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		l *= 2, r *= 2;
		int m = (l + r) / 2;
		// printf("%d\n", arr[m])
	}
	return 0;
}