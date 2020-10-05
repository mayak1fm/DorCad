#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    File=menuBar()->addMenu("File");
    File->addAction(NewOb);
    File->addAction(OpenConst);
    File->addAction(Save);
    connect(NewOb,SIGNAL(triggered()),this,SLOT(NewC()));
    connect(OpenConst,SIGNAL(triggered()),this,SLOT(open()));
    Project=menuBar()->addMenu("Project");
    Project->addAction(NewConst);
    Project->addAction(AddAxis);
    Project->addAction(AddElement);
    Project->addAction(SetConst);

}
//slots
void MainWindow::NewC(){
    CreateNewObWindow * SaveWindow = new CreateNewObWindow (this);
    connect(SaveWindow,SIGNAL(createw(QPair<QString,QString>)),this,SLOT(CreateProjectWindow(QPair<QString,QString>)));
    SaveWindow->show();
    
}
void MainWindow::CreateProjectWindow(QPair<QString,QString> str){
    ObjectWindow* window= new ObjectWindow(this);
    connect(NewConst,SIGNAL(triggered()),window,SLOT(addConst()));
    connect(SetConst,SIGNAL(triggerde()),window,SLOT(setConst()));
    connect(AddAxis,SIGNAL(triggered()),window,SLOT(addAxis()));
    connect(AddElement,SIGNAL(triggered()),window,SLOT(addElement()));
    connect(Save,SIGNAL(triggered()),window,SLOT(save()));

    window->Setname(str.first);
    window->show();
}


void MainWindow::open(){
    ObjectWindow* window= new ObjectWindow(this);
    connect(NewConst,SIGNAL(triggered()),window,SLOT(addConst()));
    connect(AddAxis,SIGNAL(triggered()),window,SLOT(addAxis()));
    connect(AddElement,SIGNAL(triggered()),window,SLOT(addElement()));
    connect(Save,SIGNAL(triggered()),window,SLOT(save()));

    XmlLoader loader(window->open());
    if(loader.load(QFileDialog::getOpenFileName())){
        QString name=window->open().GiveName();
        window->Setname(name);
        window->show();
        window->UpdateAllView();

    }
    else{
        {(new QErrorMessage(this))->
          showMessage("Не удаестся открыть файл");}
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
