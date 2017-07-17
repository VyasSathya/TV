#include "FileHandler.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>


FileHandler::FileHandler(std::string fileName)
	: mapFilename(fileName) {
	if (fileName.empty()) {
		mapFilename = "C:\\Temp\\TV_ChannelNumberToNameMap.txt";
	}
}


FileHandler::~FileHandler() {
}


bool FileHandler::readFile(ChannelMap& channelMap) {
	std::string line;
	std::string channelNumber;
	std::string channelName;
	const int channelNumberToNameStrLength = strlen(channelNumberToNameStr);

	std::ifstream settingifs(mapFilename);
	if (settingifs.is_open())
	{
		while (std::getline(settingifs, line))
		{
			char *strPtr = NULL;
			char *nextPtr = NULL;
			if (strncmp(line.c_str(), channelNumberToNameStr, channelNumberToNameStrLength) == 0)
			{
				strPtr = strtok_s((char *)line.c_str() + channelNumberToNameStrLength, ",", &nextPtr);
				if (strPtr != NULL)
				{
					channelNumber = strPtr;
					strPtr = strtok_s(NULL, "|", &nextPtr);
					if (strPtr != NULL)
					{
						channelName = strPtr;
					}
					else
					{
						channelName = "Unknown";
					}
				}
			}
			channelMap[channelNumber] = channelName;
			std::cout << "~~~ ChannelNumber: " << channelNumber << " ChannelName: " << channelName << std::endl;
		}
		settingifs.close();
	}
	else
	{
		std::cout << "Error: Unable to open tv settings file " << mapFilename << " for reading." << std::endl;
		return false;
	}

	return true;
}


bool FileHandler::writeFile(ChannelMap channelMap) {
	std::ofstream channelMapOFS(mapFilename);
	if (channelMapOFS.is_open())
	{
		for (std::map<std::string, std::string>::iterator it = channelMap.begin(); it != channelMap.end(); ++it)
		{
			std::cout << channelNumberToNameStr << it->first << ", " << it->second << "|" << std::endl;
			channelMapOFS << channelNumberToNameStr << it->first << ", " << it->second << "|" << std::endl;
		}
		channelMapOFS.close();
	}
	else
	{
		std::cout << "Error: Unable to open tv settings file " << mapFilename << " for writing." << std::endl;
		return false;
	}

	return true;
}
