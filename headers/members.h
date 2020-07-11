#ifndef members_h
#define members_h

#include <typeinfo>
#include "util.h"

using namespace std;

namespace procon2020 {
	class members : public util
	{
	private:
	public:
		members(picojson::object);
		~members();
		vector<int> judge_task(picojson::value);
	};

	members::members(picojson::object o) : util(o, key_members)
	{
	}

	members::~members() {
	}

	// 与えられた実タスクを実施可能なメンバーのID一覧を返す
	vector<int> members::judge_task(picojson::value task) {
		vector<int> member_ids;

		for (auto member : array) {
			picojson::array skillIds_member = member.get<picojson::object>()["skillIds"].get<picojson::array>();
			bool flag = true;

			// すべてのスキルIDを含むかどうか判定
			for (auto skillId_task : task.get<picojson::object>()["skillIds"].get<picojson::array>()) {
				bool id_flag = false;

				for (auto skillId_member : skillIds_member) {
					if (skillId_member == skillId_task) {
						id_flag = true;
						break;
					}
				}

				if (id_flag == false) {
					flag = false;
				}
			}

			// すべてのスキルIDを含んでいる場合、返り値にメンバIDを入れる
			if (flag) {
				member_ids.push_back(member.get<picojson::object>()["id"].get<double>());
			}
		}

		return member_ids;
	}
}

#endif // members_h