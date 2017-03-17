#include "Search.hpp"
#include "Error.hpp"
#include "main.hpp"


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

    // Get information from the url: url
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Preform the download
    curl_easy_perform(curl);

    // Clean up
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    // If ret is empty, note so
    bool isBad = true;
    for(size_t i = 0; i < ret.size(); ++i) {
        if (!isspace(ret[i])) {
            isBad = false;
            break;
        }
    }

    // If the string is bad, throw an exception
    if (isBad) throw new Error("Curl failed. Check your wifi");

    // Return the string efficiently
    return std::move(ret);
}

// Search for who, return a parsed json
json search( std::string who ) {

    // Construct the url
    std::string url("https://itunes.apple.com/search?term=");
    replace(who.begin(), who.end(), ' ', '+');
    url += who;

    // Efficiently return a json of the what is at url
    return std::move( jsn::parse( gatherData( url ) ) );
}
