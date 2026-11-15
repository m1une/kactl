#include "../utilities/template.h"

#include "../../content/graph/SCC.h"

namespace old {
vi orig, low, comp, z;
int no_vertices, no_components;
template<class G> void dfs(int j, G &g) {
	low[j] = orig[j] = no_vertices++;
	comp[j] = -2; z.push_back(j);
	for(auto &e:g[j])
		if (comp[e] == -1) {
			dfs(e, g);
			low[j] = min(low[j], low[e]);
		}
		else if (comp[e] == -2)
			low[j] = min(low[j], orig[e]);

	if (orig[j] == low[j]) {
		for (;;) {
			int x = z.back(); z.pop_back();
			comp[x] = no_components;
			if (x == j) break;
		}
		no_components++;
	}
}
template<class G> vi scc(G &g) {
	int n = sz(g);
	orig.assign(n, 0); low = orig;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	rep(i,0,n) if (comp[i] == -1) dfs(i, g);
	return comp;
}
}

int main() {
	unsigned r = 1;
	for (int N = 0; N <= 4; N++) {
		// cout << "N = " << N << endl;
		vector<vi> mat(N, vi(N)), adj(N);
		vi seen(N);
		int count = 0;
		rep(bits,0,(1 << (N*N))) {
			// if (bits % 10000 == 0) cerr << "." << flush;
			rep(i,0,N) rep(j,0,N)
				mat[i][j] = bits & 1 << (i*N+j);

			rep(i,0,N) {
				adj[i].clear();
				rep(j,0,N) if (bits & 1 << (i*N+j)) {
					adj[i].push_back(j);
					r *= 12387123; r += 1231;
					if ((r >> 6 & 31) == 3)
						adj[i].push_back(j);
				}
			}
			vi comp2 = old::scc(adj);
			scc_graph sg(N);
			rep(i,0,N) for (int j : adj[i]) sg.add_edge(i, j);
			vector<vi> groups = sg.scc();
			assert(scc_graph(adj).scc() == groups);
			vi comp3(N);
			rep(i,0,sz(groups)) for (int v : groups[i]) comp3[v] = i;
			rep(i,0,N) assert(comp3[i] == sz(groups) - 1 - comp2[i]);
			rep(i,0,N) for (int j : adj[i]) assert(comp3[i] <= comp3[j]);
			rep(i,0,N) {
				seen.assign(N, 0); seen[i] = 1;
				rep(it,0,N) {
					rep(j,0,N) if (seen[j]) for(auto &k: adj[j]) seen[k] = 1;
				}
				rep(j,0,N) {
					if (seen[j]) assert(comp3[i] <= comp3[j]);
					else assert(comp3[j] != comp3[i]);
				}
			}

			count++;
		}
		// cout << "tested " << count << endl;
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
