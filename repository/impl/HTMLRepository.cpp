#include "HTMLRepository.h"
#include "exceptions.h"
#include <fstream>
#include <algorithm>
#include <regex>


void HTMLRepository::addEnitity(const VictimFile& entity) {
	std::vector<VictimFile> allFiles = this->getAll();

	if (std::find(allFiles.begin(), allFiles.end(), entity) != allFiles.end())
		throw DuplicateElementException("Duplicate element!\n");
	allFiles.push_back(entity);

	this->writeHTML(allFiles);
}

void HTMLRepository::setFilePath(std::string filePath) {
	this->filePath = filePath;
	std::ofstream open(filePath);
}

std::vector<VictimFile> HTMLRepository::getAll() {
	std::string htmlString{};
	std::ifstream inputStream(this->filePath);
	while (!inputStream.eof()) {
		std::string line;
		std::getline(inputStream, line);
		htmlString += line + "\n";
	}
	inputStream.close();


	std::regex baseRegex("<td>(.*)</td>");
	std::vector<std::string> fields{};

	for (auto i = std::sregex_iterator(htmlString.begin(), htmlString.end(), baseRegex);
		i != std::sregex_iterator(); ++i) {
		std::smatch matched = *i;
		std::string field = matched.str();
		field.erase(0, 4);	// get rid of <td>
		field.erase(field.end() - 5, field.end()); //get rid of </td>

		fields.push_back(field);
	}
	int ENTITY_FIELDS = 4;
	int NAME_INDEX = 0, AGE_INDEX = 2, PLACE_INDEX = 1, PHOTOGRAPH_INDEX = 3;
	std::vector<VictimFile> allFiles{};

	for (size_t i = 0; i < fields.size(); i += ENTITY_FIELDS)
		allFiles.push_back(VictimFile(fields[i + NAME_INDEX], fields[i + PLACE_INDEX],
			std::stoi(fields[i + AGE_INDEX]), fields[i + PHOTOGRAPH_INDEX]));


	return allFiles;
}

void HTMLRepository::deleteEntity(const VictimFile& entity) {

	std::vector<VictimFile> allFiles = this->getAll();
	auto removeIterator = std::find(allFiles.begin(), allFiles.end(), entity);
	if (removeIterator == allFiles.end())
		throw NotFoundException("Not found!\n");

	allFiles.erase(removeIterator);
	this->writeHTML(allFiles);
}

std::string HTMLRepository::getFilePath() {
	return this->filePath;
}

void HTMLRepository::writeHTML(std::vector<VictimFile> filesToWrite) {

	std::string htmlString{};

	htmlString += "<!DOCTYPE html>\n";
	htmlString += "\t<html>\n";
	htmlString += "\t\t<head>\n";
	htmlString += "\t\t\t<title>Victim files</title>\n";
	htmlString += "\t\t</head>\n";
	htmlString += "\t<body>\n";
	htmlString += "\t<table border=\"1\">\n";
	htmlString += "\t<tr>\n";
	htmlString += "\t\t<th>Name</th>\n";
	htmlString += "\t\t<th>Age</th>\n";
	htmlString += "\t\t<th>Photograph</th>\n";
	htmlString += "\t\t<th>Place of Origin</th>\n";
	htmlString += "\t</tr>\n";

	// all victim files
	for_each(filesToWrite.begin(), filesToWrite.end(), [&](VictimFile& file) {
		htmlString += "\t<tr>\n";
		htmlString += "\t\t<td>" + file.getName() + "</td>\n";
		htmlString += "\t\t<td>" + file.getPlaceOfOrigin() + "</td>\n";
		htmlString += "\t\t<td>" + std::to_string(file.getAge()) + "</td>\n";
		htmlString += "\t\t<td>" + file.getPhotograph() + "</td>\n";
		htmlString += "\t</tr>\n";
		});

	htmlString += "\t</table>\n";
	htmlString += "\t</body>\n";
	htmlString += "\t</html>\n";

	std::ofstream outputStream(this->filePath);
	outputStream << htmlString;
}
