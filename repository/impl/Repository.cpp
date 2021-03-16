#include "Repository.h"
#include <algorithm>


void Repository::addEnitity(const VictimFile& entity) {
	if (std::find(data.begin(), data.end(), entity) != data.end())
		throw std::runtime_error("Entity already exists");

	this->data.push_back(entity);
}

void Repository::updateEntity(const VictimFile& newEntity) {
	auto iteratorToUpdate = std::find(data.begin(), data.end(), newEntity);
	if (iteratorToUpdate == data.end())
		throw std::runtime_error("Entity not found");
	(*iteratorToUpdate) = newEntity;
}

void Repository::deleteEntity(const VictimFile& entity) {
	auto iteratorToDelete = std::find(data.begin(), data.end(), entity);
	if (iteratorToDelete == data.end())
		throw std::runtime_error("Entity not found");

	this->data.erase(iteratorToDelete);
}

std::vector <VictimFile> Repository::getAll() {
	return this->data;
}
