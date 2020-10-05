#include "AddConst.h"
AddConst::AddConst(QWidget*pwgt) : QDialog(pwgt)
{
   LayForm->addRow(textNameconst,editNameconst);
   LayForm->addRow(textNamelay,editNamelay);
   LayForm->addRow(textLayh,editLayh);
   LayForm->addRow(Dellay,Addlay);
   LayForm->addRow(Cancel,Okey);
   LayVertical->addLayout(LayForm);
   LayVertical->addWidget(table);
   setLayout(LayVertical);
   table->setColumnCount(2);
   connect(Addlay,SIGNAL(clicked()),this,SLOT(AddlaySlot()));
   connect(Okey,SIGNAL(clicked()),this,SLOT(OkeySlot()));
   connect(Cancel,SIGNAL(clicked()),this,SLOT(CancelSlot()));
   connect(Dellay,SIGNAL(clicked()),this,SLOT(DellaySlot()));
}
void AddConst::bildtable(){
    table->setRowCount(list.size());
    for(int row=0; row!=list.size(); ++row){
        QTableWidgetItem *newItem1 = new QTableWidgetItem(list[row].Name);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("%1").arg(list[row].layerthin));
        table->setItem(row, 0, newItem1);
        table->setItem(row, 1, newItem2);
    }
}
void AddConst::AddlaySlot(){
    UnitConst unit;
    unit.Name=editNamelay->text();
    unit.layerthin=editLayh->text().toDouble();
    list.push_back(unit);
    bildtable();
}
void AddConst::OkeySlot(){
 QPair<QString, QVector<UnitConst>> pair=qMakePair(editNameconst->text(),list);
 emit CreatConst(pair);
 close();
}
void AddConst::CancelSlot(){
    list.clear();
    close();
}
void AddConst::DellaySlot(){
    if(!list.isEmpty()){
    list.pop_back();
    bildtable();}
}
