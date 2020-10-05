#ifndef XMLSAVER_H
#define XMLSAVER_H

#include "ProjectBase.h"
#include <QtXml>
#include <QDate>
#include "GlobalConstant.h"


class XmlSaver
{
public:

    explicit XmlSaver(const ProjectBase& Base);
    bool save(QString adress);



private:

    QDomDocument ProjectDoc;
    const ProjectBase& baseP;

    void savebase();
    void saveConstructBase(QDomElement& ConstructiveBase);
    void saveconstructPie(QDomElement& pie,const QVector<UnitConst>& vpie);
    void saveUnitBase(const UnitBase& unitb,QDomElement& unitElement);
    void saveSide(const QVector<Element>& v,QDomElement& unitElement,side s);
    void saveElement(const Element& el,QDomElement& SideElement);




    template<typename name,typename value>
    QDomElement MakeElement (name tag,value text)
    {

        QDomElement element=ProjectDoc.createElement(tag);
        QDomText Text=ProjectDoc.createTextNode(text);
        element.appendChild(Text);
        return element;
    }


};

#endif // XMLSAVER_H
