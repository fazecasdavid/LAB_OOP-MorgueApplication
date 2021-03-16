#include "FileRepository.h"
#include <fstream>
#include <algorithm>
#include "exceptions.h"


FileRepository::FileRepository(std::string filePath) {
	this->filePath = filePath;
}

void FileRepository::addEnitity(const VictimFile& entity) {

	std::ifstream inputStream(this->filePath);
	std::vector<VictimFile> allFiles;
	VictimFile currentFile{};
	while (inputStream >> currentFile)
		allFiles.push_back(currentFile);


	if (std::find(allFiles.begin(), allFiles.end(), entity) != allFiles.end())
		throw DuplicateElementException("Entity already exists");
		//throw std::runtime_error("Entity already exists");
	allFiles.push_back(entity);


	inputStream.close();
	std::ofstream outputStream(this->filePath);
	for_each(allFiles.begin(), allFiles.end(), [&outputStream](auto& file) {outputStream << file; });
}

void FileRepository::updateEntity(const VictimFile& newEntity) {
	std::ifstream inputStream(this->filePath);
	std::vector<VictimFile> allFiles;
	VictimFile currentFile{};
	while (inputStream >> currentFile)
		allFiles.push_back(currentFile);


	auto iteratorToUpdate = std::find(allFiles.begin(), allFiles.end(), newEntity);
	if (iteratorToUpdate == allFiles.end())
		throw NotFoundException("Entity not found");
		//throw std::runtime_error("Entity not found");
	(*iteratorToUpdate) = newEntity;


	inputStream.close();
	std::ofstream outputStream(this->filePath);
	for_each(allFiles.begin(), allFiles.end(), [&outputStream](VictimFile file) {outputStream << file; });
}

void FileRepository::deleteEntity(const VictimFile& entity) {
	std::ifstream inputStream(this->filePath);
	std::vector<VictimFile> allFiles;
	VictimFile currentFile{};
	while (inputStream >> currentFile)
		allFiles.push_back(currentFile);


	auto iteratorToDelete = std::find(allFiles.begin(), allFiles.end(), entity);
	if (iteratorToDelete == allFiles.end())
		throw NotFoundException("Entity not found");
		//throw std::runtime_error("Entity not found");
	allFiles.erase(iteratorToDelete);


	inputStream.close();
	std::ofstream outputStream(this->filePath);
	for_each(allFiles.begin(), allFiles.end(), [&outputStream](VictimFile file) {outputStream << file; });
}

std::vector<VictimFile> FileRepository::getAll() {
	std::ifstream inputStream(this->filePath);
	std::vector<VictimFile> allFiles;
	VictimFile currentFile{};
	while (inputStream >> currentFile)
		allFiles.push_back(currentFile);

	return allFiles;
}

void FileRepository::setFilePath(std::string filePath) {
	this->filePath = filePath;
	//std::ofstream open(filePath);
	std::fstream op;
	op.open(filePath);
	op.close();
}

std::string FileRepository::getFilePath() {
	return this->filePath;
}
