/*
Copyright 2009-2010 Cybozu Labs, Inc.
Copyright 2011-2014 Kazuho Oku
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

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
