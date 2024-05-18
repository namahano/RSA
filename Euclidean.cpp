#include "Euclidean.h"

Euclidean::Euclidean() {}

Euclidean::~Euclidean() {}


cpp_int Euclidean::extendedEuclidean(cpp_int a, cpp_int b, cpp_int* x, cpp_int* s)
{
	if (b == 0) {
		*x = 1;
		*s = 0;
		return a;
	}

	cpp_int q = a / b;
	cpp_int r = a % b;

	cpp_int x_tmp = *x;
	cpp_int s_tmp = *s;

	cpp_int gcd = extendedEuclidean(b, r, &x_tmp, &s_tmp);

	*x = s_tmp;
	*s = x_tmp - (q * s_tmp);

	return gcd;
}

cpp_int Euclidean::euclidean(cpp_int a, cpp_int b)
{
	if ((a == 0) || (b == 0)){
		return 0;
	}

	cpp_int q;
	cpp_int r;

	do{
		q = a / b;
		r = a % b;

		a = b;
		b = r;
	} while (r != 0);

	return a;
}

cpp_int Euclidean::binary_euclidean(cpp_int u, cpp_int v)
{
	if (u == v) return u;
	if (u == 0) return v;
	if (v == 0) return u;

	// u ‚Æ v ‚Ì—¼•û‚ª‹ô”‚Ìê‡
	if ((u & 1) == 0 && (v & 1) == 0) {
		return binary_euclidean(u >> 1, v >> 1) << 1;
	}
	// u ‚ª‹ô”‚Ìê‡
	else if ((u & 1) == 0) {
		return binary_euclidean(u >> 1, v);
	}
	// v ‚ª‹ô”‚Ìê‡
	else if ((v & 1) == 0) {
		return binary_euclidean(u, v >> 1);
	}
	// u ‚Æ v ‚ª—¼•ûŠï”‚Ìê‡Au >= v
	else if (u >= v) {
		return binary_euclidean((u - v) >> 1, v);
	}
	// u ‚Æ v ‚ª—¼•ûŠï”‚Ìê‡Au < v
	else {
		return binary_euclidean(u, (v - u) >> 1);
	}
}
