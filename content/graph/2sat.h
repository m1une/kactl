/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Usage:
 *  two_sat ts(number of boolean variables);
 *  ts.add_clause(0, true, 3, false); // Var 0 is true or var 3 is false
 *  ts.satisfiable(); // Returns true iff it is solvable
 *  ts.answer()[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

#include "SCC.h"

struct two_sat {
	int n;
	vector<bool> ans;
	scc_graph sg;
	two_sat(int n_) : n(n_), ans(n), sg(2 * n) {}

	void add_clause(int i, bool f, int j, bool g) {
		assert(0 <= i && i < n);
		assert(0 <= j && j < n);
		sg.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
		sg.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
	}
	bool satisfiable() {
		auto scc = sg.scc();
		vi id(2*n);
		for (int i=0; i<sz(scc); i++) for (int v : scc[i]) id[v] = i;
		for (int i = 0; i < n; i++) {
			if (id[2 * i] == id[2 * i + 1]) return false;
			ans[i] = id[2 * i] < id[2 * i + 1];
		}
		return true;
	}
	vector<bool> answer() { return ans; }
};
