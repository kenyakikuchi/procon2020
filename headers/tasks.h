#ifndef task_h
#define task_h

#include <typeinfo>
#include "util.h"

using namespace std;

namespace procon2020 {
	class tasks : public util
	{
	private:
	public:
		tasks(picojson::object);
		~tasks();
	};

	tasks::tasks(picojson::object o) : util(o, key_tasks)
	{
	}

	tasks::~tasks()
	{
	}
}

#endif // task_h