#include <iostream>
#include <exception>
#include "RSA.h"
#include "Encryptor.h"
#include "Decryptor.h"

int main()
{
	try {
		int bit;
		std::string input;
		std::cout << "生成する素数のビット数を入力してください: ";
		std::cin >> bit;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "平文: ";
		std::getline(std::cin, input);

		std::cout << "素数を生成しています" << std::endl;
		Crypto::RSA rsa(bit);
		//Crypto::RSA rsa(1951, 1861, 65537);
		Crypto::Encryptor enc(rsa.getPublicKey());
		Crypto::Decryptor dec(rsa.getPrivateKey());

		Crypto::CryptoString encrypted = rsa.encrypt(input);
		std::string decrypted = rsa.decrypt(encrypted);

		printf("\n");

		std::cout << "---- 公開鍵 ----" << std::endl;
		std::cout << "e = " << rsa.getPublicKey()->e << "\n" << std::endl;
		std::cout << "n = " << rsa.getPublicKey()->n << "\n" << std::endl;
		std::cout << "---- 秘密鍵 ----\n";
		std::cout << "d = " << rsa.getPrivateKey()->d << "\n" << std::endl;
		std::cout << "p = " << rsa.getPrivateKey()->p << "\n" << std::endl;
		std::cout << "q = " << rsa.getPrivateKey()->q << "\n" << std::endl;

		std::cout << "---- 暗号文 ---- \n";
		for (int i = 0; i < encrypted.size(); i++)
			std::cout << encrypted[i];
		printf("\n\n");
		std::cout << "---- 復号文 ----" << "\n" << decrypted << std::endl;

	}
	catch (std::exception& e) {
		std::cout << "[ERROR] RSA-exception thrown" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;
}
