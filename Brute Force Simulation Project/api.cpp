#include <curl/curl.h>
#include <iostream>
#include "api.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool tryLogin(const std::string& username, const std::string& password) {
	CURL* curl;
	CURLcode res;
	bool success = false;
	std::string responseBuffer;

	curl = curl_easy_init();
	if (curl) {
		std::string url = "http://localhost:5000/login";
		std::string postData = "username=" + username + "&password=" + password;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

		res = curl_easy_perform(curl);

		if (responseBuffer.find("\"status\":\"success\"") != std::string::npos) {
			std::cout << "Tried password: " << password << " -> Request sent successfully." << std::endl;
			success = true;
		}
		/*else {
			std::cerr << "Error sending request: " << curl_easy_strerror(res) << std::endl;
		}*/

		curl_easy_cleanup(curl);
	}
	
	return success;
}
