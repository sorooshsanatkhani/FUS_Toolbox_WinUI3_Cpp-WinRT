// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 26 October, 2023

#pragma once

#include "MainWindow.g.h"
#include "FUS.h"
#include <winrt/Windows.System.Threading.h>

namespace winrt::FUSapp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void CheckDevice_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void NumberBox_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void PulseDuration_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void DutyCycle_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void PRF_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void GenerateWaveform_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Abort_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void OnTick(Windows::System::Threading::ThreadPoolTimer const&);

        Windows::System::Threading::ThreadPoolTimer timer{ nullptr };
        Windows::Foundation::DateTime startTime;
    };
}

namespace winrt::FUSapp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
