#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab12.h"
#include "Service.h"
#include "MylistModel.h"
#include "MyListWidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(Service& service, QWidget* parent = Q_NULLPTR);

private:
	Ui::lab12Class ui;
	Service& service;
	MyListWidget* myListWidget;
	MylistModel* myListModel;


private:
	void populateList();
	int getSelectedIndex();
	int getSelectedIndexMylist();
	void displayError(std::string errorString);
	void populateMylist();
	void populateMyListTableView();


public slots:

	void addFile();
	void updateFile();
	void removeFile();
	void populateLineEdits();
	void next();
	void save();
	void open();
	void filterList();
	void undoMain();
	void redoMain();
	void undoMylist();
	void redoMylist();

	void openView();

};
