#include <iostream>
#include <string>
#include "../picojson/picojson.h"

using namespace std;

namespace procon2020 {
	class members
	{
	private:
		const string key_string = "members";
		picojson::value row_value;
		string row_string;
	public:
		members(picojson::object);
		~members();
		string get_row_string() { return row_string; }
	};
}
