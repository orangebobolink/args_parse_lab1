#pragma once
#include <string>
#include <optional>

namespace types
{
	template<typename T>
	struct Result {
		std::optional<T> data;
		std::string error;

		Result() : error("") {}
		Result(std::string error)
			: data(), error(std::move(error)) {}
		Result(T data)
			: data(data), error("") {}

		bool isOk() const {
			return data.has_value();
		}
	};
}