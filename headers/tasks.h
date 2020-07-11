/*
タスク：IDと名前の辞書
*/

#ifndef task_h
#define task_h

#include <typeinfo>
#include <random>
#include "util.h"
#include "members.h"

using namespace std;

namespace procon2020 {
	class tasks : public util
	{
	private:
		vector<picojson::value> available_tasks;	// 実タスク一覧
		vector<vector<int>> available_members;		// 実タスクを実行可能なメンバー
	public:
		tasks(picojson::object);
		~tasks();
		void show_available_tasks();
		void check_available_members(procon2020::members);
		void show_available_members(procon2020::members);
		void assign_random();
	};

	tasks::tasks(picojson::object o) : util(o, key_tasks)
	{
		// 実タスク取得：タスク一覧から実行可能タスクのみ抜き出す
		for (auto task : array) {
			picojson::value skillIds = task.get<picojson::object>()["skillIds"];
			if (skillIds.evaluate_as_boolean()) {
				available_tasks.push_back(task);
			}
		}

		// 実行可能メンバー検索：タスクごとに、必要なスキルをすべて持ったメンバーのIDを保持する
		// 乱択割り当て：実行する必要のあるタスクを、実行可能なメンバーからランダムに割り当てる
	}

	tasks::~tasks()
	{
	}

	// 実タスク一覧を表示する
	void tasks::show_available_tasks() {
		cout << "available_tasks:" << endl;
		for (auto t : available_tasks) {
			cout << t << endl;
		}
		cout << endl;
	}

	// 与えられたタスク一覧について、実行可能なメンバーを求める
	void tasks::check_available_members(procon2020::members mems) {
		for (auto task : available_tasks) {
			vector<int> available_member = mems.judge_task(task);
			available_members.push_back(available_member);
		}
	}

	// available_tasksの並び順に、実行可能なメンバー一覧を表示する
	void tasks::show_available_members(procon2020::members mems) {
		cout << "available_members:" << endl;
		for (auto available_member : available_members) {
			for (auto member_id : available_member) {
				cout << mems.get_array()[member_id - 1] << endl;
			}
			cout << endl;
		}
	}

	void tasks::assign_random() {
		// メルセンヌ・ツイスター法による擬似乱数生成器を、
		// ハードウェア乱数をシードにして初期化
		random_device seed_gen;
		mt19937 engine(seed_gen());

		// 整数の一様分布：最小値, 最大値
		uniform_int_distribution<> dist(0, 3);

		// 100個くらい出力
		for (int i=0; i<100; i++) {
			cout << dist(engine) << endl;
		}
	}
}

#endif // task_h