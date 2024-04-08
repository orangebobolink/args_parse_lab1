#pragma once
#include <string>
#include <optional>

namespace types
{
	template<typename T>
	struct Result {
		std::optional<T> data;
		std::string error;

		Result(T data)
			: data(data) {}
		Result(std::string error)
			: error(move(error)) {}
	};
}