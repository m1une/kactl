#include "../utilities/template.h"

template<class T> using vc = vector<T>;
#include "../../content/fps/fps.h"

int main() {
	FPS a{1, 2}, b{3, 4, 5};
	assert(&((a += b) -= b) == &a);
	assert(a[0].x == 1 && a[1].x == 2 && a[2].x == 0);
	a *= 3;
	assert(a[0].x == 3 && a[1].x == 6 && a[2].x == 0);
	FPS c = FPS{1, 2} * FPS{3, 4};
	assert(sz(c) == 3 && c[0].x == 3 && c[1].x == 10 && c[2].x == 8);
	FPS p = FPS{1, 2}.pre(4);
	assert(sz(p) == 4);

	mt19937 rng(1234567);
	for (int n=1; n<=100; n++) {
		FPS f(n);
		for (mint& x : f) x = int(rng());
		if (!f[0].x) f[0] = 1;
		FPS g = (f * f.inv(n)).pre(n);
		assert(g[0].x == 1);
		rep(i,1,n) assert(g[i].x == 0);

		f[0] = 0;
		FPS h = f.exp(n).log(n);
		rep(i,0,n) assert(h[i].x == f[i].x);
		FPS d = f.diff().integral();
		rep(i,0,n) assert(d[i].x == f[i].x);
	}
	cout << "Tests passed!\n";
}
