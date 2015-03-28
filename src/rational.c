#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "rational.h"

rational new_rational(int numer, int denom)
{
	assert(denom && "Denominator cannot be zero");
	rational r = { numer, denom };
	return r;
}

void print_rational(rational r)
{
	printf("%d", r.numer);

	if (r.denom != 1)
		printf("/%d", r.denom);
}

int gcd(int u, int v)
{
	int t;
	while (v)
	{
		t = u;
		u = v;
		v = t % v;
	}
	return u < 0 ? -u : u;
}

rational simplify(rational r)
{
	assert(r.denom && "Denominator cannot be zero");

	int d = gcd(r.numer, r.denom);
	rational result = { r.numer / d, r.denom / d };
	return result;
}

rational add_rational(rational a, rational b)
{
	assert(a.denom && "Denominator cannot be zero");
	assert(b.denom && "Denominator cannot be zero");

	rational product =
	{
		a.numer * b.denom + b.numer * a.denom,
		a.denom * b.denom
	};
	return simplify(product);
}

rational mult_rational(rational a, rational b)
{
	assert(a.denom && "Denominator cannot be zero");
	assert(b.denom && "Denominator cannot be zero");

	rational product = new_rational(a.numer * b.numer, a.denom * b.denom);
	return simplify(product);
}

rational power_rational(rational r, int p)
{
	assert(r.denom && "Denominator cannot be zero");
	rational result = new_rational((int)pow(r.numer, p), (int)pow(r.denom, p));
	return simplify(result);
}

rational int_to_rational(int i)
{
	rational r = { i, 1 };
	return r;
}

int rational_to_int(rational r)
{
	assert(r.denom && "Denominator cannot be zero");
	return r.denom / r.numer;
}
