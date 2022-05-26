#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; cin >> n;
	std::vector<long long> a(n);
	for (auto &x : a) cin >> x;
	sort(a.begin(), a.end());
	map<int, int> mp;
	for (auto x : a) {
		mp[x] = mp[x] + 1;
		if (x != 1) mp[x] = max(mp[x], mp[1]);

		for (int i = 2; i * i <= x; i++) {
			if (x % i == 0) {
				int j = x / i;
				if (mp.count(i)) mp[x] = max(mp[x], mp[i] + 1);
				if (j == i) continue;
				if (mp.count(j)) mp[x] = max(mp[x], mp[j] + 1);
			}
		}
	}
	int ans = 1;
	for (auto x : mp) {
		ans = max(ans, x.second);
	}
	cout << ans;
	return 0;
}