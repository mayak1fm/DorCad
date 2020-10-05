#ifndef XMLLOADER_H
#define XMLLOADER_H
#include<QtXml>
#include"ProjectBase.h"
#include <algorithm>
#include "GlobalConstant.h"


class XmlLoader
{

public:

    XmlLoader(ProjectBase& Base);
    bool load (QString adress);

private:

    QDomDocument RoadBase;
    ProjectBase& base;
    bool ParceBase();
    bool ParceProp(QDomElement& Prop);
    bool ParceCut(QDomElement& RBase);
    bool ParceConstr(QDomElement& RBase);
    bool ParceConstUnit(QDomElement& unit);
    QVector<UnitConst> ParcePie(QDomElement& pie);
    QVector<Element> ParceVectorElement(QDomElement& unit);


};

void debugElement(const QDomElement& el);
#endif // XMLLOADER_H
