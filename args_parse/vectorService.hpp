#pragma once
#include <args/arg.hpp>
#include <vector>
#include <tuple>

namespace args_parse
{

    /// @brief Вызов каждого элемента вектора.
    /// 
    /// Вызывается каждый элемнт вектора, где идет определение какой процесс вызвать (с параметром или без).
    /// 
    /// @attention
    /// Если value = "", то праметра нет.
    ///
    void invokeProcesses(
        /// Вектор процессов.
        std::vector< std::tuple<args::Arg, std::string>> vector);
} /* namespace args_parse */