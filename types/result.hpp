#pragma once
#include <string>
#include <optional>

namespace types
{
	template<typename T>
	struct Result {
		std::optional<T> data;
		std::exception error;

		Result(const std::exception& error)
			: data(), error(error) {}
		Result(T data)
			: data(data), error("") {}

		bool isOk() const {
			return data.has_value();
		}
	};
}