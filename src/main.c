#include <math.h>
#include <stdio.h>
#include "rational.h"
#include "polynome.h"
#include "log.h"

int main()
{
	Polynome* p = new_polynome(10);
	print_polynome(p);
	printf("\n");

	for (int i = 0; i < get_degree_polynome(p) + 1; ++i)
	{
		const rational r = int_to_rational(i);
		set_coef_polynome(p, i, &r);
	}


	print_polynome(p);

	printf("\nTesting polynome evaluation\n");

	for (int i = 0; i < 5; ++i)
	{
		const rational x = int_to_rational(i);
		const rational r = eval_polynome(p, &x);
		print_rational(r);
		printf("\n");
	}

	delete_polynome(p);


	const float stdlog = (float)log(1.1);
	printf("std::log = %.5f\n", stdlog);
	
	for (int i = 0; i < 100; ++i)
	{
		const float mylog = mylog_1(i);
		const float diff = mylog - stdlog;
		printf("monoms=%d,\tmylog=%.5f,\t\tdiff=%.5f\n", i, mylog, diff);
	}

	return 0;
}
