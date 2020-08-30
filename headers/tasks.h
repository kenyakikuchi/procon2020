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
		vector<picojson::value> all_tasks;
		vector<picojson::value> parent_tasks;
		vector<picojson::value> remaining_tasks;
		vector<picojson::value> available_tasks;
		vector<vector<int>> available_members;
		vector<int> assign_members;
		vector<vector<int>> task_days;
		vector<string> completed_tasks;
	public:
		tasks(picojson::object);
		~tasks();
		void show_all_tasks();
		void show_available_tasks();
		void check_available_members(procon2020::members);
		void show_available_members(procon2020::members);
		void assign_random();
		void calc_days();
		void output_answer();
	};

	tasks::tasks(picojson::object o) : util(o, key_tasks)
	{
		for (auto task : array) {
			picojson::value skillIds = task.get<picojson::object>()["skillIds"];
			remaining_tasks.push_back(task);
			if (skillIds.evaluate_as_boolean()) {
				available_tasks.push_back(task);
				task_days.push_back({ 0, 0 });
			}
			else {
				parent_tasks.push_back(task);
			}
		}
	}

	tasks::~tasks()
	{
	}

	// タスク一覧を表示する
	void tasks::show_all_tasks() {
		cout << "task_list:" << endl;
		for (auto task : array) {
			cout << task << endl;
		}
		cout << endl;
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

		for (auto available_member : available_members) {
			// 整数の一様分布：最小値, 最大値
			uniform_int_distribution<> dist(0, available_member.size()-1);

			//cout << available_member[dist(engine)] << endl;
			//cout << dist(engine) << endl;
			//cout << available_member.size()-1 << endl;

			assign_members.push_back(available_member[dist(engine)]);
		}

		for (auto assign_member : assign_members) {
			//cout << assign_member << endl;
		}
	}

	void tasks::calc_days() {
		int current_day = 0;

		int index = 0;

		// 完遂できないタイプの割り当て
		for (auto task : available_tasks) {
			int duration = stoi(task.get<picojson::object>()["duration"].to_str());

			task_days[index][0] = current_day;
			current_day += duration;
			task_days[index][1] = current_day;

			++index;
		}

		// てきと割り当て
		/*for (auto task : available_tasks) {
			string id = task.get<picojson::object>()["id"].to_str();
			picojson::value predecessorIds = task.get<picojson::object>()["predecessorIds"];
			int duration = stoi(task.get<picojson::object>()["duration"].to_str());
			
			if (predecessorIds.to_str() == "null") {
				task_days[index][0] = current_day;
				task_days[index][1] = current_day + duration;
				completed_tasks.push_back(id);
				break;
			}
			++index;
		}*/

		for (auto days : task_days) {
			//cout << days[0] << ", " << days[1] << endl;
		}
	}

	void tasks::output_answer() {
		int i = 0;
		cout << "[" << endl;
		for (auto task : available_tasks) {
			cout << "{" << endl;
			cout << "\"taskId\":" << task.get<picojson::object>()["id"].to_str() << "," << endl;
			cout << "\"memberId\":" << assign_members[i] << "," << endl;
			cout << "\"startDay\":" << task_days[i][0] << "," << endl;
			cout << "\"endDay\":" << task_days[i][1] << "" << endl;
			cout << "}," << endl;
			
			++i;
		}
		cout << "]" << endl;
	}
}

#endif // task_h