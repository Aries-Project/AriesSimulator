#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_gl=new  NGLScene(this);
    this->setCentralWidget(m_gl);
    //ui->horizontalLayout->addWidget(m_gl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
