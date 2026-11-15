/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

struct RollbackUF {
	vi par; vector<pii> st;
	RollbackUF(int n) : par(n, -1) {}
	int size(int v) { return -par[leader(v)]; }
	int leader(int v) { return par[v] < 0 ? v : leader(par[v]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time()-1; i >= t; i--) {
			par[st[i].first] = st[i].second;
		}
		st.resize(t);
	}
	bool merge(int u, int v) {
		u = leader(u), v = leader(v);
		if (u == v) return false;
		if (par[u] > par[v]) swap(u, v);
		st.push_back({u, par[u]});
		st.push_back({v, par[v]});
		par[u] += par[v]; par[v] = u;
		return true;
	}
};
