#pragma once

namespace FUS
{
    class WaveformGenerator
    {
    public:
        std::pair<std::wstring, int> WaveformGenerator::GetDeviceStatus();
        std::pair<std::wstring, bool> WaveformGenerator::Burst(int,int, double, double,int);
        double Add(double num1, double num2);
    };

    std::wstring removeEnd(std::wstring str);
}