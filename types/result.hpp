#include <string>

namespace types
{
	template<typename T>
	struct Result {
		bool success;
		T data;
		std::string error;

		Result(bool success, T data, std::string error)
			: success(success), data(data), error(error) {}
		Result(bool success, T data)
			: success(success), data(data), error("") {}
		Result(std::string)
			: success(false), data(T()), error(error) {}
	};
}