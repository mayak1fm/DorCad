#ifndef PLANVIEW_H
#define PLANVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include "ProjectBase.h"

class PlanView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit PlanView(ProjectBase& Base,QWidget*pwgt=0);
    void EnabelWindow(){

    }
private:
    ProjectBase& base;
};

#endif // PLANVIEW_H
