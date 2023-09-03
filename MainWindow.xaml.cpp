// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FUSapp::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        Title(L"Focused Ultrasound Setup"); // Set the title bar
        Frequency().Value(500000);
        Amplitude().Value(160);
        PulseDuration().Value(10);
        DutyCycle().Value(2);
        PRF().Value(2);
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::CheckDevice_Click(IInspectable const&, RoutedEventArgs const&)
    {
        FUS::WaveformGenerator FuncGen;
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
        Amplitude().Value(round(Amplitude().Value()));
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

        if (Amplitude().Text().empty())
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
            FUS::WaveformGenerator FuncGen;

            std::pair<std::wstring, bool> burst_result = FuncGen.Burst(
                Frequency().Value(),
                Amplitude().Value(),
                PulseDuration().Value(),
                DutyCycle().Value(),
                Lenght().Value());

            // Create a ContentDialog
            ContentDialog dialog;
            if (burst_result.second)
                dialog.Title(box_value(L"Waveform Generated Successfully!"));
            else
            {
                dialog.Title(box_value(L"Error!"));
                dialog.Content(box_value(burst_result.first));
            }
            dialog.CloseButtonText(L"Okay");

            // Set the XamlRoot of the ContentDialog
            dialog.XamlRoot(GenerateWaveform().XamlRoot());

            // Show the ContentDialog
            dialog.ShowAsync();
        }
    }

    void MainWindow::Abort_Click(IInspectable const&, RoutedEventArgs const&)
    {
        FUS::WaveformGenerator FuncGen2;
        FuncGen2.Stop();
    }
}
