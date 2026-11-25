/**
 * Author: miie
 * Date: 2026-11-26
 * Description: Formal power series over mint.
 * Time: $O(N \log N)$ for multiplication, inverse, logarithm and exponential.
 * Status: stress-tested
 */
#pragma once

#include "ntt.h"

struct FPS : vc<mint> {
	using vc<mint>::vector;
	FPS& operator+=(const FPS& r) {
		if (r.size() > size()) resize(r.size());
		rep(i,0,sz(r)) (*this)[i] += r[i];
		return *this;
	}
	FPS& operator+=(mint r) {
		(*this)[0] += r;
		return *this;
	}
	FPS& operator-=(const FPS& r) {
		if (r.size() > size()) resize(r.size());
		rep(i,0,sz(r)) (*this)[i] -= r[i];
		return *this;
	}
	FPS& operator*=(mint r) {
		for (auto& x : *this) x *= r;
		return *this;
	}
	FPS& operator/=(mint r) { return *this *= r.inv(); }
	FPS& operator*=(const FPS& r) {
		auto ret = convolution(*this, r);
		return *this = FPS(all(ret));
	}
	FPS operator+(const FPS& r) const { return FPS(*this) += r; }
	FPS operator-(const FPS& r) const { return FPS(*this) -= r; }
	FPS operator*(const FPS& r) const { return FPS(*this) *= r; }
	FPS operator+(mint r) const { return FPS(*this) += r; }
	FPS operator*(mint r) const { return FPS(*this) *= r; }
	FPS operator/(mint r) const { return FPS(*this) /= r; }

	FPS pre(int n) const { 
		FPS ret(begin(), begin() + min(n, sz(*this)));
		ret.resize(n);
		return ret;
	}
	FPS inv(int n) const {
		FPS r(1, (*this)[0].inv());
		for (int i=1; i<n; i<<=1)
			r = (r*mint(2) - r*r*pre(i<<1)).pre(i<<1);
		return r.pre(n);
	}
	FPS diff() const {
		FPS r(max(0, sz(*this)-1));
		rep(i,1,sz(*this)) r[i-1] = mint(i) * (*this)[i];
		return r;
	}
	FPS integral() const {
		FPS r(sz(*this)+1);
		rep(i,0,sz(*this)) r[i+1] = (*this)[i] / mint(i+1);
		return r;
	}
	FPS log(int n) const {
		return (diff() * inv(n-1)).pre(n-1).integral();
	}
	FPS exp(int n) const {
		FPS r(1, 1);
		for (int i=1; i<n; i<<=1) { r = (r * (pre(i<<1) + mint(1) - r.log(i<<1))).pre(i<<1); }
		return r.pre(n);
	}
};
