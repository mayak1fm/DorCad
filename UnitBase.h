#ifndef UNITBASE_H
#define UNITBASE_H

#include <QObject>
#include "Element.h"

struct QVectorELement{

    QVector<Element> vector;
};



enum side
{
  LEFT=0,
  RIGHT,
  Rborder,
  Lborder
};

struct r_base{
    r_base (double hMark, QVector <Element> L, QVector <Element> R, bool ISBor,
           QVector <Element> LB, QVector <Element> RB);
     double HMark;
     QVector <Element> l;
     QVector <Element> r;
     bool isBor;
     QVector <Element> lBorder;
     QVector <Element> rBorder;
};


class UnitBase
{
private:
    double HeightMark;
    QVector <Element> left;
    QVector <Element> right;
    bool isBorder;
    QVector <Element> leftBorder;
    QVector <Element> rightBorder;
    bool isMark;
    bool isEmpty;

public:    
    UnitBase();
    UnitBase(double mark);
    UnitBase(double HMark, QVector <Element> l, QVector <Element> r,
             bool isborder, QVector <Element> lBorder,QVector <Element> rBorder,bool ismark);
    void AddElement(double width,double grad,TypeElement el);
    void ChangeElement();
    void DelElement();
    r_base GetUnitBase()const;
    double GetMark ()const;
    const QVector <Element>& GetLeftElements ()const;
    const QVector <Element>& GetRightElements ()const;
    QVector <Element>& GetLeftElements ();
    QVector <Element>& GetRightElements ();

    const QVector <Element>& GetBorderLeftElements ()const;
    const QVector <Element>& GetBorderRightElements ()const;
    QVector <Element>& GetBorderLeftElements ();
    QVector <Element>& GetBorderRightElements ();

    bool is_Border() const;
    bool setMark(double mark);
    bool isMarked() const;
    bool is_empty()const;
    Element last(const side& s)const;
    QPair<int,int> column_count()const;

};



inline QTextStream& operator <<(QTextStream& out,const UnitBase base);

QVector<Element> operator - (const QVector<Element>& lhs,const QVector<Element>& rhs);

QVector<Element> operator * (const QVector<Element>& lhs,const QVector<Element>& rhs);

QVector<Element> operator / (const QVector<Element>& lhs,const QVector<Element>& rhs);
QVector<Element> operator / (const QVector<Element>& lhs,double d);
QVector<Element> operator * (const QVector<Element>& lhs,double d);

QVector<Element> operator + (const QVectorELement& lhs,const QVectorELement& rhs);


QVector<Element> operator +(const QVectorELement &lhs, const QVector<Element> &rhs);

QVector<Element> operator -(const QVectorELement &lhs, const QVector<Element> &rhs);

QVector<Element> operator /(const QVectorELement &lhs, const QVector<Element> &rhs);

QVector<Element> operator *(const QVectorELement &lhs, const QVector<Element> &rhs);


QVector<Element> operator +(const QVector<Element> &lhs, const QVectorELement &rhs);

QVector<Element> operator -(const QVector<Element> &lhs, const QVectorELement &rhs);

QVector<Element> operator /(const QVector<Element> &lhs, const QVectorELement &rhs);

QVector<Element> operator *(const QVector<Element> &lhs, const QVectorELement &rhs);


bool operator ==(const UnitBase& lhs,const UnitBase& rhs);
UnitBase operator * (const UnitBase& lhs,const UnitBase& rhs);
UnitBase operator / (const UnitBase& lhs,const UnitBase& rhs);
UnitBase operator - (const UnitBase& lhs,const UnitBase& rhs);
UnitBase operator + (const UnitBase& lhs,const UnitBase& rhs);
UnitBase operator / (const UnitBase& lhs,double d);
UnitBase operator * (const UnitBase& lhs,double d);

#endif // UNITBASE_H
