#pragma once

#include <QWidget>
#include "ui_MyListWidget.h"
#include "MylistModel.h"


class MyListWidget : public QWidget
{
	Q_OBJECT

public:
	MyListWidget(MylistModel* myListTableModel, QWidget *parent = Q_NULLPTR);
	~MyListWidget();

private:

	Ui::MyListWidget ui;
public:
	MylistModel* myListTableModel;
	
};
