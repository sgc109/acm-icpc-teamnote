ll mul(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

ll Pow(ll a, ll b, ll mod) {
    ll res = 1;
    ll x = a;
    while (b) {
        if (b & 1) res = mul(res, x, mod);
        x = mul(x, x, mod);
        b /= 2;
    }
    return res;
}

bool isPrime(ll n) {
    const static vector<int> arr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n == 1) return false;
    for (int i = 0; i < (int) arr.size(); i++) {
        if (arr[i] == n) return true;
        if (Pow(arr[i], n - 1, n) != 1) return false;
    }
    return true;
}

ll rho(ll n) {
    ll x, y, d, c = -1;
    if (n % 2 == 0) return 2;
    while (1) {
        x = y = 2;
        while (1) {
            x = mul(x, x, n);
            x = (x - c) % n;
            y = mul(y, y, n);
            y = (y - c) % n;
            y = mul(y, y, n);
            y = (y - c) % n;
            d = gcd(abs(n + y - x), n);
            if (d == n) break;
            else if (d > 1) return d;
        }
        c--;
    }
}

void fator(ll n, vector <ll> &arr) {
    if (isPrime(n)) {
        arr.push_back(n);
        return;
    }
    ll f = rho(n);
    fator(f, arr);
    fator(n / f, arr);
}

