#include "ObjectWindow.h"

ObjectWindow::ObjectWindow(QWidget *parent) : QWidget(parent)
{
  setWindowFlag(Qt::Window);
  resize(640,480);
  setAutoFillBackground(true);  
  lay->addWidget(viewCut);
  lay->addWidget(choiseCut);
  lay2->addWidget(table);
  lay2->addLayout(lay);
  setLayout(lay2);
  connect(choiseCut,SIGNAL(show(double)),viewCut,SLOT(PaintCut(double)));

}
void ObjectWindow::Setname(QString &namebase){
    base.SetName(namebase);
    namewindow=namebase;
    this->setWindowTitle(namebase);
}

void ObjectWindow::addConst(){
   AddConst* constwindow=new AddConst(this);
   constwindow->setWindowTitle("Добавление конструктива");
   constwindow->show();
   connect(constwindow,SIGNAL(CreatConst(QPair<QString,QVector<UnitConst>> )),
           this,SLOT(addConsttoBase(QPair<QString,QVector<UnitConst>>)));
}
void ObjectWindow::addConsttoBase(QPair<QString, QVector<UnitConst>> pair){
    base.AddConstruct(pair.first,pair.second);
}
void ObjectWindow::addAxis(){
    AddAxis* axiswindow=new AddAxis(this);
    axiswindow->setWindowTitle("Добавление оси трассы");
    axiswindow->show();
    connect(axiswindow,SIGNAL(CreateAxis(QString&)),
            this,SLOT(addAxistoBase(QString&)));

}
void ObjectWindow::addAxistoBase(QString& str){
    QFile axis_file(str);
    if(!axis_file.open(QIODevice::ReadOnly)){
        qWarning("Cannot open file for reading");
        return;
    }

        QString axis_str=axis_file.readAll();
        QStringList axis_list=axis_str.split('\n');
        if(!base.AddAxis(axis_list)){
           {(new QErrorMessage(this))->
             showMessage("Не удовлетворяет условиям, одна сторока или не правильный формат");}
        }
        else{
            UpdateAllView();
        }
}

void ObjectWindow::addElement(){
    try {

        AddElement* elementwindow= new AddElement(this);
        elementwindow->setWindowTitle("Импорт элементов трассы");
        elementwindow->show();
        connect(elementwindow,SIGNAL(CreateElement(QString&,TypeElement)),
            this,SLOT(addElementtoBase(QString&,TypeElement)));
    } catch (int a) {
        if(a==-1){
           (new QErrorMessage(this))->showMessage("НЕ удовлетворяет условиям, одна сторока или не правильный формат");
        }
    }

}

void ObjectWindow::setConst()
{


}
void ObjectWindow::addElementtoBase(QString& str,TypeElement t){
    QFile* file=new QFile(str);
    if(!file->open(QIODevice::ReadOnly)){
        (new QErrorMessage(this))->showMessage("Не доступа к файлу "+str);
        return;
    }
    QString elem=file->readAll();
    QStringList list=elem.split('\n');
    if(!base.AddElements(list,t)){
        (new QErrorMessage(this))->showMessage("НЕ удовлетворяет условиям, одна сторока или не правильный формат");
    }
    else{
    UpdateAllView();
    }

}

void ObjectWindow::save()
{

    XmlSaver saver(base);
    saver.save(QFileDialog::getSaveFileName());
}

void ObjectWindow::UpdateAllView()
{
    table->BildTable();
    choiseCut->update();
    viewCut->updateLastPK();
}

ProjectBase& ObjectWindow::open()
{
    return base;
}




