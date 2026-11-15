/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc_graph g(n); g.add_edge(a, b); g.scc() returns the
 * components in topological order.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

struct scc_graph {
	int n, t;
	vector<vi> g, groups;
	vi val, comp, z;
	scc_graph(int n_) : n(n_), g(n) {}
	scc_graph(const vector<vi>& g_) : n(sz(g_)), g(g_) {}

	void add_edge(int from, int to) {
		assert(0 <= from && from < n);
		assert(0 <= to && to < n);
		g[from].emplace_back(to);
	}

	int dfs(int v) {
		int low = val[v] = ++t, x; z.push_back(v);
		for (int u : g[v]) if (comp[u] < 0)
			low = min(low, val[u] ?: dfs(u));
		if (low == val[v]) {
			groups.emplace_back();
			do {
				x = z.back(); z.pop_back();
				comp[x] = sz(groups) - 1;
				groups.back().push_back(x);
			} while (x != v);
		}
		return val[v] = low;
	}
	vector<vi> scc() {
		val.assign(n, 0); comp.assign(n, -1);
		z.clear(); groups.clear(); t = 0;
		for (int v=0; v<n; v++) if (comp[v] < 0) dfs(v);
		reverse(all(groups));
		return groups;
	}
};
