#ifndef OBJECTWINDOW_H
#define OBJECTWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ProjectBase.h"
#include <QTableWidget>
#include "AddConst.h"
#include "AddAxis.h"
#include "AddElement.h"
#include "createnewobwindow.h"
#include "table_view.h"
#include <cmath>
#include "CutView.h"
#include "CutChoise.h"
#include "XmlSaver.h"


enum TypeTable{
  axis_t,
  element_t,
  construct_t
};

class ObjectWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectWindow(QWidget *pwgt =0);
    void Setname(QString& namebase);
private:
    ProjectBase base;
    QString namewindow;
    CutChoise* choiseCut=new CutChoise(base,this);
    CutView* viewCut=new CutView(base,this);
    QVBoxLayout* lay =new QVBoxLayout;
    QHBoxLayout* lay2 =new QHBoxLayout;
    Table_view* table=new Table_view(base,this);

public slots:
    void addConst();
    void addAxis ();
    void addElement();
    void setConst();
    void addConsttoBase(QPair<QString, QVector<UnitConst>> pair);
    void addAxistoBase(QString& str);
    void addElementtoBase(QString& str,TypeElement t);
    void save();
    void UpdateAllView();
    ProjectBase& open();



signals:

};

#endif // OBJECTWINDOW_H
