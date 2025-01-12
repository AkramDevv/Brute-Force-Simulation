#include <omp.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "api.h"
#include "bfAttack.h"


void generatePasswords(std::ofstream& outFile, const std::vector<std::string>& keywords, std::vector<std::string>& buffer, std::string prefix, int length, int& bufferMaxLength) {

	if (length == 0) {
		buffer.push_back(prefix);
		if (buffer.size() >= bufferMaxLength) {
			#pragma omp critical
			{
				if (outFile.is_open()) {
					for (const std::string password : buffer) {
						outFile << password << std::endl;
					}
				}
			}
			buffer.clear();
		}
		return;
	}

	#pragma omp parallel for
	{
		for (auto key : keywords)
			generatePasswords(outFile, keywords, buffer, prefix + key, length - 1, bufferMaxLength);
	}
}

void savePasswords(const std::vector<std::string>& keywords,const std::string& fileName) {

	std::ofstream outFile(fileName + ".txt", std::ios::app);

	if (!outFile.is_open()) {
		std::cerr << "Error! Unable to open file!" << std::endl;
		return;
	}

	std::string prefix = "";
	int maxLength = 4;
	std::vector<std::string> buffer;
	int bufferMaxLength = 500000;

	#pragma omp parallel for
	{
		for (int length = 1;length <= maxLength;++length) {

			generatePasswords(outFile, keywords, buffer, prefix, length, bufferMaxLength);

		}
	}

	if (!buffer.empty()) {
		for (auto password : buffer) {
			outFile << password << std::endl;
		}
		buffer.clear();
	}

	outFile.close();
	std::cout << "Passwords successfully saved!" << std::endl;

}

int main() {

	//std::vector<std::string> keywords;

	//std::string userName{};
	//std::string userSurname{};
	//std::string userBirthDay{};
	//std::string userGender{};
	//std::string userBirthPlace{};
	//std::string userRegionSerialNum{};
	//std::string userFavNum{};
	//std::string userFavTeam{};
	//std::string userFavColor{};
	//std::string userFavFamous{};
	//std::string userFavAnimal{};
	//std::string userEmail{};
	//std::string userPhoneNumber{};
	//std::string userSocialMediaName{};
	//std::string userMomName{};
	//std::string userDadName{};
	//std::string userLoveName{};
	//std::string userChildhoodNick{};
	//std::string userBrotherName{};
	//std::string userSisterName{};
	//std::string userSpecialDate{};

	//char nameChoice{};
	//std::cout << "Do you know user's name - y | n: ";
	//std::cin >> nameChoice;
	//if (nameChoice == 'y') {
	//	std::cout << "Enter user's name: ";
	//	std::cin >> userName;
	//	keywords.push_back(userName);
	//}

	//char surnameChoice{};
	//std::cout << "Do you know user's surname - y | n: ";
	//std::cin >> surnameChoice;
	//if (surnameChoice == 'y') {
	//	std::cout << "Enter user's surname: ";
	//	std::cin >> userSurname;
	//	keywords.push_back(userSurname);
	//}

	//char birthDayChoice{};
	//std::cout << "Do you know user's birthday - y | n: ";
	//std::cin >> birthDayChoice;
	//if (birthDayChoice == 'y') {
	//	std::cout << "Enter user's birthday: ";
	//	std::cin >> userBirthDay;
	//	keywords.push_back(userBirthDay);
	//}

	//char genderChoice{};
	//std::cout << "Do you know user's gender - y | n: ";
	//std::cin >> genderChoice;
	//if (genderChoice == 'y') {
	//	std::cout << "Enter user's gender: ";
	//	std::cin >> userGender;
	//	keywords.push_back(userGender);
	//}

	//char birthPlaceChoice{};
	//std::cout << "Do you know user's birth place - y | n: ";
	//std::cin >> birthPlaceChoice;
	//if (birthPlaceChoice == 'y') {
	//	std::cout << "Enter user's birth place: ";
	//	std::cin >> userBirthPlace;
	//	keywords.push_back(userBirthPlace);
	//}

	//char regionSerialNumChoice{};
	//std::cout << "Do you know user's region serial number - y | n: ";
	//std::cin >> regionSerialNumChoice;
	//if (regionSerialNumChoice == 'y') {
	//	std::cout << "Enter user's region serial number: ";
	//	std::cin >> userRegionSerialNum;
	//	keywords.push_back(userRegionSerialNum);
	//}

	//char favNumChoice{};
	//std::cout << "Do you know user's favorite number - y | n: ";
	//std::cin >> favNumChoice;
	//if (favNumChoice == 'y') {
	//	std::cout << "Enter user's favorite number: ";
	//	std::cin >> userFavNum;
	//	keywords.push_back(userFavNum);
	//}

	//char favTeamChoice{};
	//std::cout << "Do you know user's favorite team - y | n: ";
	//std::cin >> favTeamChoice;
	//if (favTeamChoice == 'y') {
	//	std::cout << "Enter user's favorite team: ";
	//	std::cin >> userFavTeam;
	//	keywords.push_back(userFavTeam);
	//}

	//char favColorChoice{};
	//std::cout << "Do you know user's favorite color - y | n: ";
	//std::cin >> favColorChoice;
	//if (favColorChoice == 'y') {
	//	std::cout << "Enter user's favorite color: ";
	//	std::cin >> userFavColor;
	//	keywords.push_back(userFavColor);
	//}

	//char favFamousChoice{};
	//std::cout << "Do you know user's favorite singer or film character - y | n: ";
	//std::cin >> favFamousChoice;
	//if (favFamousChoice == 'y') {
	//	std::cout << "Enter user's favorite singer or film character: ";
	//	std::cin >> userFavFamous;
	//	keywords.push_back(userFavFamous);
	//}

	//char favAnimalChoice{};
	//std::cout << "Do you know user's favorite animal - y | n: ";
	//std::cin >> favAnimalChoice;
	//if (favAnimalChoice == 'y') {
	//	std::cout << "Enter user's favorite animal: ";
	//	std::cin >> userFavAnimal;
	//	keywords.push_back(userFavAnimal);
	//}

	//char emailChoice{};
	//std::cout << "Do you know user's email - y | n: ";
	//std::cin >> emailChoice;
	//if (emailChoice == 'y') {
	//	std::cout << "Enter user's email: ";
	//	std::cin >> userEmail;
	//	keywords.push_back(userEmail);
	//}

	//char phoneNumChoice{};
	//std::cout << "Do you know user's phone number - y | n: ";
	//std::cin >> phoneNumChoice;
	//if (phoneNumChoice == 'y') {
	//	std::cout << "Enter user's phone number: ";
	//	std::cin >> userPhoneNumber;
	//	keywords.push_back(userPhoneNumber);
	//}

	//char socialMediaNameChoice{};
	//std::cout << "Do you know user's social media name(instagram, facebook, ...) - y | n: ";
	//std::cin >> socialMediaNameChoice;
	//if (socialMediaNameChoice == 'y') {
	//	std::cout << "Enter user's social media name(instagram, facebook, ...): ";
	//	std::cin >> userSocialMediaName;
	//	keywords.push_back(userSocialMediaName);
	//}

	//char momNameChoice{};
	//std::cout << "Do you know user's mother's name - y | n: ";
	//std::cin >> momNameChoice;
	//if (momNameChoice == 'y') {
	//	std::cout << "Enter user's mother's name: ";
	//	std::cin >> userMomName;
	//	keywords.push_back(userMomName);
	//}

	//char dadNameChoice{};
	//std::cout << "Do you know user's father's name - y | n: ";
	//std::cin >> dadNameChoice;
	//if (dadNameChoice == 'y') {
	//	std::cout << "Enter user's father's name: ";
	//	std::cin >> userDadName;
	//	keywords.push_back(userDadName);
	//}

	//char loveNameChoice{};
	//std::cout << "Do you know user's love name - y | n: ";
	//std::cin >> loveNameChoice;
	//if (loveNameChoice == 'y') {
	//	std::cout << "Enter user's love name: ";
	//	std::cin >> userLoveName;
	//	keywords.push_back(userLoveName);
	//}

	//char childhoodNickChoice{};
	//std::cout << "Do you know user's childhood nick name - y | n: ";
	//std::cin >> childhoodNickChoice;
	//if (childhoodNickChoice == 'y') {
	//	std::cout << "Enter user's childhood nick name: ";
	//	std::cin >> userChildhoodNick;
	//	keywords.push_back(userChildhoodNick);
	//}

	//char brotherNameChoice{};
	//std::cout << "Do you know user's brother's name - y | n: ";
	//std::cin >> brotherNameChoice;
	//if (brotherNameChoice == 'y') {
	//	std::cout << "Enter user's brother's name: ";
	//	std::cin >> userBrotherName;
	//	keywords.push_back(userBrotherName);
	//}

	//char sisterNameChoice{};
	//std::cout << "Do you know user's sister's name - y | n: ";
	//std::cin >> sisterNameChoice;
	//if (sisterNameChoice == 'y') {
	//	std::cout << "Enter user's sister's name: ";
	//	std::cin >> userSisterName;
	//	keywords.push_back(userSisterName);
	//}

	//char specialDateChoice{};
	//std::cout << "Do you know user's special date - y | n: ";
	//std::cin >> specialDateChoice;
	//if (specialDateChoice == 'y') {
	//	std::cout << "Enter user's special date: ";
	//	std::cin >> userSpecialDate;
	//	keywords.push_back(userSpecialDate);
	//}

	//std::string fileName{};
	//std::cout << "Enter passwords file name: ";
	//std::cin >> fileName;

	//savePasswords(keywords, fileName);

	char attackChoice{};
	std::cout << "Do you want brute force attack - y | n: ";
	std::cin >> attackChoice;
	if (attackChoice == 'y') {
		std::string smUserName{};
		std::cout << "Enter user's social media username: ";
		std::cin >> smUserName;
		bruteForceAttack(smUserName, "AliDiqqetPasswords.txt");
	}

	return 0;
}