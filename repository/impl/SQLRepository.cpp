#include "SQLRepository.h"
#include <algorithm>
#include "exceptions.h"
#include <sqlite3.h>
#include <stdio.h>
#include <iostream>



SQLRepository::~SQLRepository() {
	
	/*int r = remove(filePath.c_str());
	std::cout << r;*/

	
}

void SQLRepository::addEnitity(const VictimFile& entity) {
	
	std::string sqlCommand = entity.getInsertSQLFormat();

	sqlite3* DataBase;
	int exitCode;
	exitCode = sqlite3_open(filePath.c_str(), &DataBase);
	char* messageError;

	exitCode = sqlite3_exec(DataBase, sqlCommand.c_str(), NULL, 0, &messageError);
	if (exitCode != SQLITE_OK)
		throw DuplicateElementException(messageError);

	sqlite3_close(DataBase);
}

void SQLRepository::updateEntity(const VictimFile& newEntity) {
	auto allFiles = this->getAll();
	auto iteratorToUpdate = std::find(allFiles.begin(), allFiles.end(), newEntity);
	if (iteratorToUpdate == allFiles.end())
		throw NotFoundException("Entity not found");


	sqlite3* DataBase;
	int exitCode;
	exitCode = sqlite3_open(filePath.c_str(), &DataBase);
	char* messageError;

	std::string sqlCommand = newEntity.getUpdateSQLFormat();

	exitCode = sqlite3_exec(DataBase, sqlCommand.c_str(), NULL, 0, &messageError);

	if (exitCode != SQLITE_OK) {
		throw std::runtime_error(messageError);
	}
	sqlite3_close(DataBase);
}

void SQLRepository::deleteEntity(const VictimFile& entity) {
	auto allFiles = this->getAll();
	auto iteratorToUpdate = std::find(allFiles.begin(), allFiles.end(), entity);
	if (iteratorToUpdate == allFiles.end())
		throw NotFoundException("Entity not found");


	sqlite3* DataBase;
	int exitCode;
	exitCode = sqlite3_open(filePath.c_str(), &DataBase);
	char* messageError;

	std::string sqlCommand = "DELETE FROM victim_files WHERE NAME = '" + entity.getName() + "'";

	exitCode = sqlite3_exec(DataBase, sqlCommand.c_str(), NULL, 0, &messageError);

	if (exitCode != SQLITE_OK) {
		throw std::runtime_error(messageError);
	}

}

int fetchData(void* data_t, int argc, char** argv, char** colName) {

	std::vector<VictimFile>* allFiles = static_cast<std::vector<VictimFile>*>(data_t);

	VictimFile victimFile{ static_cast<std::string>(argv[0]), static_cast<std::string>(argv[1]),
			std::atoi(argv[2]), static_cast<std::string>(argv[3]) };
	allFiles->push_back(victimFile);
	return 0;
}

std::vector<VictimFile> SQLRepository::getAll() {
	std::vector<VictimFile> allFiles;

	sqlite3* DataBase;
	int exitCode;
	exitCode = sqlite3_open(filePath.c_str(), &DataBase);
	char* messageError;

	std::string sqlCommand = "SELECT * FROM victim_files;";

	exitCode = sqlite3_exec(DataBase, sqlCommand.c_str(), fetchData, &allFiles, &messageError);
	if (exitCode != SQLITE_OK) {
		throw std::runtime_error(messageError);
	}

	return allFiles;
}

void SQLRepository::setFilePath(std::string filePath) {
	this->filePath = filePath;
	this->createTable();
}

std::string SQLRepository::getFilePath() {
	return filePath;
}

void SQLRepository::createTable() {
	sqlite3* DataBase;
	std::string sqlCommand = "CREATE TABLE IF NOT EXISTS victim_files("
		"Name TEXT NOT NULL PRIMARY KEY, "
		"PlaceOfOrigin TEXT NOT NULL, "
		"Age INT NOT NULL, "
		"Photograph TEXT NOT NULL);";
	try {
		int exitCode;
		exitCode = sqlite3_open(filePath.c_str(), &DataBase);

		char* messageError;
		exitCode = sqlite3_exec(DataBase, sqlCommand.c_str(), NULL, 0, &messageError);
		if (exitCode != SQLITE_OK) {
			throw std::runtime_error(messageError);
		} else {
			sqlite3_close(DataBase);
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}


