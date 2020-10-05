#include "table_view.h"

Table_view::Table_view(ProjectBase& Base, QWidget *parent): QTableWidget(parent),base(Base)
{
if(base.is_empty()){
   this->setRowCount(20);
   this->setColumnCount(3);
    }
else{
     this->BildTable();
    }

}


QString Table_view::ElemFormat(const Element& el){
    QString type;
        switch (el.type) {
        case lane: type="Полоса(";
        break;
        case roadside: type="Обочина(";
        break;
        case slope: type="Откос(";
        break;
        case ditch: type="Кювет(";
        break;
    default:
        type= "Unknown";
        break;
    }
       return type+=QString::number(el.width,'f',2)+"м./"+QString::number(el.grad*1000)+')';

}
void Table_view::printPK(const QMap<double,UnitBase>::iterator& iter,  const int& i){
    QTableWidgetItem *PK = new QTableWidgetItem(PkFormat(iter.key()));
    this->setItem(i,0,PK);
    if(iter.value().GetUnitBase().isBor){
    this->setItem(i+1,0,PK);
    }

}
void Table_view::printMarkAxis(const QMap<double,UnitBase>::iterator& iter, const int& i){
    QTableWidgetItem *Mark=new QTableWidgetItem(QString::number(iter.value().GetMark(),'f',2));
    int MarkColumn=column.first+1;
    this->setItem(i,MarkColumn,Mark);
    if(iter.value().GetUnitBase().isBor){
        this->setItem(i+1,MarkColumn,Mark);
    }
}

void Table_view::print_LAndR(const QMap<double, UnitBase>::iterator &iter, const int &i){

    r_base unit=iter.value().GetUnitBase();
     int c_counter=column.first;

         for(auto &it:unit.l){
             QTableWidgetItem *elem=new QTableWidgetItem(ElemFormat(it));
             this->setItem(i,c_counter,elem);
             c_counter--;
         }
     if(unit.isBor){
         c_counter=column.first;
         for(auto &it:unit.lBorder){
             QTableWidgetItem *elem=new QTableWidgetItem(ElemFormat(it));
             this->setItem(i+1,c_counter,elem);
             c_counter--;
         }
     }

     c_counter=column.first+2;

              for(auto &it:unit.r){
                  QTableWidgetItem *elem=new QTableWidgetItem(ElemFormat(it));
                  this->setItem(i,c_counter,elem);
                  c_counter++;
              }
          if(unit.isBor){
              c_counter=column.first+2;
              for(auto &it:unit.rBorder){
                  QTableWidgetItem *elem=new QTableWidgetItem(ElemFormat(it));
                  this->setItem(i+1,c_counter,elem);
                  c_counter++;
              }
          }
}



void Table_view::BildTable(){
    this->clear();
    row=base.size();
    column=base.MaxWide();
    qDebug()<<column;
    this->setRowCount(row);
    this->setColumnCount(column.first+column.second+AxisAndMark);
    auto iter=base.GetBase().begin();
    for(int i=0;i<row;i++){
        printPK(iter,i);
        printMarkAxis(iter,i);
        print_LAndR(iter,i);
        if(iter.value().GetUnitBase().isBor){i++;}
        if(iter!=base.GetBase().end()){iter++;}

    }
}
