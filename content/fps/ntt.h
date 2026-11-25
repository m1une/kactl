/**
 * Author: chilli, miie
 * Date: 2026-11-26
 * License: CC0
 * Source: KACTL NumberTheoreticTransform.h
 * Description: Number theoretic transform and convolution modulo 998244353.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/Modint.h"

constexpr int root = 62;
void ntt(vc<mint>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vc<mint> rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		mint z[] = {1, mint(root).pow(mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = int((rev[i / 2] | (i & 1) << L) / 2);
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			mint z = rt[j + k] * a[i + j + k], &ai = a[i + j];
			a[i + j + k] = ai - z;
			ai += z;
		}
}
vc<mint> convolution(const vc<mint>& a, const vc<mint>& b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	mint inv = mint(n).inv();
	vc<mint> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n) out[-i & (n - 1)] = L[i] * R[i] * inv;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
