#include "../utilities/template.h"

#include "../../content/graph/2sat.h"

int main1() {
	const int N = 100000, M = 10000000;
	// Random constraints, unsolvable
	{
		two_sat ts(N);
		rep(i,0,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.add_clause(a, s&1, b, s&2);
		}
		assert(!ts.satisfiable());
	}
	// Random solvable instance
	{
		vector<bool> v(N);
		rep(i,0,N) v[i] = rand() & (1 << 20);
		two_sat ts(N);
		rep(i,0,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.add_clause(a, v[a], b, s&1);
		}
		assert(ts.satisfiable());
	}
	return 0;
}

int main2() {
	int N = 4;
	two_sat ts(N);
	ts.add_clause(0, true, 1, true);
	ts.add_clause(0, true, 1, false);
	ts.add_clause(2, false, 3, false);
	assert(ts.satisfiable());
	auto ans = ts.answer();
	assert((ans[0] || ans[1]) && (ans[0] || !ans[1]));
	assert(!ans[2] || !ans[3]);
	return 0;
}

int ra() {
	static unsigned X;
	X *= 1283611;
	X += 123;
	return X >> 1;
}

int main() {
	main1();
	main2();
	assert(two_sat(0).satisfiable());
	rep(it,0,10000) {
		int N = ra() % 8 + 1, M = ra() % 30;
		two_sat ts(N);
		vector<array<int, 4>> clauses;
		rep(i,0,M) {
			int a = ra() % N, b = ra() % N;
			bool f = ra() & 1, g = ra() & 1;
			ts.add_clause(a, f, b, g);
			clauses.push_back({a, f, b, g});
		}
		bool possible = false;
		rep(mask,0,1 << N) {
			bool ok = true;
			for (auto [a,f,b,g] : clauses)
				ok &= (((mask >> a) & 1) == f || ((mask >> b) & 1) == g);
			possible |= ok;
		}
		assert(ts.satisfiable() == possible);
		if (possible) {
			auto ans = ts.answer();
			for (auto [a,f,b,g] : clauses)
				assert(ans[a] == f || ans[b] == g);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
