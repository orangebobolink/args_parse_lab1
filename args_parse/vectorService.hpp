#pragma once
#include <args/arg.hpp>
#include <vector>
#include "parser.hpp"

namespace args_parse
{

	/// @brief Вызов каждого элемента вектора.
	/// 
	/// Вызывается каждый элемнт вектора, где идет определение какой процесс вызвать (с параметром или без).
	/// 
	/// @attention
	/// Если value = "", то праметра нет.
	///
	types::Result<bool> invokeProcesses(std::vector<args::Arg*> vector, const args_parse::Parser* parser);
} /* namespace args_parse */