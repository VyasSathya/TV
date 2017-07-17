#include "TV.h"
#include "FileHandler.h"
#include <stdio.h>
#include <iostream>

int main(void) {

	std::cout << "Hello TV World" << std::endl;

	const std::string mapFilename = "C:\\Temp\\TV_ChannelNumberToNameMap.txt";
	FileHandler* mapFileHandler = new FileHandler(mapFilename);

	std::map <std::string, std::string> TVChannelNumberToNameMap;
	mapFileHandler->readFile(TVChannelNumberToNameMap);
	
	TV* myTV = new TV(TVChannelNumberToNameMap);
	myTV->channelDown();
	myTV->printChannelMap();

	myTV->writeSettingToFile();

	system("PAUSE");
	return 0;
}



