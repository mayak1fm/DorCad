#pragma once
#include <cmath>
#include <QDebug>
template <typename T,typename elem>
elem interpolation( T PK,  T lhs_pk, T rhs_pk, elem lhs, elem rhs){
    return lhs-((lhs-rhs)/(lhs_pk-rhs_pk)*(lhs_pk-PK));

}
QString PkFormat(double pk);
