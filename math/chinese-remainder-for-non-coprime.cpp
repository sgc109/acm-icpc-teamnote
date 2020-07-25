ll xGCD(ll a, ll b, ll& x, ll& y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll x1, y1;
	int ret = xGCD(b, a % b, x1, y1);
	x = y1, y = x1 - (a / b) * y1;
	return ret;
}

ll chinese(vector<ll>& mods, vector<ll>& remains) {
	ll lcm = 1;
	for (ll num : mods) lcm *= num;
	ll ret = 0;
	ll N = 1;
	for (ll num : mods) N *= num;
	for (int i = 0; i < (int)mods.size(); i++) {
		ll n = mods[i];
		ll x, y;
		xGCD(n, N / n, x, y);
		if (y < 0) y %= N, y += N;
		ret = (ret + N / n * y % lcm * remains[i] % lcm) % lcm;
	}
	return ret;
}

void addMap(map<ll, pair<ll, ll> >& mp, ll idx, pair<ll, ll> pr) {
	if (mp.find(idx) != mp.end() && mp[idx].first < pr.first) mp.erase(idx);
	if (mp.find(idx) == mp.end()) mp[idx] = pr;
}

void makeVectors(vector<ll>& prevMods, vector<ll>& prevRem, vector<ll>& mods, vector<ll>& remains) {
	map<ll, pair<ll, ll> > mp;
	for (int i = 0; i < (int)prevMods.size(); i++) {
		ll back = prevMods[i];
		for (ll j = 2; j * j <= prevMods[i]; j++) {
			ll prev = back;
			int cnt = 0;
			while (back % j == 0) cnt++, back /= j;
			addMap(mp, j, { prev / back, prevRem[i] });
		}
		if (back != 1) addMap(mp, back, { back, prevRem[i] });
	}
	for (auto it : mp) {
		ll md = it.second.first;
		ll rem = it.second.second;
		rem %= md;
		mods.push_back(md);
		remains.push_back(rem);
	}
}

bool check(vector<ll>& mods, vector<ll>& remains) {
	int n = (int)mods.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || remains[i] < remains[j]) continue;
			ll trash;
			ll left = xGCD(mods[i], mods[j], trash, trash);
			ll right = remains[i] - remains[j];
			if (right % left) return false;
		}
	}
	return true;
}

ll solve(vector<ll>& prevMods, vectror<ll>& prevRem){
	if(!check(prevMods, prevRem)) return -1;
	vector<ll> mods, remains;
	makeVectors(prevMods, prevRem, mods, remains);
	return chinese(mods, remains);
}