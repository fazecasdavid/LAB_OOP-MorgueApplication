#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"
#include "FileRepository.h"
#include "HTMLRepository.h"


class MylistModel : public QAbstractTableModel {
private:
	VirtualRepository* repository;
public:
	MylistModel(VirtualRepository* repository);

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

