#ifndef DECRYPTOR_
#define DECRYPTOR_

#include "RSA.h"
#include <string>

using std::string;

namespace Crypto
{
    class Decryptor
    {
    private:
        const PrivateKey* private_key;

        string text;

    public:

        Decryptor(const PrivateKey* key);
        string decryptString(CryptoString input);
        
    };
}
#endif
