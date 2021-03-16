#include "MainWindow.h"
#include <qmessagebox.h>
#include <qshortcut.h>
#include <qkeysequence.h>
#include <qabstractitemview.h>


MainWindow::MainWindow(Service& service, QWidget *parent)
	: QMainWindow(parent), service{service}
{
	ui.setupUi(this);
	populateList();

	QShortcut* shortcutUndoMain = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(shortcutUndoMain, &QShortcut::activated, this, &MainWindow::undoMain);
	QShortcut* shortcutRedoMain = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(shortcutRedoMain, &QShortcut::activated, this, &MainWindow::redoMain);

	myListModel = new MylistModel{ this->service.getToBeTransferredRepository() };
	myListWidget = new MyListWidget{ myListModel };
}

void MainWindow::populateList() {

	this->ui.victimsListWidget->clear();
	std::vector<VictimFile> allFiles = this->service.getAll();
	for (auto file : allFiles)
		this->ui.victimsListWidget->addItem(QString::fromStdString(file.getName() + "   " + std::to_string(file.getAge()) +
			"   " + file.getPlaceOfOrigin() + "   " + file.getPhotograph()));
}

int MainWindow::getSelectedIndex() {
	QModelIndexList selectedIndexes = this->ui.victimsListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->ui.nameLineEdit->clear();
		this->ui.ageLineEdit->clear();
		this->ui.photoLineEdit->clear();
		this->ui.placeLineEdit->clear();
		return -1;
	}
	return selectedIndexes.at(0).row();
}

int MainWindow::getSelectedIndexMylist() {
	QModelIndexList selectedIndexes = this->ui.myListListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->ui.nameLineEdit->clear();
		this->ui.ageLineEdit->clear();
		this->ui.photoLineEdit->clear();
		this->ui.placeLineEdit->clear();
		return -1;
	}
	return selectedIndexes.at(0).row();
}

void MainWindow::displayError(std::string errorString) {
	QMessageBox::critical(this, "Error!", QString::fromStdString(errorString));
}

void MainWindow::populateMylist() {
	this->ui.myListListWidget->clear();
	std::vector<VictimFile> allFiles = this->service.getMyList();
	for (auto file : allFiles)
		this->ui.myListListWidget->addItem(QString::fromStdString(file.getName() + "   " + std::to_string(file.getAge()) +
			"   " + file.getPlaceOfOrigin() + "   " + file.getPhotograph()));

}

void MainWindow::populateMyListTableView() {
}

void MainWindow::addFile() {
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string ageString = this->ui.ageLineEdit->text().toStdString();
	std::string photograph = this->ui.photoLineEdit->text().toStdString();
	std::string place = this->ui.placeLineEdit->text().toStdString();

	int age = std::atoi(ageString.c_str());
	if (age == 0) {
		this->displayError("Invalid AGE");
		return;
	}

	try {
		this->service.addVictimFile(name, place, age, photograph);
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
	this->populateList();

	int lastElementIndex = this->service.getAll().size() - 1;
	this->ui.victimsListWidget->setCurrentRow(lastElementIndex);
}

void MainWindow::updateFile() {
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string ageString = this->ui.ageLineEdit->text().toStdString();
	std::string photograph = this->ui.photoLineEdit->text().toStdString();
	std::string place = this->ui.placeLineEdit->text().toStdString();

	int age = std::atoi(ageString.c_str());
	if (age == 0) {
		this->displayError("Invalid AGE");
		return;
	}

	try {
		this->service.updateVictimFile(name, place, age, photograph);
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
	this->populateList();
}

void MainWindow::removeFile() {
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0) {
		this->displayError("No item selected");
		return;
	}
	std::string name = this->ui.nameLineEdit->text().toStdString();
	try {
		this->service.deleteVictimFileByName(name);
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
	this->populateList();
	int lastElementIndex = this->service.getAll().size() - 1;
	this->ui.victimsListWidget->setCurrentRow(lastElementIndex);
}

void MainWindow::populateLineEdits() {
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
		return;
	VictimFile file = this->service.getAll()[selectedIndex];
	this->ui.nameLineEdit->setText(QString::fromStdString(file.getName()));
	this->ui.ageLineEdit->setText(QString::fromStdString(std::to_string(file.getAge())));
	this->ui.photoLineEdit->setText(QString::fromStdString(file.getPhotograph()));
	this->ui.placeLineEdit->setText(QString::fromStdString(file.getPlaceOfOrigin()));
}

void MainWindow::next() {
	int index;
	try {
		index = this->service.next();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
	this->ui.victimsListWidget->setCurrentRow(index);

	VictimFile file = this->service.getAll()[index];
	this->ui.nameLineEdit_2->setText(QString::fromStdString(file.getName()));
	this->ui.ageLineEdit_2->setText(QString::fromStdString(std::to_string(file.getAge())));
	this->ui.photoLineEdit_2->setText(QString::fromStdString(file.getPhotograph()));
	this->ui.placeLineEdit_2->setText(QString::fromStdString(file.getPlaceOfOrigin()));


}

void MainWindow::save() {
	std::string name = this->ui.nameLineEdit->text().toStdString();
	try {
		this->service.save(name);
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
	this->populateMylist();
	emit myListModel->layoutChanged();
}

void MainWindow::open() {
	try {
		this->service.displayMyList();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
		return;
	}
}

void MainWindow::filterList() {

	std::string place = this->ui.placeLineEdit_2->text().toStdString();
	std::string ageString = this->ui.ageLineEdit_2->text().toStdString();
	std::vector<VictimFile> filteredFiles{};

	if (place.empty()) {
		try {
			filteredFiles = this->service.filterByAge(std::atoi(ageString.c_str()));
		}
		catch (std::exception& ex) {
			this->displayError(ex.what());
			return;
		}
	}
	else {
		try {
			filteredFiles = this->service.filterPlaceOfOriginAndAge(place, std::atoi(ageString.c_str()));
		}
		catch (std::exception& ex) {
			this->displayError(ex.what());
			return;
		}
	}

	this->ui.FilteredListWidget->clear();
	for (auto file : filteredFiles)
		this->ui.FilteredListWidget->addItem(QString::fromStdString(file.getName() + "   " + std::to_string(file.getAge()) +
			"   " + file.getPlaceOfOrigin() + "   " + file.getPhotograph()));

}

void MainWindow::undoMain() {
	try {
		this->service.undoMain();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
	}
	this->populateList();
}

void MainWindow::redoMain() {
	try {
		this->service.redoMain();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
	}
	this->populateList();
}

void MainWindow::undoMylist() {
	try {
		this->service.undoMylist();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
	}
	this->populateMylist();
	//this->myListWidget->update();
	emit myListModel->layoutChanged();
	
}

void MainWindow::redoMylist() {
	try {
		this->service.redoMylist();
	}
	catch (std::exception& ex) {
		this->displayError(ex.what());
	}
	this->populateMylist();
	//this->myListWidget->update();
	emit myListModel->layoutChanged();
}

void MainWindow::openView() {

	myListWidget->show();
}



