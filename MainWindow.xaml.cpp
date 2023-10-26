// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 26 October, 2023

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Windows.UI.Core.h>
#include <windows.applicationmodel.core.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::ApplicationModel::Core;


FUS::WaveformGenerator FuncGen;
FUS::DeviceOutput FuncGenOutput;

ThreadPoolTimer timer{ nullptr };


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FUSapp::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        Title(L"Focused Ultrasound Setup"); // Set the title bar
        Frequency().Value(500000);
        Amplitudepp().Value(100);
        PulseDuration().Value(10);
        DutyCycle().Value(2);
        PRF().Value(2);
    }

    void MainWindow::CheckDevice_Click(IInspectable const&, RoutedEventArgs const&)
    {
        std::pair<std::wstring, int> devicestatus = FuncGen.GetDeviceStatus();

        // Create a ContentDialog
        ContentDialog dialog;
        if (devicestatus.second == 1)
        {
            dialog.Title(box_value(L"Device Recognized"));
            dialog.Content(box_value(devicestatus.first));
        }
        else
        {
            dialog.Title(box_value(L"Error!"));
            dialog.Content(box_value(devicestatus.first));
        }

        dialog.CloseButtonText(L"Okay");

        // Set the XamlRoot of the ContentDialog
        dialog.XamlRoot(CheckDevice().XamlRoot());

        // Show the ContentDialog
        dialog.ShowAsync();
    }

    void MainWindow::NumberBox_ValueChanged(IInspectable const&, NumberBoxValueChangedEventArgs const&)
    {
        // Round the value to an integer
        Frequency().Value(round(Frequency().Value()));

        if (Amplitudepp().Value() > 150)
        {
            Amplitudepp().Value(150);
        }
        else
        {
            Amplitudepp().Value(round(Amplitudepp().Value()));
        }
        
        Lenght().Value(round(Lenght().Value()));
    }
    void MainWindow::PulseDuration_ValueChanged(IInspectable const&, NumberBoxValueChangedEventArgs const&)
    {
        // Round the value to an integer
        PulseDuration().Value(round(PulseDuration().Value() * 10.) / 10.);
        DutyCycle().Value(round(((PulseDuration().Value() / 1000.) * PRF().Value()) * 100. * 10) / 10.);
    }
    void MainWindow::DutyCycle_ValueChanged(IInspectable const&, NumberBoxValueChangedEventArgs const&)
    {
        // Round the value to an integer
        DutyCycle().Value(round(DutyCycle().Value() * 10.) / 10.);
        PRF().Value(round((DutyCycle().Value() / 100.) / (PulseDuration().Value() / 1000.) * 10.) / 10.);
    }
    void MainWindow::PRF_ValueChanged(IInspectable const&, NumberBoxValueChangedEventArgs const&)
    {
        // Round the value to an integer
        PRF().Value(round(PRF().Value() * 10.) / 10.);
        PulseDuration().Value(round(((DutyCycle().Value() / 100.) / PRF().Value()) * 1000. * 10.) / 10.);
    }

    auto startTime = clock::now();
    int SonicationDuration = 0;
    void MainWindow::GenerateWaveform_Click(IInspectable const&, RoutedEventArgs const&)
    {
        bool allTextBoxesFilled = true;
        if (Frequency().Text().empty())
        {
            warningTextBlock1().Text(L"Please enter a number");
            allTextBoxesFilled = false;
        }
        else
        {
            warningTextBlock1().Text(L"");
        }

        if (Amplitudepp().Text().empty())
        {
            warningTextBlock2().Text(L"Please enter a number");
            allTextBoxesFilled = false;
        }
        else
        {
            warningTextBlock2().Text(L"");
        }

        if (PulseDuration().Text().empty())
        {
            warningTextBlock3().Text(L"Please enter a number");
            allTextBoxesFilled = false;
        }
        else
        {
            warningTextBlock3().Text(L"");
        }

        if (DutyCycle().Text().empty())
        {
            warningTextBlock4().Text(L"Please enter a number");
            allTextBoxesFilled = false;
        }
        else
        {
            warningTextBlock4().Text(L"");
        }

        if (Lenght().Text().empty())
        {
            warningTextBlock5().Text(L"Please enter a number");
            allTextBoxesFilled = false;
        }
        else
        {
            warningTextBlock5().Text(L"");
        }

        if (allTextBoxesFilled)
        {
            SonicationDuration = Lenght().Value();

            TimeSpan delay = std::chrono::duration_cast<TimeSpan>(std::chrono::seconds(static_cast<int64_t>(Lenght().Value())));
            
            FuncGenOutput = FuncGen.Burst_ON(
                Frequency().Value(),
                Amplitudepp().Value(),
                PulseDuration().Value(),
                DutyCycle().Value());
            
            timer = ThreadPoolTimer::CreateTimer(
                { get_weak(), &MainWindow::OnTick },
                delay);
        }
    }

    void MainWindow::OnTick(ThreadPoolTimer const& timer)
    {
        timer.Cancel();
        FuncGen.Stop(FuncGenOutput.Manager, FuncGenOutput.VISAsession, FuncGenOutput.deviceStatus);
    }

    void MainWindow::Abort_Click(IInspectable const&, RoutedEventArgs const&)
    {
        timer.Cancel();
        FuncGen.Stop(FuncGenOutput.Manager, FuncGenOutput.VISAsession, FuncGenOutput.deviceStatus);
    }
}