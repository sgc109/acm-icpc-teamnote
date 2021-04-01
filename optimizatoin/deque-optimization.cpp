ll psum[100003];
ll A[100003];
ll dp[100003];
deque<int> dq;
int N, K;

ll C(int i) {
    return dp[i - 1] - psum[i];
}

int main() {
    fastio();
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) psum[i] = psum[i - 1] + A[i];
    for (int i = 1; i <= N; i++) {
        while (!dq.empty() && dq.front() < i - K) dq.pop_front();
        while (!dq.empty() && C(dq.back()) <= C(i)) dq.pop_back();
        dq.push_back(i);
        dp[i] = psum[i] + C(dq.front());
        if (i <= K) dp[i] = max(dp[i], psum[i]);
    }
    cout << dp[N];
    return 0;
}


