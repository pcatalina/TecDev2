#pragma once

typedef struct rational
{
	int numer;
	int denom;
} rational;

rational new_rational(int numer, int denom);

void print_rational(rational r);

rational simplify(rational r);

rational add_rational(rational a, rational b);

rational mult_rational(rational a, rational b);

rational power_rational(rational r, int p);

rational int_to_rational(int i);

int rational_to_int(rational r);
