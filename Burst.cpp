#include "pch.h"
#include "FUS.h"
#include <visa.h>
#pragma comment(lib,"visa64.lib")
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

namespace FUS
{
	std::pair<std::wstring, bool> WaveformGenerator::Burst(int Frequency, int Amplitude, double PulseDuration, double DutyCycle, int Lenght)
	{
		ViSession defaultRM;
		ViSession instr;
		ViUInt32 numInstrs;
		ViFindList findList;
		ViStatus status;
		char instrResourceString[VI_FIND_BUFLEN];
		unsigned char buffer[100];
		/** First we must call viOpenDefaultRM to get the manager
		* handle. We will store this handle in defaultRM.*/
		status = viOpenDefaultRM(&defaultRM);
		if (status < VI_SUCCESS)
		{
			//printf("Could not open a session to the VISA Resource Manager!\n");
			return std::make_pair(L"Could not open a session to the VISA Resource Manager!", false);
		}
		/* Find all the USB TMC VISA resources in our system and store the number of resources in the system in
		numInstrs. */
		status = viFindRsrc(defaultRM, "USB?*INSTR", &findList, &numInstrs, instrResourceString);
		if (status < VI_SUCCESS)
		{
			//printf("An error occurred while finding resources.\nPress 'Enter' to continue.");
			viClose(defaultRM);
			return std::make_pair(L"An error occurred while finding resources.\nPress 'Okay' to continue.", false);
		}
		status = viOpen(defaultRM, instrResourceString, VI_NULL, VI_NULL, &instr);
		if (status < VI_SUCCESS)
		{
			//printf("Cannot open a session to the device.\n");
			return std::make_pair(L"Cannot open a session to the device.", false);
		}
		/* * At this point we now have a session open to the USB TMC instrument.
		* We will now use the viPrintf function to send the device the string "*IDN?\n",
		* asking for the device's identification. */
		const char* cmmand = "*IDN?\n";
		status = viPrintf(instr, cmmand);
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			return std::make_pair(L"Error writing to the device.", false);
		}
		/** Now we will attempt to read back a response from the device to
		* the identification query that was sent. We will use the viScanf
		* function to acquire the data.
		* After the data has been read the response is displayed.*/
		status = viScanf(instr, "%t", buffer);
		if (status < VI_SUCCESS)
		{
			//printf("Error reading a response from the device.\n");
			return std::make_pair(L"Error reading a response from the device.", false);
		}

		status = viPrintf(instr, "C1:OUTP LOAD,50\n");
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			return std::make_pair(L"Error writing to the device.", false);
		}



		//status = viPrintf(instr, "C1:BTWV STATE,ON,PRD,0.5,CARR,WVTP,SINE,CARR,FRQ,500000,CARR,AMP,0.16,GATE_NCYC,NCYC,TIME,5000,TRSR,INT\n");
		status = viPrintf(instr, "C1:BTWV STATE,ON,PRD,%f,CARR,WVTP,SINE,CARR,FRQ,%d,CARR,AMP,%f,GATE_NCYC,NCYC,TIME,%f,TRSR,INT\n", (PulseDuration/1000.)/(DutyCycle/100.), Frequency, Amplitude / 1000., round(Frequency* (PulseDuration / 1000.)));
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			return std::make_pair(L"Error writing to the device.", false);
		}
		status = viPrintf(instr, "C1:OUTP ON\n");
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			return std::make_pair(L"Error writing to the device.", false);
		}

		Sleep(Lenght*1000);

		status = viPrintf(instr, "C1:OUTP OFF\n");
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			return std::make_pair(L"Error writing to the device.", false);
		}
		status = viClose(defaultRM);

		if (status == VI_SUCCESS)
			return std::make_pair(L"Done!", true);
		else
			return std::make_pair(L"Error", false);
	}
}