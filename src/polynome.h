#pragma once
#include "rational.h"

struct Polynome;
typedef struct Polynome Polynome;

Polynome* new_polynome(unsigned int deg);

void delete_polynome(Polynome* p);

void set_coef_polynome(const Polynome* p, int deg, const rational* val);

rational* get_coef_polynome(const Polynome* p, int deg);

int get_degree_polynome(const Polynome* p);

rational eval_polynome(const Polynome* p, const rational* x);

void print_polynome(const Polynome* p);
