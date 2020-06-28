#pragma once
#include <stdexcept>
#include "VictimFile.h"
#include <vector>
#include "VirtualRepository.h"


class Repository : public VirtualRepository {

private:
	std::vector<VictimFile> data;

public:
	Repository() {}
	~Repository() = default;

	/*
		Description:
			- adds an entity to the Container the application works with
			- @param: - the entity which will be added
			- throws runtime_error if the entity already is stored in the Conatiner
			- no return
	*/
	void addEnitity(const VictimFile& entity);

	/*
		Description:
			- updates an entity in the Container the application works with
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
			- sets the path to the Container we work with
			- @params: the path
			- no return
	*/
	void setFilePath(std::string filePath) {}
};


