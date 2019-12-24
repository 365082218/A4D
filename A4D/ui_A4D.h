/********************************************************************************
** Form generated from reading UI file 'A4Dh10916.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef A4DH10916_H
#define A4DH10916_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AWidget.h"
QT_BEGIN_NAMESPACE

class Ui_A4DClass
{
public:
	QAction *_File;
	QAction *actionNew_Scene;
	QAction *actionOpen_Scene;
	QAction *actionSave;
	QAction *actionSave_as;
	QAction *actionNew_project;
	QAction *actionOpen_project;
	QAction *actionSave_Project;
	QAction *actionShaded;
	QAction *actionWireframe;
	QAction *actionShaded_Wireframe;
	QAction *actionCW;
	QAction *actionCCW;
	QAction *actionNone;
	QWidget *centralWidget;
	QWidget *verticalLayoutWidget;
	QVBoxLayout *sceneTreeLayout;
	QTreeWidget *treeWidget;
	QWidget *editorWindow;
	QWidget *verticalLayoutWidget_2;
	QVBoxLayout *verticalLayout;
	QWidget *inspectorWindow;
	QMenuBar *menuBar;
	QMenu *menu;
	QMenu *menu_2;
	QMenu *menuShading_Mode;
	QMenu *menuCull_Mode;
	QToolBar *mainToolBar;
	QStatusBar *statusBar;

	void setupUi(QMainWindow *A4DClass)
	{
		if (A4DClass->objectName().isEmpty())
			A4DClass->setObjectName(QStringLiteral("A4DClass"));
		A4DClass->resize(865, 597);
		_File = new QAction(A4DClass);
		_File->setObjectName(QStringLiteral("_File"));
		_File->setCheckable(false);
		actionNew_Scene = new QAction(A4DClass);
		actionNew_Scene->setObjectName(QStringLiteral("actionNew_Scene"));
		actionOpen_Scene = new QAction(A4DClass);
		actionOpen_Scene->setObjectName(QStringLiteral("actionOpen_Scene"));
		actionSave = new QAction(A4DClass);
		actionSave->setObjectName(QStringLiteral("actionSave"));
		actionSave_as = new QAction(A4DClass);
		actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
		actionNew_project = new QAction(A4DClass);
		actionNew_project->setObjectName(QStringLiteral("actionNew_project"));
		actionOpen_project = new QAction(A4DClass);
		actionOpen_project->setObjectName(QStringLiteral("actionOpen_project"));
		actionSave_Project = new QAction(A4DClass);
		actionSave_Project->setObjectName(QStringLiteral("actionSave_Project"));
		actionShaded = new QAction(A4DClass);
		actionShaded->setObjectName(QStringLiteral("actionShaded"));
		actionWireframe = new QAction(A4DClass);
		actionWireframe->setObjectName(QStringLiteral("actionWireframe"));
		actionShaded_Wireframe = new QAction(A4DClass);
		actionShaded_Wireframe->setObjectName(QStringLiteral("actionShaded_Wireframe"));
		actionCW = new QAction(A4DClass);
		actionCW->setObjectName(QStringLiteral("actionCW"));
		actionCCW = new QAction(A4DClass);
		actionCCW->setObjectName(QStringLiteral("actionCCW"));
		actionNone = new QAction(A4DClass);
		actionNone->setObjectName(QStringLiteral("actionNone"));
		centralWidget = new QWidget(A4DClass);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		verticalLayoutWidget = new QWidget(centralWidget);
		verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
		verticalLayoutWidget->setGeometry(QRect(0, 0, 171, 551));
		sceneTreeLayout = new QVBoxLayout(verticalLayoutWidget);
		sceneTreeLayout->setSpacing(6);
		sceneTreeLayout->setContentsMargins(11, 11, 11, 11);
		sceneTreeLayout->setObjectName(QStringLiteral("sceneTreeLayout"));
		sceneTreeLayout->setContentsMargins(0, 0, 0, 0);
		treeWidget = new QTreeWidget(verticalLayoutWidget);
		QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
		__qtreewidgetitem->setText(0, QStringLiteral("1"));
		treeWidget->setHeaderItem(__qtreewidgetitem);
		treeWidget->setObjectName(QStringLiteral("treeWidget"));

		sceneTreeLayout->addWidget(treeWidget);

		//editorWindow = new QWidget(centralWidget);
		editorWindow = new AWidget(centralWidget);
		editorWindow->setObjectName(QStringLiteral("editorWindow"));
		editorWindow->setGeometry(QRect(170, 0, 501, 531));
		verticalLayoutWidget_2 = new QWidget(centralWidget);
		verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
		verticalLayoutWidget_2->setGeometry(QRect(670, 0, 191, 531));
		verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
		verticalLayout->setSpacing(6);
		verticalLayout->setContentsMargins(11, 11, 11, 11);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		inspectorWindow = new QWidget(verticalLayoutWidget_2);
		inspectorWindow->setObjectName(QStringLiteral("inspectorWindow"));

		verticalLayout->addWidget(inspectorWindow);

		A4DClass->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(A4DClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 865, 23));
		menu = new QMenu(menuBar);
		menu->setObjectName(QStringLiteral("menu"));
		menu_2 = new QMenu(menuBar);
		menu_2->setObjectName(QStringLiteral("menu_2"));
		menuShading_Mode = new QMenu(menu_2);
		menuShading_Mode->setObjectName(QStringLiteral("menuShading_Mode"));
		menuCull_Mode = new QMenu(menu_2);
		menuCull_Mode->setObjectName(QStringLiteral("menuCull_Mode"));
		A4DClass->setMenuBar(menuBar);
		mainToolBar = new QToolBar(A4DClass);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		A4DClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
		statusBar = new QStatusBar(A4DClass);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		A4DClass->setStatusBar(statusBar);

		menuBar->addAction(menu->menuAction());
		menuBar->addAction(menu_2->menuAction());
		menu->addAction(actionNew_Scene);
		menu->addAction(actionOpen_Scene);
		menu->addSeparator();
		menu->addAction(actionSave);
		menu->addAction(actionSave_as);
		menu->addSeparator();
		menu->addAction(actionNew_project);
		menu->addAction(actionOpen_project);
		menu->addAction(actionSave_Project);
		menu_2->addAction(menuShading_Mode->menuAction());
		menu_2->addAction(menuCull_Mode->menuAction());
		menuShading_Mode->addAction(actionShaded);
		menuShading_Mode->addAction(actionWireframe);
		menuShading_Mode->addAction(actionShaded_Wireframe);
		menuCull_Mode->addAction(actionNone);
		menuCull_Mode->addAction(actionCW);
		menuCull_Mode->addAction(actionCCW);

		retranslateUi(A4DClass);

		QMetaObject::connectSlotsByName(A4DClass);
	} // setupUi

	void retranslateUi(QMainWindow *A4DClass)
	{
		A4DClass->setWindowTitle(QApplication::translate("A4DClass", "A4D", Q_NULLPTR));
		_File->setText(QApplication::translate("A4DClass", "\346\226\207\344\273\266", Q_NULLPTR));
		actionNew_Scene->setText(QApplication::translate("A4DClass", "New Scene", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
		actionNew_Scene->setToolTip(QApplication::translate("A4DClass", "\345\210\233\345\273\272\344\270\200\344\270\252\347\251\272\347\231\275\345\234\272\346\231\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
		actionOpen_Scene->setText(QApplication::translate("A4DClass", "Open Scene", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
		actionOpen_Scene->setToolTip(QApplication::translate("A4DClass", "\346\211\223\345\274\200\351\200\211\345\256\232\347\232\204\345\234\272\346\231\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
		actionSave->setText(QApplication::translate("A4DClass", "Save", Q_NULLPTR));
		actionSave_as->setText(QApplication::translate("A4DClass", "Save As...", Q_NULLPTR));
		actionNew_project->setText(QApplication::translate("A4DClass", "New Project", Q_NULLPTR));
		actionOpen_project->setText(QApplication::translate("A4DClass", "Open Project", Q_NULLPTR));
		actionSave_Project->setText(QApplication::translate("A4DClass", "Save Project", Q_NULLPTR));
		actionShaded->setText(QApplication::translate("A4DClass", "Shaded", Q_NULLPTR));
		actionWireframe->setText(QApplication::translate("A4DClass", "Wireframe", Q_NULLPTR));
		actionShaded_Wireframe->setText(QApplication::translate("A4DClass", "Shaded Wireframe", Q_NULLPTR));
		actionCW->setText(QApplication::translate("A4DClass", "CW", Q_NULLPTR));
		actionCCW->setText(QApplication::translate("A4DClass", "CCW", Q_NULLPTR));
		actionNone->setText(QApplication::translate("A4DClass", "None", Q_NULLPTR));
		menu->setTitle(QApplication::translate("A4DClass", "\346\226\207\344\273\266", Q_NULLPTR));
		menu_2->setTitle(QApplication::translate("A4DClass", "\350\260\203\350\257\225", Q_NULLPTR));
		menuShading_Mode->setTitle(QApplication::translate("A4DClass", "Shading Mode", Q_NULLPTR));
		menuCull_Mode->setTitle(QApplication::translate("A4DClass", "Cull Mode", Q_NULLPTR));
	} // retranslateUi

};

namespace Ui {
	class A4DClass : public Ui_A4DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // A4DH10916_H
