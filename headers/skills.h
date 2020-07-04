#ifndef skills_h
#define skills_h

#include "util.h"

using namespace std;

namespace procon2020 {
	class skills : public util
	{
	private:
	public:
		skills(picojson::object);
		~skills();
	};

	skills::skills(picojson::object o) : util(o, key_skills)
	{
	}

	skills::~skills()
	{
	}
}

#endif // skills_h