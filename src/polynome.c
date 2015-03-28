#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "polynome.h"
#include "rational.h"

struct Polynome
{
	int n;
	rational* coef;
};

Polynome* new_polynome(unsigned int deg)
{
	Polynome* p = malloc(sizeof *p);
	p->n = deg;
	p->coef = malloc(sizeof(p->coef[0]) * (deg + 1));
	
	for (unsigned int i = 0; i < deg + 1; ++i)
	{
		p->coef[i] = new_rational(0, 1);
	}

	return p;
}

void delete_polynome(Polynome* p)
{
	if (p)
	{
		free(p->coef);
		free(p);
		p = NULL;
	}
}

void print_polynome(const Polynome* p)
{
	for (int i = 0; i < p->n + 1; ++i)
	{
		printf("(");

		print_rational(p->coef[i]);
		
		printf(")");

		if (i > 0)
			printf(" * x");
		
		if (i > 1)
		{
			printf(" ^ %d", i);
		}

		if (i < p->n)
			printf(" + ");

		printf("\n");
	}
}

void set_coef_polynome(const Polynome* p, int deg, const rational* val)
{
	assert(p && "Trying to dereference null ptr");
	assert(p->coef  &&  "Trying to dereference null ptr");
	assert(val &&  "Trying to dereference null ptr");
	assert((deg < (p->n + 1)) && "Out of bounds: degree is too high");
	
	p->coef[deg] = *val;
}

rational* get_coef_polynome(const Polynome* p, int deg)
{
	assert(p &&  "Trying to dereference null ptr");
	assert(p->coef &&  "Trying to dereference null ptr");
	assert((deg < (p->n + 1)) && "Out of bounds: degree is too high");
	
	return &p->coef[deg];
}

int get_degree_polynome(const Polynome* p)
{
	assert(p &&  "Trying to dereference null ptr");
	return p->n;
}

rational eval_polynome(const Polynome* p, const rational* x)
{
	rational result = new_rational(0, 1);

	for (int i = 0; i < get_degree_polynome(p) + 1; ++i)
	{
		rational* mono = get_coef_polynome(p, i);
		rational mono_x = mult_rational(*mono, *x);
		result = add_rational(result, mono_x);
	}

	return result;
}
