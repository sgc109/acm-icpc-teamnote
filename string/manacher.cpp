/*
2017-10-17 edited 
res[i] = i번째 문자를 중심으로 하는 팰린드롬의 반지름(문자열은 0부터 시작한다고 가정)
홀수 길이의 팰린드롬 반지름을 반환
a b a b b
0 1 1 0 0 
짝수 길이의 팰린드롬 반지름도 필요할 경우 각 문자 사이에 '#'를 추가
#번째 문자가 속한 위치에 짝수 길이의 팰린드롬 반지름이 계산됨
이 경우 res[i] / 2이 팰린드롬의 반지름
a # b # a # b # b #
0 0 2 0 3 0 1 2 1 0
*/

vector<int> manacher(string &S) {
    int sLen = (int) S.size();
    vector<int> res(sLen, 0);
    int r = 0, c = 0;
    for (int i = 0; i < sLen; i++) {
        if (i < r) {
            res[i] = min(r - i, res[c * 2 - i]);
        }
        while (i - res[i] - 1 >= 0 && i + res[i] + 1 < sLen && S[i - res[i] - 1] == S[i + res[i] + 1]) res[i]++;
        if (r < i + res[i]) {
            r = i + res[i];
            c = i;
        }
    }
    return res;
}
