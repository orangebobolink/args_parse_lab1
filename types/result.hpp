#pragma once
#include <string>
#include <optional>
#include <utility>

namespace types
{
	struct ErrorCase {
		std::string description;

		ErrorCase(std::string err)
			:  description(std::move(err)) {}
	};

	template<typename T>
	struct Result {
		std::optional<T> data;
		std::string error;

		Result(){}
		Result(ErrorCase && err)
			: data(), error(std::move(err.description)) {}
		Result(T data)
			: data(data), error() {}
		bool isOk() const {
			return data.has_value();
		}
	};
}