ll mul(ll a, ll b, ll MOD){
	ll res = 0;
	while(b){
		if(b & 1) res = (res + a) % MOD;
		a = (a * 2) % MOD;
		b /= 2;
	}
	return res;
}

ll Pow(ll a, ll b, ll MOD){
	ll res = 1;
	ll x = a;
	while(b){
		if(b & 1) res = mul(res, x, MOD);
		x = mul(x, x, MOD);
		b /= 2;
	}
	return res;
}

bool fermat(ll n){
	const static vector<int> arr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i = 0; i < (int)arr.size(); i++){
		if(arr[i] == n) return true;
		if(Pow(arr[i], n - 1, n) != 1) return false;
	}
	return true;
}