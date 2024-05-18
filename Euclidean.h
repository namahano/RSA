#ifndef EUCLIDEAN_
#define EUCLIDEAN_

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

class Euclidean {
public:
	Euclidean();
	~Euclidean();
	cpp_int extendedEuclidean(cpp_int a, cpp_int b, cpp_int* x, cpp_int* s);
	cpp_int euclidean(cpp_int a, cpp_int b);
	cpp_int binary_euclidean(cpp_int u, cpp_int v);
private:

};

#endif