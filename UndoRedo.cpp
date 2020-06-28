#include "UndoRedo.h"

ActionAdd::ActionAdd(VirtualRepository* repository, VictimFile file) : repository{ repository }, file{ file } {}

void ActionAdd::executeUndo() {
	this->repository->deleteEntity(file);
}

void ActionAdd::executeRedo() {
	this->repository->addEnitity(file);
}

ActionRemove::ActionRemove(VirtualRepository* repository, VictimFile file) : repository{ repository }, file{ file } {}

void ActionRemove::executeUndo() {
	this->repository->addEnitity(file);
}

void ActionRemove::executeRedo() {
	this->repository->deleteEntity(file);
}

ActionUpdate::ActionUpdate(VirtualRepository* repository, VictimFile oldFile, VictimFile newFile) : repository{ repository },
oldFile{ oldFile }, newFile{ newFile } {}

void ActionUpdate::executeUndo() {
	this->repository->updateEntity(oldFile);
}

void ActionUpdate::executeRedo() {
	this->repository->updateEntity(newFile);
}
