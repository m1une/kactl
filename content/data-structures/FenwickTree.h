/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

template<typename T>
struct fenwick_tree {
	vector<T> s;
	fenwick_tree(int n) : s(n) {}
	void add(int i, T x) { // a[i] += x
		for (; i < sz(s); i |= i + 1) s[i] += x;
	}
	T sum(int r) { // sum of values in [0, r)
		T res = 0;
		for (; r > 0; r &= r - 1) res += s[r-1];
		return res;
	}
	T sum(int l, int r) { // sum of values in [l, r)
		assert(l <= r);
		return sum(r) - sum(l);
	}
	int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};
