#pragma once
#include <args/arg.hpp>
#include <vector>
#include <tuple>
#include <memory>

namespace args_parse
{

	/// @brief Вызов каждого элемента вектора.
	/// 
	/// Вызывается каждый элемнт вектора, где идет определение какой процесс вызвать (с параметром или без).
	/// 
	/// @attention
	/// Если value = "", то праметра нет.
	///
	types::Result<bool> invokeProcesses(
		/// Вектор процессов.
		std::vector<args::Arg*> vector);
} /* namespace args_parse */