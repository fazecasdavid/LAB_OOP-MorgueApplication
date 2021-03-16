#pragma once
#include "VirtualRepository.h"
#include <string>

class HTMLRepository : public VirtualRepository {
public:
	std::string filePath;

public:
	HTMLRepository(std::string filePath) : filePath{ filePath } {}
	~HTMLRepository() = default;


	void addEnitity(const VictimFile& entity) override;


	void setFilePath(std::string filePath) override;


	std::vector<VictimFile> getAll() override;


	void updateEntity(const VictimFile& newEntity) override {}


	void deleteEntity(const VictimFile& entity) override;

	std::string getFilePath() override;

	void writeHTML(std::vector<VictimFile> filesToWrite);

};

