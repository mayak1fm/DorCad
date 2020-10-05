
#include"dormath.h"

QString PkFormat(double pk){
    double meters=std::fmod(pk,100);
    double piket=(pk-meters)/100;
    QString r="ПК "+QString::number(piket)+'+'+QString::number(meters, 'f',2);
    return r;
}
