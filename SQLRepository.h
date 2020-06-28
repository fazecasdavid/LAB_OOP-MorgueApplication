#pragma once
#include "VirtualRepository.h"
#include <string>

#include <vector>

class SQLRepository :public  VirtualRepository {
private:
	std::string filePath;
public:
	SQLRepository(std::string filePath = "") :filePath{ filePath } {}
	~SQLRepository();

	void addEnitity(const VictimFile& entity) override;
	void updateEntity(const VictimFile& newEntity) override;
	void deleteEntity(const VictimFile& entity) override;
	std::vector<VictimFile> getAll() override;
	void setFilePath(std::string filePath) override;
	std::string getFilePath() override;
private:
	void createTable();










};

