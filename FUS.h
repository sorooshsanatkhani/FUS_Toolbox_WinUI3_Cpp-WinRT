// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 26 October, 2023

#pragma once
#include <visa.h>
#pragma comment(lib,"visa64.lib")

namespace FUS
{
    struct DeviceOutput
    {
        std::wstring Message;
        bool ConnectionStatus{};
        ViSession VISAsession{};
        ViSession Manager{};
        ViStatus deviceStatus{};
    };

    class WaveformGenerator
    {
    public:
        std::pair<std::wstring, int> GetDeviceStatus();
        DeviceOutput Burst_ON(int,int, double, double);
        void Stop(ViSession, ViSession, ViStatus);
    };

    std::wstring removeEnd(std::wstring str);
}