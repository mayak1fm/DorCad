#ifndef DORCAD_TESTS_H
#define DORCAD_TESTS_H

#include <QObject>
#include <QTest>
#include"Element.h"
#include"UnitBase.h"
#include"XmlSaver.h"
#include "XmlLoader.h"
#include <QTextStream>
#include"ProjectBase.h"


QTextStream& operator <<(QTextStream& stream,const QVector<Element>& el);

QTextStream& operator <<(QTextStream& stream,Element& el);

QDebug& operator <<(QDebug& stream,const Element& el);

class DorCad_Tests: public QObject
{
    Q_OBJECT
public:
    explicit DorCad_Tests(QObject *parent = 0);
private:
QMap<double,UnitBase> expected_base;
QStringList axis;
ProjectBase base;

private slots:
    void math_element();
    void MathVectorElement();
    void MathUnitBaseElement();
    void AddAxis();
    void AddElementsLeft();
    void AddElementsRight();
    void AddTwoElements();

    void AddRangeElemnts();
    void AddUniquePkElemnts();
    void XMLLOADER();
//    void AddUniquePkElemntsBouth();
//    void AddTwoUniquePkElemntsLeft();
//    void AddTwoUniquePkElemntsRight();
//    void AddTwoUniquePkElemntsBouth();
//    void AddThreeUniquePkElemntsLeft();
//    void AddThreeUniquePkElemntsRight();
//    void AddThreeUniquePkElemntsBouth();
//    void AddRangePkElemntsLeft();
//    void AddRangePkElemntsRight();
//    void AddRangePkElemntsBouth();
//    void AddTwoRangePkElemntsLeft();
//    void AddTwoRangePkElemntsRight();
//    void AddTwoRangePkElemntsBouth();
//    void AddThreeRangePkElemntsLeft();
//    void AddThreeRangePkElemntsRight();
//    void AddThreeRangePkElemntsBouth();

};

#endif // DORCAD_TESTS_H
