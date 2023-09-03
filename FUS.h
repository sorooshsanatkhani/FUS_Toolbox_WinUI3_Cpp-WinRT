#pragma once

namespace FUS
{
    class WaveformGenerator
    {
    public:
        std::pair<std::wstring, int> WaveformGenerator::GetDeviceStatus();
        std::pair<std::wstring, bool> WaveformGenerator::Burst(int,int, double, double,int);
        void WaveformGenerator::Stop();
    };

    std::wstring removeEnd(std::wstring str);
}