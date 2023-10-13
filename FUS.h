#pragma once
#include <visa.h>
#pragma comment(lib,"visa64.lib")

namespace FUS
{
    struct DeviceOutput
    {
        std::wstring Message;
        bool ConnectionStatus;
        ViSession VISAsession;
        ViSession Manager;
        ViStatus deviceStatus;
    };

    class WaveformGenerator
    {
    public:
        std::pair<std::wstring, int> GetDeviceStatus();
        DeviceOutput Burst_ON(int,int, double, double,int);
        void Stop(ViSession, ViSession, ViStatus);
    };

    std::wstring removeEnd(std::wstring str);
}