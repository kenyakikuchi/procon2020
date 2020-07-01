#include <iostream>
#include <string>
#include "../picojson/picojson.h"

using namespace std;

namespace procon2020 {
	class tasks
	{
	private:
		const string key_string = "tasks";
		picojson::value row_value;
		string row_string;
	public:
		tasks(picojson::object);
		~tasks();
		string get_row_string() { return row_string; }
	};
}
