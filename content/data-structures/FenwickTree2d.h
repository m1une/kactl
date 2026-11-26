/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call reserve() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

template<typename T>
struct fenwick_tree_2d {
	vector<vi> ys; vector<fenwick_tree<T>> ft;
	fenwick_tree_2d(int n) : ys(n) {}
	void reserve(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void add(int x, int y, T v) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].add(ind(x, y), v);
	}
	T sum(int x, int y) {
		T res = 0;
		for (; x; x &= x - 1)
			res += ft[x-1].sum(ind(x-1, y));
		return res;
	}
	T sum(int lx, int rx, int ly, int ry) {
		assert(lx <= rx && ly <= ry);
		return sum(rx, ry) - sum(lx, ry) - sum(rx, ly) + sum(lx, ly);
	}
};
