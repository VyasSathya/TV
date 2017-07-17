#pragma once

#ifndef TV_H
#define TV_H
#include <String>
#include <map>

class TV
{
private:
	const std::string myMapFilename = "C:\\Temp\\TV_Settings.txt";
	const std::string manufacturerStr = "Manufacturer:";
	const std::string modelStr = "Model:";
	const std::string inchStr = "Inch:";
	const std::string hDStr = "HD:";
	const std::string brightnessStr = "Brightness:";
	const std::string contrastStr = "Contrast:";
	const std::string volumeCurrentStr = "VolumeCurrent:";
	const std::string channelCurrentStr = "ChannelCurrent:";
	const int channelNumberLength = 10;
	const int volumeMin = 1;
	const int volumeMax = 10;
	const std::string channelMin = "1";
	const std::string channelMax = "1000";

	typedef std::map<std::string, std::string>::iterator mapIteratorType;
	std::map <std::string, std::string> myChannelNumberToNameMap;
	mapIteratorType mapItr;
	int currentChannelItrIndex;
	std::string manufacturer;
	std::string model;
	int inch;
	bool HD;
	bool on;
	int brightness;
	int contrast;
	int volumeCurrent;
	std::string channelCurrent;
	int numberOfChannels;

	//State state;

	std::string TV::spacePadString(std::string value, int length);

public:
	TV(std::map <std::string, std::string> channelNumbertoName);

	//TV();  // Temporarily available to create initial setting file
	~TV();

	bool readSettingFromFile();
	bool writeSettingToFile();
	void printChannelMap();

	void setup();
	void factoryReset();
	void channelUp();
	void channelDown();
	void goToChannel(std::string channelCurrent);
	void volumeUp();
	void volumeDown();

};

#endif