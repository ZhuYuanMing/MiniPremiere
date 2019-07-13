#ifndef APP_H
#define APP_H

#include "../model/Model.h"
#include "../View/MainWindow.h"
#include "../ViewModel/ViewModel.h"

class App
{
private:
	std::shared_ptr<MainWindow> mainwindow;
	std::shared_ptr<Model> model;
	std::shared_ptr<ViewModel> viewmodel;

public:
	App();
	void run();
};
#endif
