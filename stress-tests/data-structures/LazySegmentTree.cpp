#include "../utilities/template.h"

namespace range_add_max {
int op(int a, int b) { return max(a, b); }
int e() { return INT_MIN; }
int mapping(int f, int x) { return x == e() ? e() : f + x; }
int composition(int f, int g) { return f + g; }
int id() { return 0; }

#include "../../content/data-structures/LazySegmentTree.h"

using Tree = LazySegTree<int, op, e, int, mapping, composition, id>;
}

namespace affine_sum {
struct S { long long sum; int size; };
struct F { long long a, b; };
S op(S x, S y) { return {x.sum + y.sum, x.size + y.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {f.a * x.sum + f.b * x.size, x.size}; }
F composition(F f, F g) { return {f.a * g.a, f.a * g.b + f.b}; }
F id() { return {1, 0}; }
using Tree = range_add_max::LazySegTree<S, op, e, F, mapping, composition, id>;
}

int main() {
	using namespace range_add_max;
	mt19937 rng(1234567);
	for (int n = 0; n < 30; ++n) {
		vector<int> a(n);
		for (int& x : a) x = int(rng() % 100) - 50;
		Tree tree(a, 0, n);
		for (int it = 0; it < 20000; ++it) {
			int l = int(rng() % unsigned(n + 1));
			int r = int(rng() % unsigned(n + 1));
			if (l > r) swap(l, r);
			if (rng() % 3 == 0) {
				int want = e();
				for (int i = l; i < r; ++i) want = max(want, a[i]);
				assert(tree.prod(l, r) == want);
			} else {
				int f = int(rng() % 21) - 10;
				tree.apply(l, r, f);
				for (int i = l; i < r; ++i) a[i] += f;
			}
		}
	}
	{
		using namespace affine_sum;
		vector<S> init;
		vector<long long> a(20);
		for (int i = 0; i < sz(a); ++i) a[i] = i, init.push_back({i, 1});
		affine_sum::Tree tree(init, 0, sz(init));
		for (int it = 0; it < 10000; ++it) {
			int l = int(rng() % 21), r = int(rng() % 21);
			if (l > r) swap(l, r);
			if (rng() & 1) {
				F f{static_cast<long long>(rng() % 3),
					static_cast<long long>(int(rng() % 11) - 5)};
				tree.apply(l, r, f);
				for (int i = l; i < r; ++i) a[i] = f.a * a[i] + f.b;
			} else {
				long long want = accumulate(a.begin() + l, a.begin() + r, 0LL);
				assert(tree.prod(l, r).sum == want);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
