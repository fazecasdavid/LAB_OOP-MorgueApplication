#pragma once
#include "Repository.h"
#include <vector>
#include "VictimFile.h"
#include "FileRepository.h"
#include <string>
#include "UndoRedo.h"
#include <memory>

class Service {

private:
	VirtualRepository* repository;
	VirtualRepository* toBeTransferred;
	int indexNext;

	std::vector<std::unique_ptr<Action>> undoMainStack;
	std::vector<std::unique_ptr<Action>> redoMainStack;
	std::vector<std::unique_ptr<Action>> undoMylistStack;
	std::vector<std::unique_ptr<Action>> redoMylistStack;


public:
	void undoMain();
	void redoMain();
	void undoMylist();
	void redoMylist();

	Service(VirtualRepository* repository);
	~Service();
	void HTML_InitializeTransferredRepository(std::string filePath);
	void CSV_InitializeTransferredRepository(std::string filePath);
	VirtualRepository* getToBeTransferredRepository();

	/*
		Description:
			- adds a VictimFile to the repository
			- the VictimFile is composed by: name, placeOfOrigin, age, photograph
			- no return
			- throws runtime_error if the file is already in the repository
	*/
	void addVictimFile(std::string name, std::string placeOfOrigin, int age, std::string photograph);


	/*
		Description:
			- updates a VictimFile from the repository
			- the VictimFile is composed by: name, placeOfOrigin, age, photograph
			- no return
			- throws runtime_error if the file is not found in the repository
	*/
	void updateVictimFile(std::string newName, std::string newPlaceOfOrigin, int newAge, std::string newPhotograph);


	/*
		Description:
			- deletes a VictimFile from the repository
			- the VictimFile is identified by its name
			- no return
			- throws runtime_error if the file is not found in the repository
	*/
	void deleteVictimFileByName(std::string name);


	/*
		Description:
			- returns a Vector conatining all the elements from the Container the application works with
			- if there are no elements in the Container, the Vector will be empty;
	*/
	std::vector<VictimFile> getAll();


	/*
		Description:
			- iterates through the files from the repository
			- returns the next in line VictimFile
	*/
	int next();


	/*
		Description:
			- saves a file to the MyList repository
			- the VictimFile is identified by its name
			- no return
			- throws runtime_error if the file is not found in the main repository
	*/
	void save(std::string name);


	/*
		Description:
			- returns a Vector conatining all the elements from the MyList repository
			- if there are no elements in the Container, the Vector will be empty
	*/
	std::vector<VictimFile> getMyList();


	/*
		Description:
			- returns a Vector conatining all the elements from the repository that satisfy the condition
			- if there are no elements in the Container, the Vector will be empty
			- the files must have the same place of origin and the age less then the given age
	*/
	std::vector<VictimFile> filterPlaceOfOriginAndAge(std::string placeOfOrigin, int age);

	/*
		Description:
			- returns a Vector conatining all the elements from the repository that satisfy the condition
			- if there are no elements in the Container, the Vector will be empty
			- the files must have the age less then the given age
	*/
	std::vector<VictimFile> filterByAge(int age);


	/*
		Description:
			- sets the path to the Container we work with
			- @params: the path
			- no return
	*/
	void setFilePath(std::string filePath);

	void displayMyList();

};

