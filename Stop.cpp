// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 3 September, 2023

#include "pch.h"
#include "FUS.h"
#include <visa.h>
#pragma comment(lib,"visa64.lib")
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

namespace FUS
{
	void WaveformGenerator::Stop()
	{
		ViSession defaultRM;
		ViSession instr;
		ViUInt32 numInstrs;
		ViFindList findList;
		ViStatus status;
		char instrResourceString[VI_FIND_BUFLEN];
		unsigned char buffer[100];
		status = viOpenDefaultRM(&defaultRM);
		status = viOpen(defaultRM, instrResourceString, VI_NULL, VI_NULL, &instr);
		status = viPrintf(instr, "OUTP:STAT OFF\n");
		if (status < VI_SUCCESS)
		{
			// Error handling
			viClose(instr);
			viClose(defaultRM);
		}

		// Close the session
		viClose(instr);
		viClose(defaultRM);
	}
}