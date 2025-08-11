#pragma once

#include <vector>
#include <string>

class static_vector
{
public:
    static std::vector<std::string> &get_vector()
    {
        static std::vector<std::string> vector_;
        return vector_;
    }
};