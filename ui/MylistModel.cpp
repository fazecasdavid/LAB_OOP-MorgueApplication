#include "MylistModel.h"
#include <qimage.h>
#include <qpixmap.h>

MylistModel::MylistModel(VirtualRepository* repository) : repository{ repository } {}

int MylistModel::rowCount(const QModelIndex& parent) const {
	return this->repository->getAll().size();
}

int MylistModel::columnCount(const QModelIndex& parent) const {
	return 4;	//Name    PlaceOfOrigin    Age    Photograph   
}

QVariant MylistModel::data(const QModelIndex& index, int role) const {

	VictimFile victimFile = this->repository->getAll()[index.row()];
	int columnIndex = index.column();

	QString photographPath = QString::fromStdString("C:\\Users\\David\\source\\TEST\\" + victimFile.getPhotograph());
	QImage image{ photographPath };

	if (role == Qt::DisplayRole) {
		if (columnIndex == 0)
			return QString::fromStdString(victimFile.getName());
		else if (columnIndex == 1)
			return QString::fromStdString(std::to_string(victimFile.getAge()));
		else if (columnIndex == 2)
			return QString::fromStdString(victimFile.getPlaceOfOrigin());
	}
	QPixmap pixmap(photographPath);
	if (columnIndex == 3) {
		
		if (role == Qt::DecorationRole)
			return pixmap;   // return QPixmap for decoration role

		
	}
	if (role == Qt::SizeHintRole)
		return pixmap.size(); // in case need the image size
	


	return QVariant();
}

QVariant MylistModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return QString("Name");
			else if (section == 1)
				return QString("Age");
			else if (section == 2)
				return QString("PlaceOfOrigin");
			else if (section == 3)
				return QString("Photograph");
		}
	}
	return QVariant();
}
