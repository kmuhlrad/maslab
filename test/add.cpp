#include "mraa.hpp"
#include "add.h"

void Add::set_a() {
	a = num;
}

void Add::set_b() {
	b = num;
}

int Add::two_sum() {
	return a + b;
}