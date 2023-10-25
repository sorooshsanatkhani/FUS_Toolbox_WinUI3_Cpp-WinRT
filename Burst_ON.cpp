// Author: Soroosh Sanatkhani
// Columbia University
// Created: 1 August, 2023
// Last Modified : 3 September, 2023

#include "pch.h"
#include "FUS.h"
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

namespace FUS
{
	DeviceOutput WaveformGenerator::Burst_ON(int Frequency, int Amplitudepp, double PulseDuration, double DutyCycle, int Lenght)
	{
		ViSession defaultRM, instr;
		ViStatus status;
		ViUInt32 numInstrs;
		ViFindList findList;
		char instrResourceString[VI_FIND_BUFLEN];
		unsigned char buffer[100];
		DeviceOutput result;
		/** First we must call viOpenDefaultRM to get the manager
		* handle. We will store this handle in defaultRM.*/
		status = viOpenDefaultRM(&defaultRM);
		if (status < VI_SUCCESS)
		{
			//printf("Could not open a session to the VISA Resource Manager!\n");
			//return std::make_pair(L"Could not open a session to the VISA Resource Manager!", false, instr);
			result.Message = L"Could not open a session to the VISA Resource Manager!";
			result.ConnectionStatus = false;
			result.VISAsession = {};
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		/* Find all the USB TMC VISA resources in our system and store the number of resources in the system in
		numInstrs and the resource string in the instrResourceString*/
		status = viFindRsrc(defaultRM, "USB?*INSTR", &findList, &numInstrs, instrResourceString);
		if (status < VI_SUCCESS)
		{
			//printf("An error occurred while finding resources.\nPress 'Enter' to continue.");
			viClose(defaultRM);
			//return std::make_pair(L"An error occurred while finding resources.\nPress 'Okay' to continue.", false, instr);
			result.Message = L"An error occurred while finding resources.\nPress 'Okay' to continue.";
			result.ConnectionStatus = false;
			result.VISAsession = {};
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		status = viOpen(defaultRM, instrResourceString, VI_NULL, VI_NULL, &instr);
		if (status < VI_SUCCESS)
		{
			//printf("Cannot open a session to the device.\n");
			//return std::make_pair(L"Cannot open a session to the device.", false, instr);
			result.Message = L"Cannot open a session to the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
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
			//return std::make_pair(L"Error writing to the device.", false, instr);
			result.Message = L"Error writing to the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		/** Now we will attempt to read back a response from the device to
		* the identification query that was sent. We will use the viScanf
		* function to acquire the data.
		* After the data has been read the response is displayed.*/
		status = viScanf(instr, "%t", buffer);
		if (status < VI_SUCCESS)
		{
			//printf("Error reading a response from the device.\n");
			//return std::make_pair(L"Error reading a response from the device.", false, instr);
			result.Message = L"Error reading a response from the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}

		status = viPrintf(instr, "C1:OUTP LOAD,50\n");
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			//return std::make_pair(L"Error writing to the device.", false, instr);
			result.Message = L"Error writing to the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}

		//status = viPrintf(instr, "C1:BTWV STATE,ON,PRD,0.5,CARR,WVTP,SINE,CARR,FRQ,500000,CARR,AMP,0.16,GATE_NCYC,NCYC,TIME,5000,TRSR,INT\n");
		status = viPrintf(instr, "C1:BTWV STATE,ON,PRD,%f,CARR,WVTP,SINE,CARR,FRQ,%d,CARR,AMP,%f,GATE_NCYC,NCYC,TIME,%f,TRSR,INT\n", (PulseDuration/1000.)/(DutyCycle/100.), Frequency, Amplitudepp / 2000., round(Frequency* (PulseDuration / 1000.)));
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			//return std::make_pair(L"Error writing to the device.", false, instr);
			result.Message = L"Error writing to the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		status = viPrintf(instr, "C1:OUTP ON\n");
		if (status < VI_SUCCESS)
		{
			//printf("Error writing to the device.\n");
			status = viClose(instr);
			//return std::make_pair(L"Error writing to the device.", false, instr);
			result.Message = L"Error writing to the device.";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}

		if (status == VI_SUCCESS)
		{
			result.Message = L"Done!";
			result.ConnectionStatus = true;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		else
		{
			result.Message = L"Error!";
			result.ConnectionStatus = false;
			result.VISAsession = instr;
			result.Manager = defaultRM;
			result.deviceStatus = status;
			return result;
		}
		
		/*
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
			*/
	}
}