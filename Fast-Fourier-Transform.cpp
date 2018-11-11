typedef complex<double> base;
const double PI = 2.0 * acos(0.0);

/*blog.myungwoo.kr/54*/
void fft(vector <base> &a, bool invert) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
            j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; j++) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
    vector<base> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < max(sz(a), sz(b))) n <<= 1; n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    for (int i = 0; i < n; i++) res[i] = int(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
    while(!res.empty() && res.back() == 0) res.pop_back();
}

const int MAX_L = (3e5 + 9) * 2;
vector<int> A, B, res;
int ans[MAX_L];

int main() {
    fastio();
    string s1, s2;
    cin >> s1 >> s2;
    int s1sz = s1.size(), s2sz = s2.size();
    for(int i = 0; i < s1sz; i++){
        A.push_back(s1[i] - '0');
    }
    for(int i = 0; i < s2sz; i++){
        B.push_back(s2[i] - '0');
    }
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    multiply(A, B, res);
    int ressz = res.size();
    for(int i = 0; i < ressz; i++){
        int v = (ans[i] + res[i]);
        ans[i] = v % 10;
        ans[i + 1] = v / 10;
    }
    int len = ressz;
    while(len >= 0 && ans[len] == 0) len--;
    if(len < 0) printf("0");
    for(int i = len; i >= 0; i--) printf("%d", ans[i]);
}
