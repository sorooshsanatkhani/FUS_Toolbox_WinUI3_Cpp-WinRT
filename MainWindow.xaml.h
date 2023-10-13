// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "MainWindow.g.h"
#include "FUS.h"
#include <winrt/Windows.System.Threading.h>

namespace winrt::FUSapp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void CheckDevice_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void NumberBox_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void PulseDuration_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void DutyCycle_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void PRF_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void GenerateWaveform_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Abort_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        
        void OnTick(Windows::System::Threading::ThreadPoolTimer const&);
        void OnPeriodicTick(Windows::System::Threading::ThreadPoolTimer const&);

        Windows::System::Threading::ThreadPoolTimer timer{ nullptr };
        Windows::System::Threading::ThreadPoolTimer periodicTimer{ nullptr };
        Windows::Foundation::DateTime startTime;
    };
}

namespace winrt::FUSapp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
