#ifndef members_h
#define members_h

#include "util.h"

using namespace std;

namespace procon2020 {
	class members : public util
	{
	private:
	public:
		members(picojson::object);
		~members();
	};

	members::members(picojson::object o) : util(o, key_members)
	{
	}

	members::~members() {
	}
}

#endif // members_h