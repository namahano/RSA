#ifndef RSA_
#define RSA_

#include <iostream>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace boost::multiprecision;
using namespace boost::random;

namespace Crypto {

	typedef struct {
		cpp_int s;
		cpp_int p;
		cpp_int q;
	} PrivateKey;

	typedef struct {
		cpp_int r;
		cpp_int m;
	} PublicKey;

	typedef std::vector<cpp_int> CryptoString;
	typedef cpp_int CryptoChar;

	class RSA {
	public:
		//テスト用
		RSA(cpp_int p, cpp_int q, cpp_int r);
		RSA(int bit);

		const PublicKey* getPublicKey() const;
		const PrivateKey* getPrivateKey() const;
		cpp_int getPrime();

		CryptoString encrypt(std::string str);
		std::string decrypt(CryptoString str);

	private:

		void calcPrivateKey();
		void calcPublicKey();
		void calcKeys();
		cpp_int makePositive(cpp_int numb, cpp_int mod) const;

		cpp_int calcPhi(cpp_int a, cpp_int b);
		bool isPrime(cpp_int num);
		void setParameters(cpp_int p, cpp_int q, cpp_int r);

		int bit;
		mt19937 gen;

		cpp_int p;
		cpp_int q;
		cpp_int phi_of_m;

		cpp_int m;
		cpp_int r;

		PrivateKey* private_key;
		PublicKey* public_key;
	};

}

#endif