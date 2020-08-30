#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../headers/util.h"
#include "../headers/skills.h"
#include "../headers/tasks.h"
#include "../headers/members.h"
#include "../picojson/picojson.h"

using namespace std;

string question_filename;				// 問題ファイル名
string answer_path = "../answer/";		// 回答出力先
string answer_filename = "answer.json";	// 回答ファイル名

ifstream ifs;	// 問題読み取りストリーム
ofstream ofs;	// 回答出力ストリーム

picojson::value value;			// パースした問題文

procon2020::skills* skills;		// スキル
procon2020::tasks* tasks;		// タスク
procon2020::members* members;	// メンバー

int main(int argc, char** argv)
{
	// コマンドライン引数でファイルが指定されているか確認
	if (argv[1] == NULL) {
		cout << MSG001_NO_FILENAME << endl;
		exit(0);
	}

	// 問題ファイル名を一応表示
	question_filename = argv[1];
	//cout << MSG002_SHOW_FILENAME << question_filename << "\n" << endl;

	// 問題ファイルを開く
	ifs.open(question_filename, ios::in);
	if (ifs.fail()) {
		cerr << MSG003_FAILED_TO_OPEN_QUESTION_FILE << question_filename << endl;
		exit(1);
	}

	// 開いた問題をパースしてvalueに渡し、ファイルを閉じる
	try {
		picojson::parse(value, ifs);
		ifs.close();
	}
	catch (const exception& e)
	{
		cerr << MSG004_FAILED_TO_PARSE << e.what() << endl;
		exit(2);
	}

	// skills, tasks, membersを作成する
	try {
		picojson::object& obj = value.get<picojson::object>();
		skills = new procon2020::skills(obj);
		members = new procon2020::members(obj);
		tasks = new procon2020::tasks(obj);
	}
	catch (const exception& e)
	{
		cerr << MSG005_FAILED_TO_MAKE_STM << e.what() << endl;
		exit(3);
	}

	// タスク一覧を出力する
	//tasks->show_all_tasks();

	// 実タスクを出力する
	//tasks->show_available_tasks();

	// 実タスクに対し、実行可能なメンバーを求める
	tasks->check_available_members(*members);
	//tasks->show_available_members(*members);

	// 実タスクに対し、実行メンバーをランダムに割り当てる
	tasks->assign_random();

	// タスクの実行順を決める
	tasks->calc_days();

	// 回答を出力する
	//ofs.open(answer_path + answer_filename, ios::out);
	//ofs << s->get_row_string() << endl;
	tasks->output_answer();

	//ofs.close();

	return 0;
}