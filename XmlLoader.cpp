#include "XmlLoader.h"

XmlLoader::XmlLoader(ProjectBase& Base):base(Base)
{

}

bool XmlLoader::load(QString adress)
{

    QFile* file=new QFile(adress);

    if (!file->open(QIODevice::ReadOnly)) {return false;}

    if (!RoadBase.setContent(file)) {return false;}

    return ParceBase();
}





bool XmlLoader::ParceBase(){

    QDomElement RBase=RoadBase.documentElement().firstChildElement();

    while(!RBase.isNull()){

        if(RBase.tagName()=="Properties"){
            if(!ParceProp(RBase)) return false;
            qDebug()<<"Prop loading is done!!";
        }

        if(RBase.tagName()=="ConstructiveBase"){
            if(!ParceConstr(RBase)) return false;
            qDebug()<<"ConstructiveBase is done!!";
        }


        if(RBase.tagName()=="Base"){
            if(!ParceCut(RBase)) return false;
            qDebug()<<"Base loading is done!!";
        }

        RBase=RBase.nextSiblingElement();
    }
    return true;
}


bool XmlLoader:: ParceConstr(QDomElement& RBase){

    QDomElement Construct=RBase.firstChildElement();

    while (!Construct.isNull()) {
        QDomElement unit=Construct.firstChildElement();
        if(!ParceConstUnit(unit)){return false;}
        Construct=Construct.nextSiblingElement();
    }
    return true;
}

bool XmlLoader::ParceConstUnit(QDomElement &unit)
{
    QString name;
    QVector<UnitConst> pie;
    while (!unit.isNull()) {
        if(unit.tagName()=="name"){
            name=unit.text();
        }
        else if (unit.tagName()=="pie"){
            pie=ParcePie(unit);
        }
        else {
            qDebug()<<unit.tagName();
            return false;
        }


        unit=unit.nextSiblingElement();
    }

    base.AddConstruct(name,pie);
    return true;
}

QVector<UnitConst> XmlLoader::ParcePie(QDomElement &pie)
{
    QVector<UnitConst> PieLayers;
    QDomElement layers=pie.firstChildElement();
    while (!layers.isNull()) {
        QDomElement name=layers.firstChildElement();
        QDomElement thin=layers.lastChildElement();
        PieLayers.push_back({name.text(),thin.text().toDouble()});
        layers=layers.nextSiblingElement();
    }

    return PieLayers;
}


bool XmlLoader::ParceProp(QDomElement& Prop){


        QDomElement NameBase=Prop.firstChildElement();
        QDomElement DateCreation=NameBase.nextSiblingElement();
        QDomElement DateChange=DateCreation.nextSiblingElement();
        QDomElement CountBorder=DateChange.nextSiblingElement();
        debugElement(DateCreation);

        if(NameBase.tagName()=="NameBase"&&
           DateCreation.tagName()=="DateCreation"&&
           DateChange.tagName()=="DateChange"&&
           CountBorder.tagName()=="CountBorder" ){
           base.SetName(NameBase.text());
           base.setDataCreation(QDateTime::fromString(DateCreation.text(),DateFormat));
           base.setDataChange(QDateTime::fromString(DateChange.text(),DateFormat));
           base.setCountBorder(CountBorder.text().toInt());

            return  true;
        }

        else return false;

}

bool XmlLoader::ParceCut(QDomElement &Base){


    auto list=Base.elementsByTagName("unit");
    for(int i=0;i<list.size();i++){
        double pk=list.at(i).toElement().attribute("pk").toDouble();
        double HeightMark=0;
        bool isBorder;
        bool isMark;
        bool isEmpty;

        QVector<Element> left;
        QVector<Element> right;
        QVector<Element> leftborder;
        QVector<Element> rightborder;

        QDomElement unit=list.at(i).toElement();

        QDomElement element=unit.firstChildElement();

        while (!element.isNull()) {

           if(element.tagName()=="HeightMark"){
               HeightMark=element.text().toDouble();

           }
           if(element.tagName()=="LEFT"){
               left=ParceVectorElement(element);
           }
           if(element.tagName()=="RIGHT"){
               right=ParceVectorElement(element);
           }
           if(element.tagName()=="Rborder"){
               rightborder=ParceVectorElement(element);
           }
           if(element.tagName()=="LBorder"){
               leftborder=ParceVectorElement(element);
           }
           if(element.tagName()=="isBorder"){
               element.text()=="true"? isBorder=true:isBorder=false;
           }
           if(element.tagName()=="isMark"){
               element.text()=="true"? isMark=true:isMark=false;
           }
           if(element.tagName()=="isEmpty"){
               element.text()=="true"? isEmpty=true:isEmpty=false;
           }
         element=element.nextSiblingElement();
        }

        UnitBase ub(HeightMark,left,right,isBorder,leftborder,rightborder,isMark);
        base.AddCut(pk,ub);
    }
    return true;
}

QVector<Element> XmlLoader::ParceVectorElement(QDomElement &unit) {

QDomElement element=unit.firstChildElement();
QVector<Element> result;
    double widht;
    double grad;
    bool border;
    QString constr;
    TypeElement type;

    while (!element.isNull()) {

        if (element.tagName()=="width"){
            widht=element.text().toDouble();
        }
        if(element.tagName()=="grad"){
            grad=element.text().toDouble();
        }
        if(element.tagName()=="border"){
            element.text()=="true"? border=true:border=false;
        }
        if(element.tagName()=="TypeElement"){
            auto it=std::find(Type.begin(),Type.end(),element.text());
            type=TypeElement(it-Type.begin());

        }
        if(element.tagName()=="Constructive"){
            constr=element.text();
            result.push_back(Element(widht,grad,type,constr,border));

        }
        element=element.nextSiblingElement();

    }
    return result;
}


void debugElement(const QDomElement& el)
{
    qDebug()<<"Tag "<<el.tagName();
    if(el.tagName()=="unit"){
     qDebug()<<"atr "<<el.attribute("pk");
    }


}


