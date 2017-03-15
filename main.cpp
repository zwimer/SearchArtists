#include <algorithm>
#include <iostream>
#include <sstream>

// External libraries
#include <curl/curl.h>
#include <json.hpp>

// For readability
using json = nlohmann::json;


// Append ptr to data. Called by curl
size_t write_callback(char * ptr, size_t size, size_t nmemb, void * data) {
	((std::string *) data)->append(ptr, size * nmemb);
	return size * nmemb;
}

// Read data from url into a string
inline std::string gatherData(const std::string & url) {

	//The data to be returned
	std::string ret;
	
	//Create a new CURL
	CURL * curl = curl_easy_init();

	// When data is read, call write_callback with 4th arg: ret
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);

	// Get information from the url url
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	// Preform the download
	curl_easy_perform(curl);

	// Clean up
	curl_easy_cleanup(curl);
	curl_global_cleanup();

	// Return the string efficiently
	return std::move(ret);
}

// Search for who
auto search( std::string who ) {

	// Construct the url
	std::string url("https://itunes.apple.com/search?term=");
	replace(who.begin(), who.end(), ' ', '+');
	url += who;
	
	// Efficiently return a json of the what is at url
	return std::move( json::parse( gatherData( url ) ) );
}

int main() {

	// Collect data
	std::string who = "jack johnson";
	auto js = search( who );

	// Separate number of tracks from media
	auto media = js["results"];
	int n = js["resultCount"];

	// Print out name of tracks
	for(int i = 0; i < n; i++)
		std::cout << media[i]["trackName"] << '\n';

	std::cout << " n = " << n << std::endl;



	return 0;
}

















#if 0

// special iterator member functions for objects
for (auto i : o) {
	cout << i << '\n';
	break;
	for (auto k : i) {
		cout << k << '\n';
		break;
	}
}
#endif
