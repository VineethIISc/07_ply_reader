/*
reference : https://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html on date 31/07/19
reference for dock windows: https://doc.qt.io/qt-5/qtwidgets-mainwindows-dockwidgets-example.html on 1/8/19
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>


class MainWindow : public QMainWindow
{
public:
	MainWindow();
	
private slots:
	void newFile();

private:
	void createMenus();
	void createActions();
	void createToolbar();
	void createDockWindows();

private:
	//Menus
	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* viewMenu;
	
	//ToolBar
	QToolBar* fileToolBar;

	//List of items
	QListWidget* itemsList;

	//Action
	QAction* newAct;
	QAction* openAct;
	QAction* saveAct;
	QAction* exitAct;
	QAction* propertyAct;

	//Label
	QLabel* infoLabel;
};
#endif // !MAIN_WINDOW_h



