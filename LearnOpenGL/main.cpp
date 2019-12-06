#include <iostream>
#include <memory>
#include "MainWindow.h"
#include <map>
int main()
{
	{
		std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>();

		mainWindow->Run();
	}
	system("pause");
}