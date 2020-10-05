#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QTableWidget>
#include  <QWidget>
#include "ProjectBase.h"
#include "Element.h"
#include "dormath.h"

class Table_view:   public QTableWidget
{
    Q_OBJECT

public:
    explicit Table_view(ProjectBase&  Base, QWidget *pwgt =0);

private:

    int row;
    QPair<int,int> column;
    const int AxisAndMark=2;
    ProjectBase& base;

    QString ElemFormat(const Element& element);

    void printPK(const QMap<double,UnitBase>::iterator& iter, const int& i);
    void printMarkAxis(const QMap<double,UnitBase>::iterator& iter, const int& i);
    void print_LAndR(const QMap<double,UnitBase>::iterator& iter, const int& i);


public:
    void BildTable();


};

#endif // TABLE_VIEW_H
