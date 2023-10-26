// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 26 October, 2023

#pragma once

#include "App.xaml.g.h"

namespace winrt::FUSapp::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
