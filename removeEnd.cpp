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