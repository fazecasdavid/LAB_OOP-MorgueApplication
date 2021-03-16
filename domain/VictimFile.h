#pragma once
#include <string>
#include <iostream>
#include <fstream>

class VictimFile {

private:
	std::string name;
	std::string placeOfOrigin;
	int age;
	std::string photograph;

public:
	VictimFile(std::string name, std::string placeOfOrigin, int age, std::string photograph);
	VictimFile(std::string name);
	VictimFile();

	std::string getInsertSQLFormat() const;
	std::string getUpdateSQLFormat() const;


	/*
		Description:
			- overloads the "is_equal operator"
			- two VictimFiles are equal if they have the Victims have the same name
	*/
	bool operator==(const VictimFile& victimFile);

	/*
		Description:
			- Getter:	returns the name of the Victim
	*/
	std::string getName() const;

	/*
		Description:
			- Getter:	returns the place of origin of the Victim
	*/
	std::string getPlaceOfOrigin() const;

	/*
		Description:
			- Getter:	returns the age of the Victim
	*/
	int getAge() const;

	/*
		Description:
			- Getter:	returns a photograph of the Victim
	*/
	std::string getPhotograph() const;


	/*
		Description:
			- Setter:	changes the Name of the Victim with the given name
	*/
	void setName(std::string newName);


	/*
		Description:
			- Setter:	changes the Place of origin of the Victim with the given Place of origin
	*/
	void setPlaceOfOrigin(std::string newPlaceOfOrigin);

	/*
		Description:
			- Setter:	changes the Age of the Victim with the given Age
	*/
	void setAge(int newAge);


	/*
		Description:
			- Setter:	changes the Photograph of the Victim with the given Photograph
	*/
	void setPhotograph(std::string newPhotograph);


	/*
		Description:
			- return the printing format of the File
	*/
	std::string getPrintFormat() const;

	/*
		Description:
			- return the CSV printing format of the File
	*/
	std::string getCSVFormat() const;


	 
	/*
		Description:
			- overloads the "extraction operator"
			- the Victimfile must be in CSV format
	*/
	friend std::istream& operator>>(std::istream& inputStream, VictimFile& victimFile);


	/*
		Description:
			- overloads the "insertion operator"
			- the Victimfile will be inserted in CSV format
	*/
	friend std::ostream& operator<<(std::ostream& outputStream, const VictimFile& victimFile);

};

