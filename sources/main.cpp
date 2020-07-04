#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../headers/util.h"
#include "../headers/skills.h"
#include "../headers/tasks.h"
#include "../headers/members.h"
#include "../picojson/picojson.h"

using namespace util;
using namespace std;

string question_filename;				// 問題ファイル名
string answer_path = "../answer/";		// 回答出力先
string answer_filename = "answer.json";	// 回答ファイル名

ifstream ifs;	// 問題読み取りストリーム
ofstream ofs;	// 回答出力ストリーム

picojson::value v;

procon2020::skills* s;		// スキル
procon2020::tasks* t;		// タスク
procon2020::members* m;		// メンバー

int main(int argc, char** argv)
{
	// コマンドライン引数でファイルが指定されているか確認
	if (argv[1] == NULL) {
		cout << "no input file." << endl;
		exit(0);
	}

	// 問題ファイル名を一応表示
	question_filename = argv[1];
	cout << question_filename << "\n" << endl;

	// 問題ファイルを開く
	ifs.open(question_filename, ios::in);
	istream& json = ifs;

	// 開いた問題をpicojsonクラスに渡す
	picojson::parse(v, ifs);

	// skills, tasks, membersを作成する
	picojson::object& obj = v.get<picojson::object>();
	s = new procon2020::skills(obj);
	t = new procon2020::tasks(obj);
	m = new procon2020::members(obj);

	//// 回答を出力する
	/*ofs.open(answer_path + answer_filename, ios::out);
	ofs << s->get_row_string() << endl;*/

	ifs.close();
	//ofs.close();

	return 0;
}
