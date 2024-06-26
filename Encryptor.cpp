#include "Encryptor.h"
#include "RSA.h"
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

Crypto::Encryptor::Encryptor(const PublicKey* key)
    : text(""), public_key(key)
{}

Crypto::CryptoString Crypto::Encryptor::encryptString(string& input)
{
    CryptoString str;

    cpp_int tmp;
    for (int i = 0; i < input.length(); i++) {
        tmp = boost::multiprecision::powm((cpp_int)input.at(i), public_key->e, public_key->n);
        str.push_back(tmp);
    }
    return str;
}
