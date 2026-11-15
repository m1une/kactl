/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once

struct dsu {
	vi par;
	dsu(int n): par(n, -1) {}
	bool same(int u, int v) { return leader(u) == leader(v); }
	int size(int v) { return -par[leader(v)]; }
	int leader(int v) { return par[v] < 0 ? v : par[v] = leader(par[v]); }
	bool merge(int u, int v) {
		u = leader(u), v = leader(v);
		if(u == v) return false;
		if(par[u] > par[v]) swap(u, v);
		par[u] += par[v]; par[v] = u;
		return true;
	}
};
