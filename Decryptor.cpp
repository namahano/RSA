#include <string>
#include "Decryptor.h"
#include "RSA.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

Crypto::Decryptor::Decryptor(const PrivateKey* key)
    : text(""), private_key(key)
{}

string Crypto::Decryptor::decryptString(CryptoString input)
{
    string cypher;

    cpp_int tmp;
    for (int i = 0; i < input.size(); i++)
    {
        tmp = boost::multiprecision::powm(input[i], private_key->s, private_key->q * private_key->p);
        cypher.push_back(tmp.convert_to<char>());
    }

    return cypher;
}
