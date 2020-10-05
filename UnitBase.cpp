#include "UnitBase.h"

QVector<Element> operator - (const QVector<Element>& lhs,const QVector<Element>& rhs){
    return VectorElementMath(lhs,rhs,substraction);
}

QVector<Element> operator * (const QVector<Element>& lhs,const QVector<Element>& rhs){
    return VectorElementMath(lhs,rhs,multiplication);
}

QVector<Element> operator / (const QVector<Element>& lhs,const QVector<Element>& rhs){
    return VectorElementMath(lhs,rhs,division);
}
QVector<Element> operator / (const QVector<Element>& lhs,double d){
    QVector<Element> result;
    for(const auto& i:lhs){
        result.push_back(i/d);
    }
    return result;
}
QVector<Element> operator * (const QVector<Element>& lhs,double d){
    QVector<Element> result;
    for(const auto& i:lhs){
        result.push_back(i*d);
    }
    return result;
}

QVector<Element> operator + (const QVectorELement& lhs,const QVectorELement& rhs){

    return VectorElementMath(lhs.vector,rhs.vector,addition);
}

QVector<Element> operator +(const QVectorELement &lhs, const QVector<Element> &rhs)
{
    return VectorElementMath(lhs.vector,rhs,addition);
}

QVector<Element> operator -(const QVectorELement &lhs, const QVector<Element> &rhs)
{
    return VectorElementMath(lhs.vector,rhs,substraction);
}

QVector<Element> operator /(const QVectorELement &lhs, const QVector<Element> &rhs)
{
    return VectorElementMath(lhs.vector,rhs,division);
}

QVector<Element> operator *(const QVectorELement &lhs, const QVector<Element> &rhs)
{
    return VectorElementMath(lhs.vector,rhs,multiplication);
}

QVector<Element> operator +(const QVector<Element> &lhs, const QVectorELement &rhs)
{
    return VectorElementMath(lhs,rhs.vector,addition);
}

QVector<Element> operator -(const QVector<Element> &lhs, const QVectorELement &rhs)
{
    return VectorElementMath(lhs,rhs.vector,substraction);
}

QVector<Element> operator /(const QVector<Element> &lhs, const QVectorELement &rhs)
{
    return VectorElementMath(lhs,rhs.vector,division);
}

QVector<Element> operator *(const QVector<Element> &lhs, const QVectorELement &rhs)
{
    return VectorElementMath(lhs,rhs.vector,multiplication);
}
bool operator ==(const UnitBase& lhs,const UnitBase& rhs){

    r_base l=lhs.GetUnitBase();
    r_base r=rhs.GetUnitBase();
    if(l.HMark!=r.HMark){return false;}
    if(l.isBor!=r.isBor){return false;}
    if(l.l!=r.l){return false;}
    if(l.r!=r.r){return false;}
    if(l.lBorder!=r.lBorder){return false;}
    if(l.rBorder!=r.rBorder){return false;}
    return true;
}

UnitBase operator * (const UnitBase& lhs,const UnitBase& rhs){
    return UnitBase(lhs.GetMark()*rhs.GetMark(),
                    lhs.GetLeftElements()*rhs.GetLeftElements(),
                    lhs.GetRightElements()*rhs.GetRightElements(),
                    false,QVector<Element>{},QVector<Element>{},
                    (lhs.isMarked()||rhs.isMarked()));
}

UnitBase operator / (const UnitBase& lhs,const UnitBase& rhs){
    return UnitBase(lhs.GetMark()/rhs.GetMark(),
                    lhs.GetLeftElements()/ rhs.GetLeftElements(),
                    lhs.GetRightElements()/rhs.GetRightElements(),
                    false,QVector<Element>{},QVector<Element>{},
                    (lhs.isMarked()||rhs.isMarked()));
}


UnitBase operator - (const UnitBase& lhs,const UnitBase& rhs){
    return UnitBase(lhs.GetMark()-rhs.GetMark(),
                    lhs.GetLeftElements() - rhs.GetLeftElements(),
                    lhs.GetRightElements()-rhs.GetRightElements(),
                    false,QVector<Element>{},QVector<Element>{},
                    (lhs.isMarked()||rhs.isMarked()));
}
UnitBase operator + (const UnitBase& lhs,const UnitBase& rhs){
    QVectorELement ll;
    QVectorELement lr;
    QVectorELement rl;
    QVectorELement rr;
    ll.vector=lhs.GetLeftElements();
    lr.vector=lhs.GetRightElements();

    rl.vector=rhs.GetLeftElements();
    rr.vector=rhs.GetRightElements();

    return UnitBase(lhs.GetMark()+rhs.GetMark(),
                    ll + rl,lr + rr,
                    false,QVector<Element>{},QVector<Element>{},
                    (lhs.isMarked()||rhs.isMarked()));
}


UnitBase operator / (const UnitBase& lhs,double d){
    return UnitBase(lhs.GetMark()/d,
                    lhs.GetLeftElements()/ d,
                    lhs.GetRightElements()/d,
                    false,QVector<Element>{},QVector<Element>{},
                    lhs.isMarked());

}
UnitBase operator * (const UnitBase& lhs,double d){
    return UnitBase(lhs.GetMark()*d,
                    lhs.GetLeftElements()* d,
                    lhs.GetRightElements()*d,
                    false,QVector<Element>{},QVector<Element>{},
                    lhs.isMarked());

}

r_base::r_base (double hMark, QVector <Element> L, QVector <Element> R, bool ISBor,
                QVector <Element> LB, QVector <Element> RB):HMark(hMark),
                         l(L),r(R),isBor(ISBor),lBorder(LB),rBorder(R){};




UnitBase::UnitBase():isMark(false),isEmpty(true)
{

}

UnitBase::UnitBase(double mark):HeightMark(mark),isBorder(false),isMark(true),isEmpty(false)
{

}
UnitBase::UnitBase(double HMark, QVector <Element> l, QVector <Element> r,
    bool isborder, QVector <Element> lBorder,QVector <Element> rBorder,bool ismark):
                                                                HeightMark(HMark),
                                                                left(l),
                                                                right(r),
                                                                isBorder(isborder),
                                                                leftBorder(lBorder),
                                                                rightBorder(rBorder),
                                                                isMark(ismark),
                                                                isEmpty(false){}
double UnitBase::GetMark()const{
    return HeightMark;
}

const QVector<Element> &UnitBase::GetLeftElements() const
{
    return left;
}

const QVector<Element> &UnitBase::GetRightElements() const
{
    return right;
}

QVector<Element> &UnitBase::GetLeftElements()
{
    return  left;
}
QVector<Element> &UnitBase::GetRightElements()
{
    return  right;
}

const QVector<Element> &UnitBase::GetBorderLeftElements() const
{
    return leftBorder;
}

const QVector<Element> &UnitBase::GetBorderRightElements() const
{
    return rightBorder;
}

QVector<Element> &UnitBase::GetBorderLeftElements()
{
    return leftBorder;
}
QVector<Element> &UnitBase::GetBorderRightElements()
{
    return rightBorder;
}

bool UnitBase::is_Border() const
{
    return isBorder;
}

void UnitBase::AddElement(double width, double grad,TypeElement el){
    Element a(width,grad,el);
    if(width>0){
        right.push_back(a);

    }
    else if(width<0) {
         left.push_back(a);
    }
    else{
        qWarning("add element whith zero widht");
    }

}
QPair<int,int> UnitBase::column_count()const{
    return QPair<int,int>{std::max(left.size(),leftBorder.size()),
                std::max(right.size(),rightBorder.size())};
}



    r_base UnitBase::GetUnitBase()const{
    r_base UBase(HeightMark,left,right,isBorder,leftBorder,rightBorder);
    return UBase;
}
    bool UnitBase::isMarked() const{
        return isMark;
    }

    bool UnitBase::is_empty() const
    {
        return isEmpty;
    }
    bool UnitBase::setMark(double mark){
        if (isMark){
            return false;
        }
        else{
            HeightMark=mark;
            return true;
        }
    }
    Element UnitBase::last( const side& s)const{
        switch (s) {
        case LEFT: return left.last();
            break;
        case RIGHT: return right.last();
        }
    }



