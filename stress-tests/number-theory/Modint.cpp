#include "../utilities/template.h"

#include "../../content/number-theory/Modint.h"

int main() {
	auto norm = [](ll a) { return int((a % mod + mod) % mod); };
	assert(mint().x == 0);
	assert(mint(mod).x == 0);
	assert(mint(-1).x == mod - 1);
	assert((-mint(0)).x == 0);
	assert((-mint(2)).x == mod - 2);

	mt19937_64 rng(123456789);
	rep(it,0,100000) {
		ll a = ll(rng() % (2LL * mod)) - mod;
		ll b = ll(rng() % (mod - 1)) + 1;
		mint x = a, y = b;
		assert((x + y).x == norm(a + b));
		assert((x - y).x == norm(a - b));
		assert((x * y).x == norm(a * b));
		assert(((x / y) * y).x == x.x);
	}

	mint x = 3;
	assert(x.pow(0).x == 1);
	assert(x.pow(5).x == 243);
	assert((x * x.inv()).x == 1);
	cout << "Tests passed!\n";
}
