#include <iostream>
#include <string>
#include "../picojson/picojson.h"

using namespace std;

namespace procon2020 {
	class skills
	{
	private:
		const string key_string = "skills";
		picojson::value row_value;
		string row_string;
	public:
		skills(picojson::object);
		~skills();
		string get_row_string() { return row_string; }
	};
}
