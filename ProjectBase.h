#ifndef PROJECTBASE_H
#define PROJECTBASE_H

#include <QObject>
#include <QWidget>
#include <QtCore>
#include <QErrorMessage>
#include "UnitBase.h"
#include "Element.h"
#include "dormath.h"
class ProjectBase
{
public:
    ProjectBase();
void SetName(const QString& name);
void setDataCreation(const QDateTime& data);
void setDataChange(const QDateTime& data);
void setCountBorder(int i);
bool AddAxis(QStringList& axis);
bool AddElements(QStringList& element_list,TypeElement el);
void AddConstruct(QString& name,QVector<UnitConst>& p);
void AddCut(double pk,UnitBase& unit);
bool is_empty();
int  size();
QMap<double,UnitBase>& GetBase();
const QMap<double,UnitBase>& GetBase() const;
const QMap<QString,Construct> GetConstructBase()const;
QPair<int, int> MaxWide();
UnitBase GetCut(double pk);
const QString GiveName () const;
const QDateTime GiveDateCretion() const;
const QDateTime GiveDateChange() const;
int GiveCountBorder()const;
void SetConstructive(double Pk,QString NameConstr,TypeElement type,side Side=LEFT, int lane=1000);
void insert_new_pk(double pk);
QMap <double,UnitBase>::iterator begin();
QMap <double,UnitBase>::iterator end();
QMap <double,UnitBase>::iterator lowerBound(double Pk);


private:
    QMap<double,UnitBase> Base;    
    QMap<QString,Construct> BaseConstruct;
    QString Name;
    QDateTime DateCreation;
    QDateTime DateChange;
    int count_border=0;
    double marked(double pk);

    void SetConstructElement(QVector<Element>& sidevector, QString& name,TypeElement type,int lane);
    void parce( QMap<double,UnitBase>::iterator &FirstIt,
                                       QMap<double,UnitBase>::iterator &LastIt,const TypeElement& el,side s);


};

#endif // PROJECTBASE_H
