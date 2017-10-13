#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long unsigned llu;
typedef long double ld;

const int inf = 0x3c3c3c3c;
const ll infl = 0x3c3c3c3c3c3c3c3c;

/*
2017-09-26 edited 
res[i] = i번째 문자를 중심으로 하는 팰린드롬의 반지름
홀수 길이의 팰린드롬 반지름을 반환
a b a b b
0 1 1 0 0 
짝수 길이의 팰린드롬 반지름도 필요할 경우 각 문자 사이에 '#'를 추가
#번째 문자가 속한 위치에 짝수 길이의 팰린드롬 반지름이 계산됨
i가 홀수일 경우에 res[i] / 2 + 1이 팰린드롬의 반지름
i가 짝수일 경우에 res[i] / 2이 팰린드롬의 반지름 
a # b # a # b # b #
0 0 2 0 3 0 1 1 0 0
*/

vector<int> manacher(string &S){
	int sLen = (int)S.size();
	vector<int> res(sLen, 0);
	int r = 0, c = 0;
	for(int i = 0; i < sLen; i++){
		if(i < r){
			res[i] = min(r - i, res[c * 2 - i]);
		}
		while(i - res[i] - 1 >= 0 && i + res[i] + 1 < sLen && S[i - res[i] - 1] == S[i + res[i] + 1]) res[i]++;
		if(r < i + res[i]){
			r = i + res[i];
			c = i;
		}
	}
	return res;
}