#include "../headers/skills.h"

using namespace std;

namespace procon2020 {
	skills::skills(picojson::object o)
	{
		row_value = o["skills"];
		row_string = row_value.serialize();

		cout << key_string << ": " << row_string << "\n" << endl;
	}

	skills::~skills()
	{
	}
}
