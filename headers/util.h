#ifndef util_h
#define util_h

#define NO_FILENAME "no input filename"
#define SHOW_FILENAME "question-filename : "
#define FAILED_TO_OPEN_QUESTION_FILE "failed to open question-file. : "
#define FAILED_TO_PARSE "failed to parse question-string. : "
#define FAILED_TO_MAKE_STM "failed to create skills/tasks/members. : "

#include <iostream>
#include <string>
#include "../picojson/picojson.h"

using namespace std;

// スキル・タスク・メンバーの共通親クラス
namespace procon2020 {
	const string key_skills = "skills";
	const string key_tasks = "tasks";
	const string key_members = "members";

	class util
	{
	private:
	protected:
		string key;
		picojson::value value;
	public:
		util(picojson::object, string);
		~util();
	};

	util::util(picojson::object o, string key)
	{
		value = o[key];
		cout << key << ": " << value.serialize() << "\n" << endl;
	}

	util::~util()
	{
	}
}

#endif // util_h