#pragma once
#include "Repository.h"


class FileRepository : public VirtualRepository {
public:
	std::string filePath;

public:
	FileRepository(std::string filePath = "");
	~FileRepository() = default;

	/*
		Description:
			- adds an entity to the file from the filePath in CSV format
			- @param: - the entity which will be added
			- throws runtime_error if the entity already is stored in the Conatiner
			- no return
	*/
	void addEnitity(const VictimFile& entity);

	/*
		Description:
			- updates an entity in the file from the filePath in CSV format
			- @param: - the entity which will be updated
			- throws runtime_error if the entity is not stored in the Conatiner
			- no return
	*/
	void updateEntity(const VictimFile& newEntity);

	/*
		Description:
			- deletes an entity from the Container the application works with
			- @param: - the entity which will be deleted
			- throws runtime_error if the entity is not stored in the Conatiner
			- no return
	*/
	void deleteEntity(const VictimFile& entity);


	/*
		Description:
			- returns a Vector conatining all the elements from the Container the application works with
			- if there are no elements in the Container, the Vector will be empty;
	*/
	std::vector<VictimFile> getAll();


	/*
		Description:
			- sets the path to the file the appliction will work with
			- @params: the path
			- no return
	*/
	void setFilePath(std::string filePath);

	std::string getFilePath() override;

};

