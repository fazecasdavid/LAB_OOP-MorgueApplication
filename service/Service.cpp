#include "Service.h"
#include <algorithm>
#include "VictimFileValidator.h"
#include "HTMLRepository.h"


void Service::undoMain() {
	if (this->undoMainStack.empty())
		throw std::runtime_error("No more undo!");

	this->undoMainStack.back()->executeUndo();

	// we move the action to the Redo stack
	this->redoMainStack.push_back(std::move(this->undoMainStack.back()));
	this->undoMainStack.pop_back();
}

void Service::redoMain() {
	if (this->redoMainStack.empty())
		throw std::runtime_error("No more redo!");

	this->redoMainStack.back()->executeRedo();

	// we move the action to the Undo stack
	this->undoMainStack.push_back(std::move(this->redoMainStack.back()));
	this->redoMainStack.pop_back();
}

void Service::undoMylist() {
	if (this->undoMylistStack.empty())
		throw std::runtime_error("No more undo!");

	this->undoMylistStack.back()->executeUndo();

	// we move the action to the Redo stack
	this->redoMylistStack.push_back(std::move(this->undoMylistStack.back()));
	this->undoMylistStack.pop_back();
}

void Service::redoMylist() {
	if (this->redoMylistStack.empty())
		throw std::runtime_error("No more redo!");

	this->redoMylistStack.back()->executeRedo();

	// we move the action to the Undo stack
	this->undoMylistStack.push_back(std::move(this->redoMylistStack.back()));
	this->redoMylistStack.pop_back();
}

Service::Service(VirtualRepository* repository) {
	this->repository = repository;
	this->indexNext = 0;
	this->toBeTransferred = nullptr;
}

Service::~Service() {
	//if (this->toBeTransferred != nullptr)
		delete this->toBeTransferred;
}

void Service::HTML_InitializeTransferredRepository(std::string filePath) {
	HTMLRepository* htmlRepository = new HTMLRepository{ filePath };
	this->toBeTransferred = htmlRepository;
	std::ofstream open(filePath);
}

void Service::CSV_InitializeTransferredRepository(std::string filePath) {
	FileRepository* fileRepository = new FileRepository{filePath};
	this->toBeTransferred = fileRepository;
	std::ofstream open(filePath);
}

VirtualRepository* Service::getToBeTransferredRepository() {
	return this->toBeTransferred;
}


void Service::addVictimFile(std::string name, std::string placeOfOrigin, int age, std::string photograph) {

	VictimFile victimFile{ name, placeOfOrigin, age, photograph };
	VictimFileValidator::ValidateVictimFile(victimFile);
	this->repository->addEnitity(victimFile);

	this->undoMainStack.push_back(std::make_unique<ActionAdd>(repository, victimFile));
	this->redoMainStack.clear();
}


void Service::updateVictimFile(std::string newName, std::string newPlaceOfOrigin, int newAge, std::string newPhotograph) {
	VictimFile newVictimFile{ newName, newPlaceOfOrigin, newAge, newPhotograph };
	auto allFiles = this->repository->getAll();
	VictimFile oldFile;
	for (auto file : allFiles)
		if (file.getName() == newVictimFile.getName())
			oldFile = file;
	VictimFileValidator::ValidateVictimFile(newVictimFile);
	this->repository->updateEntity(newVictimFile);


	this->undoMainStack.push_back(std::make_unique<ActionUpdate>(repository, oldFile, newVictimFile));
	this->redoMainStack.clear();
}


void Service::deleteVictimFileByName(std::string name) {
	auto allFiles = this->repository->getAll();
	VictimFile victimFileToBeDeleted{ name };
	auto iteratorToBeDeleted = std::find(allFiles.begin(), allFiles.end(), victimFileToBeDeleted);
	VictimFileValidator::ValidateVictimFile(victimFileToBeDeleted);
	this->repository->deleteEntity(victimFileToBeDeleted);


	this->undoMainStack.push_back(std::make_unique<ActionRemove>(repository, *iteratorToBeDeleted));
	this->redoMainStack.clear();
}


std::vector<VictimFile> Service::getAll() {
	return this->repository->getAll();
}


int Service::next() {
	std::vector<VictimFile> allFiles = this->getAll();
	if (allFiles.size() == 0)
		throw NotFoundException("No files in the program");
		//throw std::runtime_error("No files in the program");

	// we cycle back the files
	if (this->indexNext >= allFiles.size())
		this->indexNext = 0;

	//VictimFile wantedFile = allFiles[this->indexNext];
	//this->indexNext++;
	return this->indexNext++;
}


void Service::save(std::string name) {
	std::vector<VictimFile> allFiles = this->getAll();

	auto iteratorWantedFile = std::find_if(allFiles.begin(), allFiles.end(), [name](auto file) {return file.getName() == name; });
	if (iteratorWantedFile == allFiles.end())
		throw std::runtime_error("No such file found");

	this->toBeTransferred->addEnitity(*iteratorWantedFile);

	this->undoMylistStack.push_back(std::make_unique<ActionAdd>(toBeTransferred, *iteratorWantedFile));
}


std::vector<VictimFile> Service::getMyList() {
	return this->toBeTransferred->getAll();
}


std::vector<VictimFile> Service::filterPlaceOfOriginAndAge(std::string placeOfOrigin, int age) {
	std::vector<VictimFile> allFiles = this->getAll();
	std::vector<VictimFile> wantedFiles(allFiles.size());

	auto lastIterator = std::copy_if(allFiles.begin(), allFiles.end(), wantedFiles.begin(),
		[placeOfOrigin, age](auto file) {return file.getPlaceOfOrigin() == placeOfOrigin && file.getAge() < age; });
	wantedFiles.resize(std::distance(wantedFiles.begin(), lastIterator));
	return wantedFiles;
}


std::vector<VictimFile> Service::filterByAge(int age) {
	std::vector<VictimFile> allFiles = this->getAll();
	std::vector<VictimFile> wantedFiles(allFiles.size());

	auto lastIterator = std::copy_if(allFiles.begin(), allFiles.end(), wantedFiles.begin(),
		[age](auto file) {return file.getAge() < age; });
	wantedFiles.resize(std::distance(wantedFiles.begin(), lastIterator));

	return wantedFiles;
}

void Service::setFilePath(std::string filePath) {
	this->repository->setFilePath(filePath);
}

void Service::displayMyList() {
	system(this->toBeTransferred->getFilePath().c_str());
}





