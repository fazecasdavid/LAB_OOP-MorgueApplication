#pragma once
#include "VictimFile.h"
#include <vector>


class VirtualRepository {
public:

	virtual ~VirtualRepository() = 0 {};

	/*
		Description:
			- pure virtual method
			- adds an entity to the Container the application works with
			- @param: - the entity which will be added
			- throws runtime_error if the entity already is stored in the Conatiner
			- no return
	*/
	virtual void addEnitity(const VictimFile& entity) = 0;


	/*
		Description:
			- pure virtual method
			- updates an entity in the Container the application works with
			- @param: - the entity which will be updated
			- throws runtime_error if the entity is not stored in the Conatiner
			- no return
	*/
	virtual void updateEntity(const VictimFile& newEntity) = 0;


	/*
		Description:
			- pure virtual method
			- deletes an entity from the Container the application works with
			- @param: - the entity which will be deleted
			- throws runtime_error if the entity is not stored in the Conatiner
			- no return
	*/
	virtual void deleteEntity(const VictimFile& entity) = 0;
	

	/*
		Description:
			- pure virtual method
			- returns a Vector conatining all the elements from the Container the application works with
			- if there are no elements in the Container, the Vector will be empty;
	*/
	virtual std::vector<VictimFile> getAll() = 0;


	/*
		Description:
			- sets the path to the Container we work with
			- @params: the path
			- no return
	*/
	virtual void setFilePath(std::string filePath) = 0;

	virtual std::string getFilePath() { return ""; }



};

