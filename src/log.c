#include "log.h"

float mylog_1(int n)
{
	Polynome* p = new_polynome(n);

	for (int i = 1; i < get_degree_polynome(p) + 1; ++i)
	{
		int sign = -1;
		if (i % 2)
			sign = +1;

		rational coef = new_rational(sign * 1, i);
		set_coef_polynome(p, i, &coef);
	}

	rational x = new_rational(1, 10);
	rational r = eval_polynome(p, &x);

	return (float)r.numer / (float)r.denom;
}
