#include "vectorService.hpp"

namespace args_parse
{
	void invokeProcesses(vector<tuple<Arg, string>> vector)
	{
		for (tuple<Arg, string> tuple : vector)
		{
			Arg arg = std::get<Arg>(tuple);
			string value = std::get<string>(tuple);

			if (value == "")
			{
				arg.process();
			}
			else
			{
				arg.processWithValue(value);
			}
		}
	}
}