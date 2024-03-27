#pragma once
#include <vector>
#include <tuple>
#include "arg.hpp"

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
        vector<tuple<Arg, string>> vector);
} /* namespace args_parse */