#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <map>

class FileHandler
{

public:

	typedef std::map <std::string, std::string> ChannelMap;

	FileHandler(std::string fileName);
	~FileHandler();

	bool readFile(ChannelMap& channelMap);
	bool writeFile(ChannelMap channelMap);


private:

	std::string mapFilename;  
	static const int MaxChannelNumberToNameStrLength = 30;
	const char channelNumberToNameStr[MaxChannelNumberToNameStrLength] = "ChannelNumberToName: ";

};

#endif