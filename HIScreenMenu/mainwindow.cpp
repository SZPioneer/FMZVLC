#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(1.0);
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_pWidgetCentral            = new QWidgetCentral(this);
    setCentralWidget(m_pWidgetCentral);

//    QRect       rcMain      = QApplication::desktop()->screenGeometry();
//    rcMain.setTop(100);
//    rcMain.setBottom(rcMain.bottom()-40);
//    rcMain.setLeft(30);
//    rcMain.setRight(230);
//    setGeometry(rcMain);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}



