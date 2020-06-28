#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <memory>
#include "FileRepository.h"
#include "Repository.h"
#include "Service.h"
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	std::ifstream configFileStream("configFile.txt");
	std::string whereToStore;
	std::string mainRepoPath;
	std::string mylistRepoPath;
	std::getline(configFileStream, whereToStore);
	std::getline(configFileStream, mainRepoPath);
	std::getline(configFileStream, mylistRepoPath);
	configFileStream.close();


	if (whereToStore == "memory") {
		std::unique_ptr<VirtualRepository> repository = std::make_unique<Repository>();
		Service service{ repository.get() };
		if (mylistRepoPath.substr(mylistRepoPath.find_last_of(".") + 1) == "html")
			service.HTML_InitializeTransferredRepository(mylistRepoPath);
		else if (mylistRepoPath.substr(mylistRepoPath.find_last_of(".") + 1) == "csv")
			service.CSV_InitializeTransferredRepository(mylistRepoPath);
		MainWindow GUI{ service };
		GUI.show();
		return a.exec();
	}
	else {
		std::unique_ptr<VirtualRepository> repository = std::make_unique<FileRepository>();
		repository->setFilePath(mainRepoPath);
		Service service{ repository.get() };
		if (mylistRepoPath.substr(mylistRepoPath.find_last_of(".") + 1) == "html")
			service.HTML_InitializeTransferredRepository(mylistRepoPath);
		else if (mylistRepoPath.substr(mylistRepoPath.find_last_of(".") + 1) == "csv")
			service.CSV_InitializeTransferredRepository(mylistRepoPath);
		MainWindow GUI{ service };
		GUI.show();
		return a.exec();
	}

}
