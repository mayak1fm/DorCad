#include "SetConst.h"

SetConst::SetConst(ProjectBase& Base,QWidget*pwgt):QDialog(pwgt),base(Base)
{
    Okey=new QPushButton("OK");
    Cancel=new QPushButton("Cancel");
    AllElementsChoice= new QCheckBox();
    Description= new QLabel("Конструктив будет присвон всем"
                            " елементам на данном участке");
    AllElemChoiceLabel= new QLabel("Все елементы");
    PkBeginLabel = new QLabel ("Начало участка, м");
    PkEndLabel = new QLabel ("Конец участка, м");
    ConChoiceLabel =new QLabel ("Конструктив");
    TypeElemChoiseLabel = new QLabel ("Тип Елемента");
    ConstuctiveChoise =new QComboBox();
    TypeElementChoise= new QComboBox();
    PkBegin = new QLineEdit();
    PkEnd = new QLineEdit();
    plan= new PlanView(base,this);
    Side=LEFT;
    LaneNumber=1000;

    connect(Okey,SIGNAL(clicked()),this,SLOT(OkeySlot()));
    connect(Cancel,SIGNAL(clicked()),this,SLOT(CancelSlot()));
    connect(AllElementsChoice,SIGNAL(triggered()),this,SLOT(CheckBoxSlot()));
}

void SetConst::OkeySlot(){


    base.insert_new_pk(PkBegin->text().toDouble());
    base.insert_new_pk(PkEnd->text().toDouble());

    auto begin=base.lowerBound(PkBegin->text().toDouble());
    auto it=begin;
    auto end=base.lowerBound(PkEnd->text().toDouble());

    while (it!=end) {
        if(AllElementsChoice->isChecked())
           base.SetConstructive(it.key(),ConstuctiveChoise->currentText(),
                                TypeElement(TypeElementChoise->currentIndex()));
        else
           base.SetConstructive(it.key(),ConstuctiveChoise->currentText(),
                                TypeElement(TypeElementChoise->currentIndex()),Side,LaneNumber);

    }
    close();
}
void SetConst::CancelSlot(){
    close();
}
void SetConst::CheckBoxSlot(){
    if(!AllElementsChoice->isChecked()){
        plan->hide();
    }
    else
        plan->show();
}
