#include "CutChoise.h"

CutChoise::CutChoise(ProjectBase& Base,QWidget* parent):base(Base),
                                                        QComboBox(parent)
{
    connect(this,SIGNAL(activated(int)),this,SLOT(ShowCut(int)));
    update();
}
void CutChoise::update(){
    pkString.clear();
    pkDouble.clear();
    auto it=base.GetBase().begin();
    auto end=base.GetBase().end();
    while (it!=end) {
        pkString.push_back(PkFormat(it.key()));
        pkDouble.push_back(it.key());
        it++;
    }
    this->addItems(pkString);
}

void CutChoise::ShowCut(int n){
    if(!pkDouble.isEmpty())
    {

        emit show(pkDouble[n]);
    }
}
