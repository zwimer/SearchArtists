#ifndef MAIN_HPP
#define MAIN_HPP

// OSI approved external libraries
#include <curl/curl.h>
#include <json.hpp>

// For readability
using jsn = nlohmann::json;

// For clarity (this type is huge to type by hand)
typedef decltype(jsn::parse("")) json;

#endif // MAIN_HPP
