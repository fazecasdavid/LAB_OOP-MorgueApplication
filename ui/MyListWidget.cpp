#include "MyListWidget.h"



MyListWidget::MyListWidget(MylistModel* myListTableModel, QWidget *parent) : myListTableModel(myListTableModel), QWidget(parent)
{
	ui.setupUi(this);
	this->ui.MyListtableView->setModel(myListTableModel);
	this->ui.MyListtableView->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);
	QHeaderView* verticalHeader = this->ui.MyListtableView->verticalHeader();
	verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader->setDefaultSectionSize(100);
	//this->ui.MyListtableView->verticalHeader()->setStretchLastSection(true);
		
}

MyListWidget::~MyListWidget()
{
}
