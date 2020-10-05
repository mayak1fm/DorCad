#include "AddAxis.h"
AddAxis::AddAxis(QWidget*pwgt) : QDialog(pwgt)
{
   adressString->setMinimumSize(300,20);
   LayForm->addRow(adressString,Open);
   LayForm->addRow(Cancel,Okey);
   setLayout(LayForm);
   connect(Open,SIGNAL(clicked()),this,SLOT(OpenSlot()));
   connect(Okey,SIGNAL(clicked()),this,SLOT(OkeySlot()));
   connect(Cancel,SIGNAL(clicked()),this,SLOT(CancelSlot()));

}
void AddAxis::OpenSlot(){
    adressString->setText(QFileDialog::getOpenFileName());
}
void AddAxis::OkeySlot(){
    adress=adressString->text();
    emit CreateAxis(adress);
    close();
}
void AddAxis::CancelSlot(){
    close();
}
