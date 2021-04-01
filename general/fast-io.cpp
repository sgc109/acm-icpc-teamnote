static char s[75000000];

static inline void init() { fread(s, 1, sizeof(s), stdin); }

static inline void readN(int &r) {
    static char *p = s;
    while (*p < 45) p++;
    int m = 0;
    for (r = 0; *p >= '-'; p++) {
        if (*p == '-') {
            m = 1;
            continue;
        }
        r = r * 10 + (*p & 15);
    }
    if (m) r = -r;
}

int A[5000003];
int N, K;

int main() {
    init();
    readN(N);
    readN(K);
    for (int i = 0; i < N; i++) {
        readN(A[i]);
    }
    nth_element(A, A + K - 1, A + N);
    printf("%d", A[K - 1]);
}
