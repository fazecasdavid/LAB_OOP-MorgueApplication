#include "VictimFile.h"
#include "utils.h"
#include <string>


VictimFile::VictimFile(std::string name, std::string placeOfOrigin, int age, std::string photograph) {
	this->name = name;
	this->placeOfOrigin = placeOfOrigin;
	this->age = age;
	this->photograph = photograph;
}

VictimFile::VictimFile(std::string name) {
	this->name = name;
	this->placeOfOrigin = "";
	this->age = 0;
	this->photograph = "";
}

VictimFile::VictimFile() {
	this->name = "";
	this->placeOfOrigin = "";
	this->age = 0;
	this->photograph = "";
}

bool VictimFile::operator==(const VictimFile& victimFile) {
	if (this->name == victimFile.name)
		return true;
	return false;
}

std::string VictimFile::getName() const { return this->name; }

std::string VictimFile::getPlaceOfOrigin() const { return this->placeOfOrigin; }

int VictimFile::getAge() const { return this->age; }

std::string VictimFile::getPhotograph() const { return this->photograph; }

void VictimFile::setName(std::string newName) { this->name = newName; }

void VictimFile::setPlaceOfOrigin(std::string newPlaceOfOrigin) { this->placeOfOrigin = newPlaceOfOrigin; }

void VictimFile::setAge(int newAge) { this->age = newAge; }

void VictimFile::setPhotograph(std::string newPhotograph) { this->photograph = newPhotograph; }


std::string VictimFile::getPrintFormat() const {
	return name + " " + placeOfOrigin + " " + std::to_string(age) + " " + photograph + "\n";
}

std::string VictimFile::getCSVFormat() const {
	return name + "," + placeOfOrigin + "," + std::to_string(age) + "," + photograph + "\n";
}

std::string VictimFile::getInsertSQLFormat() const {
	return "INSERT INTO victim_files (Name, PlaceOfOrigin, Age, Photograph) VALUES ('" + name + "', '" + placeOfOrigin +
		"', '" + std::to_string(age) + "', '" + photograph + "');";
}

std::string VictimFile::getUpdateSQLFormat() const {
	return "UPDATE victim_files SET Age = " + std::to_string(age) + ", Photograph = '" + photograph + "', PlaceOfOrigin = '" +
		placeOfOrigin + "' WHERE NAME = '" + name + "'";
}


std::istream& operator>>(std::istream& inputStream, VictimFile& victimFile) {
	std::string  line;
	std::getline(inputStream, line);
	std::vector<std::string> tokens = splitDelimiter(line, ",");
	if (tokens.size() != 4)
		return inputStream;

	victimFile.name = tokens[0];
	victimFile.placeOfOrigin = tokens[1];
	victimFile.age = std::stoi(tokens[2]);
	victimFile.photograph = tokens[3];
	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const VictimFile& victimFile) {
	outputStream << victimFile.getCSVFormat();
	return outputStream;
}
