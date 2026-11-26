#include "../utilities/template.h"

template<class T> using vc = vector<T>;
#include "../../content/fps/ntt.h"

vc<mint> slow(const vc<mint>& a, const vc<mint>& b) {
	if (a.empty() || b.empty()) return {};
	vc<mint> c(sz(a) + sz(b) - 1);
	rep(i,0,sz(a)) rep(j,0,sz(b)) c[i+j] += a[i] * b[j];
	return c;
}

int main() {
	mt19937 rng(1234567);
	rep(it,0,10000) {
		vc<mint> a(rng() % 20), b(rng() % 20);
		for (mint& x : a) x = int(rng());
		for (mint& x : b) x = int(rng());
		auto x = convolution(a, b), y = slow(a, b);
		assert(sz(x) == sz(y));
		rep(i,0,sz(x)) assert(x[i].x == y[i].x);
	}
	cout << "Tests passed!\n";
}
