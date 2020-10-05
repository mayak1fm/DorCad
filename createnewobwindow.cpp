#include "createnewobwindow.h"
CreateNewObWindow::CreateNewObWindow(QWidget*pwgt) : QDialog(pwgt)
{
   LayForm = new QFormLayout;
   Okey = new QPushButton("OK");
   connect(Okey,SIGNAL(clicked()),this,SLOT(OKeySlot()));
   Cancel = new QPushButton("Cancel");
   connect(Cancel,SIGNAL(clicked()),this,SLOT(CancelSlot()));
   Folder = new QPushButton("Folder");
   connect(Folder,SIGNAL(clicked()),this,SLOT(ChoiceF()));
   TextName = new QLabel("Название объекта");
   TextCatalog = new QLabel("Выбор каталога");
   TextCatalogChoise=new QLabel();
   CatalogChoise=new QLabel("Каталог");
   NameEdit=new QLineEdit;
   LayForm->addRow(TextName,NameEdit);
   LayForm->addRow(TextCatalog,Folder);
   LayForm->addRow(CatalogChoise,TextCatalogChoise);
   LayForm->addRow(Okey,Cancel);
   setLayout(LayForm);
   resize(480,150);
}

void CreateNewObWindow::ChoiceF(){
    adrees=QFileDialog::getExistingDirectory();
    TextCatalogChoise->setText(adrees);
}
void CreateNewObWindow::CancelSlot(){
    close();
}
void CreateNewObWindow::OKeySlot(){
    nameObject=NameEdit->text();
    if(!nameObject.isEmpty()&&!adrees.isEmpty()){        
        QPair<QString,QString> str =qMakePair(nameObject,adrees);
        emit createw(str);
        close();

    }
}
