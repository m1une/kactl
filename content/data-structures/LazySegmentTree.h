/**
 * Author: Simon Lindholm, miie
 * Date: 2016-10-08
 * License: CC0
 * Source: me, AtCoder Library
 * Description: Dynamic lazy segment tree. $op$ and $e$ form a monoid on S,
 * $mapping(f, x)$ applies f to x, and $composition(f, g)$ returns $f \circ g$.
 * The actions F form a monoid with identity $id()$ and distribute over $op$.
 * Bounds are inclusive to the left and exclusive to the right.
 * Time: O(\log N) per operation
 * Usage: LazySegTree<S, op, e, F, mapping, composition, id> tree(0, n);
 * Status: stress-tested
 */
#pragma once

template <typename S, auto op, auto e, typename F, auto mapping,
		  auto composition, auto id>
struct LazySegTree {
	LazySegTree *l = 0, *r = 0;
	int lo, hi;
	S val = e();
	F lazy = id();
	LazySegTree(int lo, int hi) : lo(lo), hi(hi) {}
	LazySegTree(const vector<S>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new LazySegTree(v, lo, mid);
			r = new LazySegTree(v, mid, hi);
			pull();
		} else if (lo < hi) val = v[lo];
	}
	~LazySegTree() { delete l; delete r; }
	LazySegTree(const LazySegTree&) = delete;
	LazySegTree& operator=(const LazySegTree&) = delete;
	S prod(int L, int R) {
		if (R <= lo || hi <= L) return e();
		if (L <= lo && hi <= R) return val;
		push();
		return op(l->prod(L, R), r->prod(L, R));
	}
	void apply(int L, int R, F f) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) allApply(f);
		else {
			push();
			l->apply(L, R, f), r->apply(L, R, f);
			pull();
		}
	}
private:
	void pull() { val = op(l->val, r->val); }
	void allApply(F f) {
		val = mapping(f, val);
		lazy = composition(f, lazy);
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo) / 2;
			l = new LazySegTree(lo, mid);
			r = new LazySegTree(mid, hi);
		}
		l->allApply(lazy), r->allApply(lazy);
		lazy = id();
	}
};
