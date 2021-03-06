#pragma once

#include "Includes.h"

namespace FS
{
	static std::unordered_map<std::string, std::string> cachedFile;
	static std::vector<std::string> randomFilenames;
	static std::vector<std::string> randomFoldernames;

	std::string readFile(std::string name, bool cache) {
		std::fstream stream;
		if (cache) {
			if (cachedFile.find(name) != cachedFile.end()) {
				return cachedFile[name];
			}
		}

		std::string buffer;

		stream.open(name);
		if (!stream.is_open()) {
			std::cout << "Failed opening file " << name << "\n";
			return "";
		}

		buffer.clear();

		std::string line;
		while (getline(stream, line)) {
			buffer += line + '\n';
		}

		stream.close();

		if (cache) {
			cachedFile[name] = buffer;
		}

		return buffer;
	}

	std::string getRandomFilename() {
		return randomFilenames[rand() % randomFilenames.size()];
	}

	std::string getRandomFoldername() {
		return randomFoldernames[rand() % randomFoldernames.size()];
	}

	void loadRandomFiles() {
		randomFilenames.clear();

		std::string randomAsString = readFile("files/Filenames.txt", true);

		std::string temp = "";
		for (int i = 0; i <= randomAsString.length(); i++)
		{
			if (randomAsString[i] == '\n')
			{
				randomFilenames.push_back(temp);
				temp.clear();
			}
			else
			{
				temp += randomAsString[i];
			}
		}

		randomFoldernames.clear();

		randomAsString = readFile("files/Foldernames.txt", true);

		temp.clear();
		for (int i = 0; i <= randomAsString.length(); i++)
		{
			if (randomAsString[i] == '\n')
			{
				randomFoldernames.push_back(temp);
				temp.clear();
			}
			else
			{
				temp += randomAsString[i];
			}
		}
	}

	void resetCache() {
		cachedFile.clear();
	}

	

};