#ifndef ELEMENT_H
#define ELEMENT_H

#include<QtCore>

enum TypeElement{
  lane=0,
  roadside,
  slope,
  ditch,
  asix
};
enum TypeMathSymbols{
  division=0,
  multiplication,
  substraction,
  addition
};

struct UnitConst{
    QString Name;
    double layerthin;
};

struct Construct{
    QString Name;
    QVector<UnitConst>pie;
};

class Element {
public:
TypeElement type;
double width;
double grad;
QString Constr;
bool border;
Element();
Element(double w, double g,TypeElement el);
Element(double w, double g,TypeElement el,bool is_border);
Element(double w, double g,TypeElement el, QString c, bool is_border);
};


QVector<Element> VEM (const QVector<Element> &minV, const QVector<Element> &maxV, TypeMathSymbols s,bool isReverse);

Element ElementMath(const Element& lhs,const Element& rhs,TypeMathSymbols s);

QVector<Element> VectorElementMath(const QVector<Element> &lhs, const QVector<Element> &rhs, TypeMathSymbols s);


bool operator !=(const Construct& lhs,const Construct& rhs);

bool operator ==(const Element& lhs,const Element& rhs);

Element operator *(const Element& lhs,const Element& rhs);

Element operator + (const Element& lhs,const Element& rhs);

Element operator - (const Element& lhs,const Element& rhs);

Element operator / (const Element& lhs,const Element& rhs);

Element operator / (const Element& lhs,double pk);

Element operator * (const Element& lhs,double pk);


#endif // ELEMENT_H
