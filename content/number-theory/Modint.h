/**
 * Author: miie
 * Date: 2026-10-08
 * Description: Modular integer arithmetic modulo the prime constant
 * $\texttt{mod}$. Supports the four arithmetic operations and powers.
 * Time: $O(1)$ per arithmetic operation, $O(\log b)$ for pow(b) and inv().
 * Status: Unit-tested
 */
#pragma once

constexpr int mod = 998244353;
struct mint {
	int x;
	mint(ll x_ = 0) : x(int(x_ % mod)) {
		if (x < 0) x += mod;
	}
	mint operator-() const {
		auto res = *this;
		res.x = (x ? mod - x : 0);
		return res;
	}
	mint& operator+=(mint r) {
		if ((x += r.x) >= mod) x -= mod;
		return *this;
	}
	mint& operator-=(mint r) {
		if ((x -= r.x) < 0) x += mod;
		return *this;
	}
	mint& operator*=(mint r) {
		x = int(1LL * x * r.x % mod);
		return *this;
	}
	mint& operator/=(mint r) { return *this *= r.inv(); }
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
	friend mint operator/(mint a, mint b) { return a /= b; }
	mint inv() const { return pow(mod - 2); }
	mint pow(ll b) const {
		mint a = *this, c = 1;
		while (b) {
			if (b & 1) c *= a;
			a *= a;
			b >>= 1;
		}
		return c;
	}
};
