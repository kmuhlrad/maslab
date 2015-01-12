#include "add.h"
#include "mraa.hpp"

void Add::set_a(int num) {
	a = num;
}

void Add::set_b(int num) {
	b = num;
}

int Add::two_sum() {
	return a + b;
}