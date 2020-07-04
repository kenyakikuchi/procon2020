#ifndef task_h
#define task_h

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

#endif // task_h