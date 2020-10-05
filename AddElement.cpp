#include "AddElement.h"
AddElement ::AddElement (QWidget*pwgt) : QDialog(pwgt)
{

   ElementTypes->addItems(types);
   adressString->setMinimumSize(300,20);
   LayForm->addRow(adressString,Open);
   LayForm->addRow(Cancel,Okey);
   LayH->addLayout(LayForm);
   LayH->addWidget(ElementTypes);
   setLayout(LayH);
   connect(Open,SIGNAL(clicked()),this,SLOT(OpenSlot()));
   connect(Okey,SIGNAL(clicked()),this,SLOT(OkeySlot()));
   connect(Cancel,SIGNAL(clicked()),this,SLOT(CancelSlot()));

}
void AddElement::OpenSlot(){
    adressString->setText(QFileDialog::getOpenFileName());
}
void AddElement::OkeySlot(){
    adress=adressString->text();

    switch (ElementTypes->currentIndex()) {
    case(lane):emit CreateElement(adress,lane);
        break;
    case(roadside):emit CreateElement(adress,roadside);
        break;
    case(slope):emit CreateElement(adress,slope);
        break;
    case(ditch):emit CreateElement(adress,ditch);
        break;
    }

    close();
}
void AddElement::CancelSlot(){
    close();
}
