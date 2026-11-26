#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
template<class T> using vc = vector<T>;
using vi = vc<int>;

#include "../content/fps/ntt.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vc<mint> a(n), b(m);
	for (mint& x : a) { int y; cin >> y; x = y; }
	for (mint& x : b) { int y; cin >> y; x = y; }
	for (mint x : convolution(a, b)) cout << x.x << ' ';
	cout << '\n';
}
