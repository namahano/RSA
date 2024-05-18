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
		std::cout << "¶¬‚·‚é‘f”‚Ìƒrƒbƒg”‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ";
		std::cin >> bit;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "•½•¶: ";
		std::getline(std::cin, input);

		std::cout << "‘f”‚ð¶¬‚µ‚Ä‚¢‚Ü‚·" << std::endl;
		Crypto::RSA rsa(bit);
		//Crypto::RSA rsa(1951, 1861, 2281);
		Crypto::Encryptor enc(rsa.getPublicKey());
		Crypto::Decryptor dec(rsa.getPrivateKey());

		Crypto::CryptoString encrypted = rsa.encrypt(input);
		std::string decrypted = rsa.decrypt(encrypted);

		printf("\n");

		std::cout << "---- ŒöŠJŒ® ----" << std::endl;
		std::cout << "r = " << rsa.getPublicKey()->r << "\n" << std::endl;
		std::cout << "m = " << rsa.getPublicKey()->m << "\n" << std::endl;
		std::cout << "---- ”é–§Œ® ----\n";
		std::cout << "s = " << rsa.getPrivateKey()->s << "\n" << std::endl;
		std::cout << "p = " << rsa.getPrivateKey()->p << "\n" << std::endl;
		std::cout << "q = " << rsa.getPrivateKey()->q << "\n" << std::endl;

		std::cout << "---- ˆÃ†•¶ ---- \n";
		for (int i = 0; i < encrypted.size(); i++)
			std::cout << encrypted[i];
		printf("\n\n");
		std::cout << "---- •œ†•¶ ----" << "\n" << decrypted << std::endl;

	}
	catch (std::exception& e) {
		std::cout << "[ERROR] RSA-exception thrown" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;
}