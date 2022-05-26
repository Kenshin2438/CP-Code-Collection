#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n; long long k;
	cin >> n >> k;
	std::vector<long long> a(n);
	for (auto &ax : a) cin >> ax;
	long long l = 0, r = 2e13, ans;
	while (l <= r) {
		long long m = (l + r) >> 1;
		long long sum = 0;
		for (auto ax : a) {
			if (ax >= m) continue;
			sum += m - ax;
		}
		if (sum > k) r = m - 1;
		else l = m + 1, ans = m;
	}
	cout << ans;
	return 0;
}