/*
・文言の定数定義
・タスク、スキル、メンバーの基底クラス…と言ってもあまり共通化できなかった
*/

#ifndef util_h
#define util_h

#define MSG001_NO_FILENAME "no input filename"
#define MSG002_SHOW_FILENAME "question-filename:\n"
#define MSG003_FAILED_TO_OPEN_QUESTION_FILE "failed to open question-file:\n"
#define MSG004_FAILED_TO_PARSE "failed to parse question-string:\n"
#define MSG005_FAILED_TO_MAKE_STM "failed to create skills/tasks/members:\n"

#include <iostream>
#include <string>
#include <vector>
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
		picojson::value value;			// STMキーで分割したもの
		vector<picojson::value> array;	// 分割したSTMをvectorに直したもの
	public:
		util(picojson::object, string);
		~util();
		vector<picojson::value> get_array() { return array; }
	};

	util::util(picojson::object o, string key)
	{
		// キーごとにオブジェクトの配列を持っていることまでは共通
		value = o[key];
		array = value.get<picojson::array>();
	}

	util::~util()
	{
	}
}

#endif // util_h