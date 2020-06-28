#pragma once
#include "Repository.h"

class Action {

public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() {}
};



class ActionAdd : public Action {

private:
	VirtualRepository* repository;
	VictimFile file;

public:
	ActionAdd(VirtualRepository* repository, VictimFile file);
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdd() {}
};

class ActionRemove : public Action {

private:
	VirtualRepository* repository;
	VictimFile file;

public:
	ActionRemove(VirtualRepository* repository, VictimFile file);
	void executeUndo() override;
	void executeRedo() override;
	~ActionRemove() {}
};

class ActionUpdate : public Action {

private:
	VirtualRepository* repository;
	VictimFile newFile;
	VictimFile oldFile;


public:
	ActionUpdate(VirtualRepository* repository, VictimFile oldFile, VictimFile newFile);
	void executeUndo() override;
	void executeRedo() override;
	~ActionUpdate() {}
};

