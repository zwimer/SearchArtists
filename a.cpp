#include <sstream>
#include <fstream>
#include <iostream>

#include <json.hpp>

using namespace std;

// For convenience
using json = nlohmann::json;

int main() {

	ifstream f("/Users/zwimer/Desktop/tst.txt");
	stringstream s; s << f.rdbuf(); f.close();

	auto js = json::parse(s.str());
	auto media = js["results"];
	int n = js["resultCount"];

	for(int i = 0; i < n; i++)
		cout << media[i]["trackName"] << '\n';

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
