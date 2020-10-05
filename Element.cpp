#include "Element.h"

bool operator !=(const Construct& lhs,const Construct& rhs){
    if(lhs.Name!=rhs.Name){return true;}
    return false;
 }

bool operator ==(const Element& lhs,const Element& rhs){
    if(lhs.grad!=rhs.grad){return false;}
    if(lhs.width!=rhs.width){return false;}
    if(lhs.type!=rhs.type){return false;}
    if(lhs.Constr!=rhs.Constr){return false;}
    return true;
}

Element operator *(const Element& lhs,const Element& rhs){
    return Element(lhs.width*rhs.width,lhs.grad*rhs.grad,lhs.type,lhs.Constr,lhs.border);
}

Element operator + (const Element& lhs,const Element& rhs){
    return Element(lhs.width+rhs.width,lhs.grad+rhs.grad,lhs.type,lhs.Constr,lhs.border);
}

Element operator - (const Element& lhs,const Element& rhs){
    return Element(lhs.width-rhs.width,lhs.grad-rhs.grad,lhs.type,lhs.Constr,lhs.border);
}

Element operator / (const Element& lhs,const Element& rhs){

    if(rhs.grad!=0&&rhs.width!=0)
        {
            return Element(lhs.width/rhs.width,lhs.grad/rhs.grad,lhs.type,lhs.Constr,lhs.border);
        }
    else
        {
            return Element(lhs.width,lhs.grad,lhs.type,lhs.Constr,lhs.border);
        }
}

Element operator / (const Element& lhs,double pk){
    if(pk!=0)
        {
            return Element(lhs.width/pk,lhs.grad/pk,lhs.type,lhs.Constr,lhs.border);
        }
    else
        {
            return Element(lhs.width,lhs.grad,lhs.type,lhs.Constr,lhs.border);
        }
}
Element operator * (const Element& lhs,double pk){
            return Element(lhs.width*pk,lhs.grad*pk,lhs.type,lhs.Constr,lhs.border);

}


Element::Element()
{
    border=false;
}

Element::Element(double w, double g, TypeElement el): type(el),width(w),grad(g){
    border=false;
}
Element::Element(double w, double g,TypeElement el,bool is_border): type(el),width(w),grad(g),border(is_border)
{

}

Element::Element(double w, double g, TypeElement el, QString c, bool is_border):type(el),width(w),grad(g),Constr(c),border(is_border)
{

}



QVector<Element> VectorElementMath (const QVector<Element> &lhs, const QVector<Element> &rhs, TypeMathSymbols s)
{

    if(lhs.isEmpty()||rhs.isEmpty()){  //если один из векторов пустой то вернуть пустой вектор;
        return std::min(lhs,rhs,[](const QVector<Element>& l,const QVector<Element>& r){return l.size()<r.size();});
        }
    if(lhs.size()<=rhs.size())  {
        return VEM(lhs,rhs,s,false);
    }
        return VEM(rhs,lhs,s,true);

}


QVector<Element> VEM (const QVector<Element> &minV, const QVector<Element> &maxV, TypeMathSymbols s,bool isReverse){
    // Функция переберает значения минимального вектора i и проводит математические операции со значениями максимального вектора.
    QVector<Element> result;
    auto itMin=minV.begin();
    auto itMax=maxV.begin();
    while (itMin!=minV.end()) {
        if(itMax==maxV.end()){
            return result;
        }
        if(itMin->type==itMax->type){    // Если типы равны запускает математическую операцию


            !isReverse ? result.push_back(ElementMath(*itMin,*itMax,s)): // проверка на перевернутую функцию
                        result.push_back(ElementMath(*itMax,*itMin,s));// если правый вектор меньше тогда надо перевернуть обратно значения
            itMin++;
            itMax++;
        }
        else{
            if  (itMin->border){ itMin++;}
            if  (itMax->border){ itMax++;}// Если типы не  равны и помеченны как граница пропускает значение второго вектора для поиска нужного типа
            if  (!itMax->border ||!itMin->border) {
                !isReverse ? result.push_back(ElementMath(Element(0,0,itMax->type,itMax->border), *itMax,s)):
                            result.push_back(ElementMath(*itMax,Element(0,0,itMax->type,itMax->border),s));
                            // Если границы нет то выполняет операцию с нулевыми значениями при НЕсовподении типов
                itMax++;
            }
        }
    }

    while (itMax!=maxV.end()) { // итерируется по остаткам второго вектора и интерполирует на ноль если нет метки границы
        if(itMin->border||itMax->border){ itMax++;}
        else{
            !isReverse ? result.push_back(ElementMath(Element(0,0,itMax->type,itMax->border), *itMax,s)):
                        result.push_back(ElementMath(*itMax,Element(0,0,itMax->type,itMax->border),s));
            itMax++;
        }
    }
    return result;
}





Element ElementMath(const Element &lhs, const Element &rhs, TypeMathSymbols s)
{
    switch (s) {
        case division: return lhs/rhs;
        case multiplication: return lhs*rhs;
        case addition: return lhs+rhs;
        case substraction: return lhs-rhs;
    }
}





