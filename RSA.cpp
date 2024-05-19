#include "RSA.h"
#include "Euclidean.h"
#include "Encryptor.h"
#include "Decryptor.h"
#include <exception>

using namespace boost::multiprecision;
using namespace boost::random;

//テスト用
Crypto::RSA::RSA(cpp_int p, cpp_int q, cpp_int r)
	: p(0), q(0), n(0), phi(0), e(0),
	private_key(nullptr),
	public_key(nullptr)
{
	try {
		setParameters(p, q, r);
		calcKeys();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		throw;
	}
}

Crypto::RSA::RSA(int bit)
	: p(getPrime()), q(getPrime()), n(0), phi(0), e(0), bit(bit),
	private_key(nullptr),
	public_key(nullptr)
{
	try {
		setParameters(p, q, 65537);
		calcKeys();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		throw;
	}
}

const Crypto::PublicKey* Crypto::RSA::getPublicKey() const
{
	return public_key;
}

const Crypto::PrivateKey* Crypto::RSA::getPrivateKey() const
{
	return private_key;
}

void Crypto::RSA::setParameters(cpp_int p, cpp_int q, cpp_int e)
{
	Euclidean euc;
	this->p = p;
	this->q = q;
	this->e = e;
	this->n = p * q;
	this->phi = calcPhi(p, q);

	if (!isPrime(p) || !isPrime(q))
	{
		throw std::exception("[ERROR] p または q は素数ではありません");
	}
	else if ((e < n) && (e > 1) && (euc.euclidean(e, phi) != 1))
	{
		throw std::exception("[ERROR] e が p * q (=> m) 以下ではないか、e と m の phi が互いに素ではありません");
	}

}

void Crypto::RSA::calcPrivateKey()
{
	Euclidean euc;
	cpp_int a = this->phi;
	cpp_int b = this->e;

	cpp_int s = 0;
	cpp_int x = 0;

	euc.extendedEuclidean(a, b, &x, &s);

	s = s < 0 ? makePositive(s, this->phi) : s;

	this->private_key = new PrivateKey{ s, this->p, this->q };
}

void Crypto::RSA::calcPublicKey()
{
	this->public_key = new PublicKey{ this->e, this->n };
}

void Crypto::RSA::calcKeys()
{
	if (private_key != nullptr || public_key != nullptr)
	{
		throw std::exception("[ERROR] すでに計算されています。");
	}

	calcPublicKey();
	calcPrivateKey();
}

cpp_int Crypto::RSA::makePositive(cpp_int numb, cpp_int mod) const
{
	cpp_int tmp = numb;
	while (tmp < 0) {
		tmp += mod;
	}
	return tmp;
}

cpp_int Crypto::RSA::getPrime()
{
	boost::random::uniform_int_distribution<cpp_int> dist(0, cpp_int(1) << bit);

	while (true) {
		cpp_int x = dist(gen);
		if (isPrime(x)) {
			return x;
		}
	};
}

cpp_int Crypto::RSA::calcPhi(cpp_int a, cpp_int b)
{
	if (!isPrime(a) || !isPrime(b))
	{
		return 0;
	}

	return (a - 1) * (b - 1);
}

bool Crypto::RSA::isPrime(cpp_int num)
{
	cpp_int U = 1;
	bool is_prime = false;
	Euclidean euc;
	boost::random::uniform_int_distribution<cpp_int> pn(0, cpp_int(1) << 16);

	for (int i = 0; i < 128; i++) {
		cpp_int u = pn(gen);
		if (u % 2 == 1) {
			bool is_prime = miller_rabin_test(u, 15, gen);
			if (is_prime) {
				U *= u;
			}
		}
	}
	is_prime = false;
	if (euc.euclidean(num, U) == 1) {
		is_prime = miller_rabin_test(num, 30, gen);
	}

	return is_prime;
}

Crypto::CryptoString Crypto::RSA::encrypt(std::string str)
{
	Encryptor enc(public_key);
	CryptoString out = enc.encryptString(str);
	return out;
}

std::string Crypto::RSA::decrypt(CryptoString str)
{
	Crypto::Decryptor dec(private_key);
	string res = dec.decryptString(str);
	return res;
}
