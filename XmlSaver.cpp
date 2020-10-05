#include "XmlSaver.h"


XmlSaver::XmlSaver(const ProjectBase& Base): baseP(Base)
{
    ProjectDoc=QDomDocument("ProjectBase");
}

bool XmlSaver::save(QString adress)
{
    savebase();
    QFile file (adress);
    if(file.open(QIODevice::WriteOnly)){

        QTextStream(&file)<<ProjectDoc.toString();
        file.close();
        return true;
    }
    else
        return false;
}
void XmlSaver::savebase(){
    ProjectDoc.clear();
    QDomElement RoadBase=ProjectDoc.createElement("RoadBase");
    ProjectDoc.appendChild(RoadBase);
    QDomElement Propertis=ProjectDoc.createElement("Properties");
    RoadBase.appendChild(Propertis);

    Propertis.appendChild( MakeElement ("NameBase",baseP.GiveName()));
    Propertis.appendChild( MakeElement ("DateCreation",baseP.GiveDateCretion().toString(DateFormat)));
    Propertis.appendChild( MakeElement ("DateChange",baseP.GiveDateChange().toString(DateFormat)));
    Propertis.appendChild( MakeElement ("CountBorder",QString::number(baseP.GiveCountBorder())));

    QDomElement ConstructiveBase=ProjectDoc.createElement("ConstructiveBase");
    RoadBase.appendChild(ConstructiveBase);

    saveConstructBase(ConstructiveBase);

    QDomElement BaseData=ProjectDoc.createElement("Base");
    RoadBase.appendChild(BaseData);
    auto it=baseP.GetBase().begin();
    while (it!=baseP.GetBase().end()) {

        QDomElement unit=ProjectDoc.createElement("unit");
        BaseData.appendChild(unit);
        unit.setAttribute("pk",it.key());
        saveUnitBase(it.value(),unit);
        it++;
    }
}

void XmlSaver::saveConstructBase(QDomElement& ConstructiveBase)
{


    for (const auto& i:baseP.GetConstructBase()) {
        QDomElement construct=ProjectDoc.createElement("construct");
        ConstructiveBase.appendChild(construct);
        construct.appendChild(MakeElement("name",i.Name));
        QDomElement pie=ProjectDoc.createElement("pie");
        construct.appendChild(pie);
        saveconstructPie(pie,i.pie);

    }
}

void XmlSaver::saveconstructPie(QDomElement &pie,const QVector<UnitConst>& vpie)
{
        for(const auto& i: vpie){
            QDomElement layer=ProjectDoc.createElement("layer");
            pie.appendChild(layer);
            layer.appendChild(MakeElement("NameLay",i.Name));
            layer.appendChild(MakeElement("thin",QString::number(i.layerthin)));
        }
}

void XmlSaver::saveUnitBase(const UnitBase& unitb,QDomElement& unitElement)
{

    unitElement.appendChild(MakeElement("HeightMark",QString::number(unitb.GetMark())));
    unitElement.appendChild(MakeElement("isBorder",is_bool[unitb.is_Border()]));
    unitElement.appendChild(MakeElement("isMark",is_bool[unitb.isMarked()]));
    unitElement.appendChild(MakeElement("isEmpty",is_bool[unitb.is_empty()]));

    saveSide(unitb.GetLeftElements(),unitElement,LEFT);
    saveSide(unitb.GetRightElements(),unitElement,RIGHT);
    saveSide(unitb.GetBorderLeftElements(),unitElement,Rborder);
    saveSide(unitb.GetBorderRightElements(),unitElement,Lborder);

}

void XmlSaver::saveSide(const QVector<Element> & v, QDomElement &unitElement, side s)
{
    if(v.isEmpty()){return;}    
    QDomElement SideElement=ProjectDoc.createElement(Side[s]);
    unitElement.appendChild(SideElement);
    for(const auto& i:v){
        saveElement(i,SideElement);
    }
}

void XmlSaver::saveElement(const Element &el, QDomElement &SideElement)
{
    SideElement.appendChild(MakeElement("width",QString::number(el.width)));
    SideElement.appendChild(MakeElement("grad",QString::number(el.grad)));
    SideElement.appendChild(MakeElement("border",is_bool[el.border]));
    SideElement.appendChild(MakeElement("TypeElement",Type[el.type]));
    SideElement.appendChild(MakeElement("Constructive",el.Constr));

}




