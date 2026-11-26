#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
template<class T> using vc = vector<T>;
using vi = vc<int>;

#include "../content/fps/fps.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	FPS f(n);
	for (mint& x : f) { int y; cin >> y; x = y; }
	for (mint x : f.log(n)) cout << x.x << ' ';
	cout << '\n';
}
