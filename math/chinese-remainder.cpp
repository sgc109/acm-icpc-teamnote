ll xGCD(ll a, ll b, ll& x, ll& y){
	if(!b){
		x = 1, y = 0;
		return a;
	}
	ll x1, y1;
	int ret = xGCD(b, a % b, x1, y1);
	x = y1, y = x1 - (a / b) * y1;
	return ret;
}

ll chinese(vector<ll>& mods, vector<ll>& remains){
	ll lcm = mods[0];
	ll trash;
	for(int i = 1; i < (int)mods.size(); i++){
		lcm = lcm * mods[i] / xGCD(lcm, mods[i], trash, trash);
	}
	ll ret = 0;
	ll N = 1;
	for(ll num : mods) N *= num;
	for(int i = 0 ; i < (int)mods.size(); i++){
		ll n = mods[i];
		ll x, y;
		xGCD(n, N / n, x, y);
		if(y < 0) y %= N, y += N;
		ret = (ret + N / n * y % lcm * remains[i] % lcm) % lcm;
	}
	return ret;
}