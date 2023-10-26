// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 26 October, 2023

#include "pch.h"
#include "FUS.h"

namespace FUS {

    std::wstring removeEnd(std::wstring str)
    {
        while (!str.empty() && str.back() == str[str.size() - 1])
        {
            str.pop_back();
        }
        return str;
    }

} // namespace FUS