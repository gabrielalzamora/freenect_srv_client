/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMenu2;
    QAction *actionOpcion2_1;
    QAction *actionOpcion1_2;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_server;
    QLabel *label_ip;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QGraphicsView *gviewDista;
    QGraphicsView *gviewVideo;
    QGraphicsView *gviewBarre;
    QOpenGLWidget *oglWidget;
    QWidget *tab_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_k;
    QComboBox *combo;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pbGo;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pbStop;
    QPushButton *pbHalt;
    QMenuBar *menuBar;
    QMenu *menuMenu1;
    QMenu *menuMenu2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(817, 596);
        actionMenu2 = new QAction(MainWindow);
        actionMenu2->setObjectName(QStringLiteral("actionMenu2"));
        actionOpcion2_1 = new QAction(MainWindow);
        actionOpcion2_1->setObjectName(QStringLiteral("actionOpcion2_1"));
        actionOpcion1_2 = new QAction(MainWindow);
        actionOpcion1_2->setObjectName(QStringLiteral("actionOpcion1_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_server = new QLabel(centralWidget);
        label_server->setObjectName(QStringLiteral("label_server"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_server->sizePolicy().hasHeightForWidth());
        label_server->setSizePolicy(sizePolicy);
        label_server->setMaximumSize(QSize(50, 30));

        gridLayout_2->addWidget(label_server, 0, 0, 1, 1);

        label_ip = new QLabel(centralWidget);
        label_ip->setObjectName(QStringLiteral("label_ip"));

        gridLayout_2->addWidget(label_ip, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gviewDista = new QGraphicsView(tab);
        gviewDista->setObjectName(QStringLiteral("gviewDista"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gviewDista->sizePolicy().hasHeightForWidth());
        gviewDista->setSizePolicy(sizePolicy1);
        gviewDista->setMinimumSize(QSize(320, 240));
        gviewDista->setBaseSize(QSize(320, 240));

        gridLayout->addWidget(gviewDista, 0, 0, 1, 1);

        gviewVideo = new QGraphicsView(tab);
        gviewVideo->setObjectName(QStringLiteral("gviewVideo"));
        sizePolicy1.setHeightForWidth(gviewVideo->sizePolicy().hasHeightForWidth());
        gviewVideo->setSizePolicy(sizePolicy1);
        gviewVideo->setMinimumSize(QSize(320, 240));
        gviewVideo->setBaseSize(QSize(320, 240));

        gridLayout->addWidget(gviewVideo, 0, 1, 1, 1);

        gviewBarre = new QGraphicsView(tab);
        gviewBarre->setObjectName(QStringLiteral("gviewBarre"));
        sizePolicy1.setHeightForWidth(gviewBarre->sizePolicy().hasHeightForWidth());
        gviewBarre->setSizePolicy(sizePolicy1);
        gviewBarre->setMinimumSize(QSize(320, 240));
        gviewBarre->setBaseSize(QSize(320, 240));

        gridLayout->addWidget(gviewBarre, 1, 0, 1, 1);

        oglWidget = new QOpenGLWidget(tab);
        oglWidget->setObjectName(QStringLiteral("oglWidget"));
        oglWidget->setMinimumSize(QSize(320, 240));
        oglWidget->setBaseSize(QSize(320, 240));

        gridLayout->addWidget(oglWidget, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 2, 9, 1);

        verticalSpacer = new QSpacerItem(88, 127, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 2);

        label_k = new QLabel(centralWidget);
        label_k->setObjectName(QStringLiteral("label_k"));

        gridLayout_2->addWidget(label_k, 2, 0, 1, 1);

        combo = new QComboBox(centralWidget);
        combo->setObjectName(QStringLiteral("combo"));

        gridLayout_2->addWidget(combo, 3, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(68, 128, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 0, 1, 2);

        pbGo = new QPushButton(centralWidget);
        pbGo->setObjectName(QStringLiteral("pbGo"));
        pbGo->setEnabled(false);

        gridLayout_2->addWidget(pbGo, 5, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(138, 127, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 6, 0, 1, 2);

        pbStop = new QPushButton(centralWidget);
        pbStop->setObjectName(QStringLiteral("pbStop"));
        pbStop->setEnabled(false);

        gridLayout_2->addWidget(pbStop, 7, 0, 1, 2);

        pbHalt = new QPushButton(centralWidget);
        pbHalt->setObjectName(QStringLiteral("pbHalt"));

        gridLayout_2->addWidget(pbHalt, 8, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 817, 22));
        menuMenu1 = new QMenu(menuBar);
        menuMenu1->setObjectName(QStringLiteral("menuMenu1"));
        menuMenu2 = new QMenu(menuBar);
        menuMenu2->setObjectName(QStringLiteral("menuMenu2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu1->menuAction());
        menuBar->addAction(menuMenu2->menuAction());
        menuMenu1->addAction(actionMenu2);
        menuMenu1->addAction(actionOpcion1_2);
        menuMenu2->addAction(actionOpcion2_1);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionMenu2->setText(QApplication::translate("MainWindow", "opcion1_1", 0));
        actionOpcion2_1->setText(QApplication::translate("MainWindow", "opcion2_1", 0));
        actionOpcion1_2->setText(QApplication::translate("MainWindow", "opcion1_2", 0));
        label_server->setText(QApplication::translate("MainWindow", "server ip:", 0));
        label_ip->setText(QApplication::translate("MainWindow", "localhost", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        label_k->setText(QApplication::translate("MainWindow", "select k", 0));
        combo->setCurrentText(QString());
        pbGo->setText(QApplication::translate("MainWindow", "Go", 0));
        pbStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        pbHalt->setText(QApplication::translate("MainWindow", "Achtung MINEN", 0));
        menuMenu1->setTitle(QApplication::translate("MainWindow", "menu1", 0));
        menuMenu2->setTitle(QApplication::translate("MainWindow", "menu2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
