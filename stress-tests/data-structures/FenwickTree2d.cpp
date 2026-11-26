#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree2d.h"

int main() {
	rep(it,0,1000000) {
		fenwick_tree_2d<ll> ft(12);
		vector<tuple<int, int, int>> upd;
		int c = rand() % 20;
		rep(i,0,c) {
			upd.emplace_back(rand() % 12, rand() % 12, rand() % 10 - 5);
		}

		vector<vi> grid(12, vi(12)), sumto(13, vi(13));
		for(auto &pa: upd)
			ft.reserve(get<0>(pa), get<1>(pa));
		ft.init();
		for(auto &pa: upd) {
			grid[get<0>(pa)][get<1>(pa)] += get<2>(pa);
			ft.add(get<0>(pa), get<1>(pa), get<2>(pa));
		}

		rep(i,0,13) {
			rep(j,0,13) {
				ll v = ft.sum(i, j);
				if (i == 0 || j == 0) assert(v == 0);
				else {
					sumto[i][j] = grid[i-1][j-1] + sumto[i-1][j] + sumto[i][j-1] - sumto[i-1][j-1];
					assert(v == sumto[i][j]);
				}
			}
		}
		int lx = rand() % 13, rx = rand() % 13;
		int ly = rand() % 13, ry = rand() % 13;
		if (lx > rx) swap(lx, rx);
		if (ly > ry) swap(ly, ry);
		ll expected = sumto[rx][ry] - sumto[lx][ry]
			- sumto[rx][ly] + sumto[lx][ly];
		assert(ft.sum(lx, rx, ly, ry) == expected);
	}
	cout<<"Tests passed!"<<endl;
}
