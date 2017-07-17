#include "TV.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  

//ASSUMPTIONS
//The Channel Numbers are Integers

// Software creation of TV
TV::TV(std::map <std::string, std::string> channelNumbertoName)
	: currentChannelItrIndex(0)
	, numberOfChannels(0)
{
	//TODO check if values are valid

	for (mapIteratorType itr = channelNumbertoName.begin(); itr != channelNumbertoName.end(); ++itr) {
		myChannelNumberToNameMap[spacePadString(itr->first, channelNumberLength)] = itr->second;
		numberOfChannels++;
	}
	mapItr = myChannelNumberToNameMap.begin();
	setup();

	return;

}

TV::~TV() {
}


// First Time TV owner setting up television (languages, brightness, other options)
void TV::setup() {
	// Prompt user for language, ...
	readSettingFromFile();
	goToChannel(channelCurrent);
}

void TV::factoryReset() {
	//prompt user to erase data
}

void TV::channelUp() {
	// increment to next available channel	
	mapItr = myChannelNumberToNameMap.begin();
	if (currentChannelItrIndex = numberOfChannels - 1) {
		//std::advance(mapItr, 0);
		currentChannelItrIndex = 0;
	}
	std::advance(mapItr, currentChannelItrIndex);
	currentChannelItrIndex++;
}

void TV::channelDown() {
	// decrement to next available channel
	mapItr = myChannelNumberToNameMap.begin();
	if (currentChannelItrIndex = 0) {
		mapItr = myChannelNumberToNameMap.end();
		currentChannelItrIndex = numberOfChannels - 1;
	}
	std::advance(mapItr, currentChannelItrIndex);
	currentChannelItrIndex++;
}

void TV::goToChannel(std::string channelCurrent) {
	int channelItrIndex = 0;

	for (mapItr = myChannelNumberToNameMap.begin(); mapItr != myChannelNumberToNameMap.end(); ++mapItr) {
		if (mapItr->first == spacePadString(channelCurrent, channelNumberLength)) {
			currentChannelItrIndex = channelItrIndex;
			std::cout << "$$$ " << currentChannelItrIndex << " - " << mapItr->first << " => " << mapItr->second << std::endl;
			return; // channel was found
		}
		channelItrIndex++;
	}
	//channelItrIndex = 0;  // channel was not found
}

void TV::volumeUp() {
	if (volumeCurrent < volumeMax) {
		volumeCurrent++;
	}
}

void TV::volumeDown() {
	if (volumeCurrent > volumeMin) {
		volumeCurrent--;
	}
}

std::string TV::spacePadString(std::string value, int length) {
	std::stringstream ss;
	ss << std::setfill(' ') << std::setw(length) << value;
	std::string convertedValue = ss.str();
	return convertedValue;
};


bool TV::readSettingFromFile() {
	std::string line;
	std::string field;
	std::string value;

	std::ifstream settingifs(myMapFilename);
	if (settingifs.is_open()) {
		while (std::getline(settingifs, line)) {
			char *strPtr = NULL;
			char *nextPtr = NULL;
			char *stopPtr = NULL;
			bool readField = false;

			strPtr = strtok_s((char *)line.c_str(), " ", &nextPtr);
			if (strPtr != NULL)
			{
				field = strPtr;
				strPtr = strtok_s(NULL, "|", &nextPtr);
				if (strPtr != NULL)
				{
					value = strPtr;
					readField = true;
				}
				else
				{
					value = "Unknown";  // TBD: Report/Handle invalid setting in file
				}
			}

			if (readField) {
				if (field == manufacturerStr) {
					manufacturer = value;
				}
				else if (field == modelStr) {
					model = value;
				}
				else if (field == inchStr) {
					inch = strtol(value.c_str(), &stopPtr, 10);
				}
				else if (field == hDStr) {
					HD = strtol(value.c_str(), &stopPtr, 10);
				}
				else if (field == brightnessStr) {
					brightness = strtol(value.c_str(), &stopPtr, 10);
				}
				else if (field == contrastStr) {
					contrast = strtol(value.c_str(), &stopPtr, 10);
				}
				else if (field == volumeCurrentStr) {
					volumeCurrent = strtol(value.c_str(), &stopPtr, 10);
				}
				else if (field == channelCurrentStr) {
					channelCurrent = value;
				}
			}
			std::cout << "~~~ Field: " << field << " Value: " << value << std::endl;
		}
		settingifs.close();
	}
	else
	{
		std::cout << "Error: Unable to open tv settings file " << myMapFilename << " for reading." << std::endl;
		std::cout << "Initializing with default values..." << std::endl;
		// Default TV settings if  setting file is not found
		manufacturer = "Samsung";
		model = "QN75Q9FAMFXZA";
		inch = 75;
		HD = true;
		brightness = 50;
		contrast = 50;
		volumeCurrent = 4;
		channelCurrent = 9;

		return false;
	}

	return true;
}


bool TV::writeSettingToFile() {
	std::ofstream settingofs(myMapFilename);
	if (settingofs.is_open()) {
		settingofs << manufacturerStr << " " << manufacturer << "|" << std::endl;
		settingofs << modelStr << " " << model << "|" << std::endl;
		settingofs << inchStr << " " << inch << "|" << std::endl;
		settingofs << hDStr << " " << HD << "|" << std::endl;
		settingofs << brightnessStr << " " << brightness << "|" << std::endl;
		settingofs << contrastStr << " " << contrast << "|" << std::endl;
		settingofs << volumeCurrentStr << " " << volumeCurrent << "|" << std::endl;
		settingofs << channelCurrentStr << " " << channelCurrent << "|" << std::endl;

		settingofs.close();
	}
	else {
		std::cout << "Error: Unable to open tv settings file " << myMapFilename << " for writing." << std::endl;
		return false;
	}

	return true;
}

void TV::printChannelMap() {
	std::cout << "printChannelMap():" << std::endl;
	for (mapItr = myChannelNumberToNameMap.begin(); mapItr != myChannelNumberToNameMap.end(); ++mapItr) {
		std::cout << mapItr->first << " => " << mapItr->second << std::endl;
	}
	mapIteratorType itr = myChannelNumberToNameMap.begin();
	currentChannelItrIndex = 2;
	std::advance(itr, currentChannelItrIndex);
	if (itr != myChannelNumberToNameMap.end()) {
		std::cout << "+++ " << itr->first << " => " << itr->second << std::endl;
	}
}