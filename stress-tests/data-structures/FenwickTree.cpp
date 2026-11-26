#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

int main() {
	rep(it,0,100000) {
		int N = rand() % 10;
		fenwick_tree<int> fw(N);
		vi t(N);
		rep(i,0,N) {
			int v = rand() % 3;
			fw.add(i, v);
			t[i] += v;
		}
		rep(l,0,N+1) rep(r,l,N+1) {
			int expected = accumulate(t.begin() + l, t.begin() + r, 0);
			assert(fw.sum(l, r) == expected);
		}
		int q = rand() % 20;
		int ind = fw.lower_bound(q);
		int res = -1, sum = 0;
		rep(i,0,N+1) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);
	}
	cout<<"Tests passed!"<<endl;
}
