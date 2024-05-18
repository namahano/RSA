#ifndef ENCRYPTOR_
#define ENCRYPTOR_

#include "RSA.h"
#include <string>

using std::string;

namespace Crypto
{
    class Encryptor
    {
    private:
        const PublicKey* public_key;

        string text;

    public:
        Encryptor(const PublicKey* key);

        CryptoString encryptString(string& input);
        
    };
}
#endif
