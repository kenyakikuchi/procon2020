#include "../headers/tasks.h"

using namespace std;

namespace procon2020 {
	tasks::tasks(picojson::object o)
	{
		row_value = o[key_string];
		row_string = row_value.serialize();

		cout << key_string << ": " << row_string << "\n" << endl;
	}

	tasks::~tasks()
	{
	}
}