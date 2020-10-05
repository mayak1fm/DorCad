#include "ProjectBase.h"
#include "dorcad_tests.h"

ProjectBase::ProjectBase()
{
    DateCreation= QDateTime::currentDateTime();
   // qDebug()<<DateCreation.toString("dd.MM.yyyy,hh:mm");
    DateChange=QDateTime::currentDateTime();
   // qDebug()<<QDateTime::fromString(DateCreation.toString("dd.MM.yyyy,hh:mm"),"dd.MM.yyyy,hh:mm");

}
void ProjectBase::SetName(const QString &name){
    Name=name;
}

void ProjectBase::setDataCreation(const QDateTime &data)
{
    if(data.isValid()){
        DateCreation=data;

    }
}

void ProjectBase::setDataChange(const QDateTime &data)
{
    if(data.isValid()){
        DateChange=data;
    }
}

void ProjectBase::setCountBorder(int i)
{
    count_border=i;
}
bool ProjectBase::AddAxis(QStringList& axis){
    if(axis.empty()){
        return false;
    }
    for (auto& i:axis) {
         QStringList line=i.split(',');
         if(line.size()!=2){
            return false;
         }
          Base[line.at(0).toDouble()]=UnitBase(line.at(1).toDouble());
        }
      return true;
}

//____________________________________________________________
bool ProjectBase::AddElements( QStringList& element_list,TypeElement el){


            if(element_list.size()<=1){
               return false;
            }


            auto lhs=element_list.begin();





            while(lhs!=element_list.end()){
                if(lhs->isEmpty()){return false;}
                QStringList lhs_line=lhs->split(',');
                if(lhs_line.at(1).toDouble()==0||lhs_line.size()!=3){return false;}
                insert_new_pk(lhs_line.at(0).toDouble());
                lhs++;
            }

            lhs=element_list.begin();
            QStringList lhs_line=lhs->split(',');


            Base[lhs_line.at(0).toDouble()].AddElement(lhs_line.at(1).toDouble(),lhs_line.at(2).toDouble(),el);

            auto rhs=std::next(lhs);

                while(rhs!=element_list.end()){

                    QStringList lhs_line=lhs->split(',');
                    QStringList rhs_line=rhs->split(',');

                    auto& iter_L=Base[lhs_line.at(0).toDouble()];
                    auto& iter_R=Base[rhs_line.at(0).toDouble()];

                    iter_R.AddElement(rhs_line.at(1).toDouble(),rhs_line.at(2).toDouble(),el);

                    if(!iter_L.isMarked()){
                        iter_L.setMark(marked(lhs_line.at(0).toDouble()));
                    }
                    if(!iter_R.isMarked()){
                        iter_R.setMark(marked(rhs_line.at(0).toDouble()));
                    }
                    auto FirstIt=Base.lowerBound(lhs_line.at(0).toDouble());
                    auto LastIt=Base.lowerBound(rhs_line.at(0).toDouble());

                    lhs_line.at(1).toDouble()<0 ? parce(FirstIt,LastIt,el,LEFT) : parce(FirstIt,LastIt,el,RIGHT);
                    lhs++;
                    rhs++;
                      }
   return true;
}
//____________________________________________________________________

void ProjectBase::AddConstruct(QString &name,QVector<UnitConst>&p){

    Construct c;
    c.Name=name;
    c.pie=p;
    BaseConstruct[name]=c;


}

void ProjectBase::AddCut(double pk, UnitBase &unit)
{
    Base[pk]=unit;
}
//______________________________________________________________________

QMap<double,UnitBase>& ProjectBase::GetBase(){
    return Base;
}

const QMap<double, UnitBase> &ProjectBase::GetBase() const
{
    return Base;
}

const QMap<QString, Construct> ProjectBase::GetConstructBase() const
{
    return BaseConstruct;
}
int ProjectBase::size(){
    return Base.size()+count_border;
}
QPair<int,int> ProjectBase::MaxWide(){


    auto i=std::max_element(Base.begin(),Base.end(),[](UnitBase & lhs, UnitBase & rhs){
        return (lhs.column_count().first+lhs.column_count().second)<
               (rhs.column_count().first+rhs.column_count().second);});
    auto pair = i.value().column_count();
    return pair;

}

UnitBase ProjectBase::GetCut(double pk){

    if(Base.isEmpty()){
        return UnitBase();
    }
    auto iRHS=Base.lowerBound(pk);
        if(iRHS.key()==pk) {
            return iRHS.value();
        }


        auto iLHS=iRHS;
        if (iRHS!=Base.begin()){
            iLHS=std::prev(iRHS);
            return interpolation(pk,iLHS.key(),iRHS.key(),iLHS.value(),iRHS.value());

        }

        else
            return iRHS.value();
}

const QString ProjectBase::GiveName () const
{
    return Name;
}

const QDateTime ProjectBase::GiveDateCretion() const
{
    return DateCreation;
}

const QDateTime ProjectBase::GiveDateChange() const
{
    return DateChange;
}

 int ProjectBase::GiveCountBorder() const
{
     return  count_border;
 }

 void ProjectBase::SetConstructive(double Pk, QString NameConstr, TypeElement type,side Side, int lane)
 {
    QVector<Element>& left=GetCut(Pk).GetLeftElements();
    QVector<Element>& right=GetCut(Pk).GetRightElements();
    QVector<Element>& leftb=GetCut(Pk).GetBorderLeftElements();
    QVector<Element>& rightb=GetCut(Pk).GetBorderRightElements();

    if (lane==1000){
        for (auto& i:left){
            if(i.type==type){
                i.Constr=NameConstr;
            }
        }
        for(auto& i:right){
            if(i.type==type){
                i.Constr=NameConstr;
            }
        }
    }

    else {
        switch (Side) {
        case LEFT:SetConstructElement(left,NameConstr,type,lane);
            break;
        case RIGHT:SetConstructElement(right,NameConstr,type,lane);
            break;
        case Rborder:SetConstructElement(rightb,NameConstr,type,lane);
            break;
        case Lborder:SetConstructElement(leftb,NameConstr,type,lane);
            break;
        }
    }
 }

 void ProjectBase::SetConstructElement(QVector<Element> &sidevector, QString &name, TypeElement type, int lane){
    if(sidevector.size()>=std::abs(lane)){

        if(sidevector[lane].type==type){
            sidevector[lane].Constr=name;
        }
        else{
            (new QErrorMessage())->showMessage("SetConstructElement: types is not equal");
            qDebug()<<"SetConstructElement: types is not equal";
        }
    }
    else {
        (new QErrorMessage())->showMessage("SetConstructElement: out of range");
        qDebug()<<"SetConstructElement: out of range";
    }
 }


bool ProjectBase::is_empty(){return Base.isEmpty();}

double ProjectBase::marked(double pk){
    auto iter_pair=Base.equal_range(pk);
    if(iter_pair.first!=Base.begin()||iter_pair.second!=Base.end()){
        double lhs_mark=std::prev(iter_pair.first).value().GetMark();
        double rhs_mark=iter_pair.second.value().GetMark();
        double lhs_pk=std::prev(iter_pair.first).key();
        double rhs_pk=iter_pair.second.key();
        double r = interpolation(pk,lhs_pk,rhs_pk,lhs_mark,rhs_mark);
        qDebug()<<this<<"marked"<<"return- "<<r<< "for pk-"<<pk;
        return r;
    }
    else{
        qDebug()<<this<<"marked"<<"return- "<<0<< "for pk-"<<pk<<"out_of_rainge";
        return 0;
    }
}

void ProjectBase::insert_new_pk(double pk)
{
    if(Base.count(pk)!=0){return;}

    auto& unit=Base[pk];
    auto iter=Base.lowerBound(pk);

    if (Base.lastKey()==iter.key()||Base.begin()==iter){return;}

    auto lhs=std::prev(iter);
    auto rhs=std::next(iter);

    unit=interpolation(pk,lhs.key(),rhs.key(),lhs.value(),rhs.value());

}

QMap <double,UnitBase>::iterator ProjectBase::begin(){
    return Base.begin();
}
QMap <double,UnitBase>::iterator ProjectBase::end(){
    return  Base.end();
}
QMap <double,UnitBase>::iterator ProjectBase::lowerBound(double Pk){
    return Base.lowerBound(Pk);
}






void ProjectBase::parce( QMap<double,UnitBase>::iterator &FirstIt,
                                   QMap<double,UnitBase>::iterator &LastIt,const TypeElement& el,side s){

    auto iter=std::next(FirstIt);
    if(iter==LastIt||FirstIt==LastIt){
        return;}
    double lhs_pk=FirstIt.key();
    double rhs_pk=LastIt.key();
    while (iter!=LastIt) {
        double pk=iter.key();
        if(s==LEFT){
        Element lhs_el=FirstIt.value().last(LEFT);
        Element rhs_el=LastIt.value().last(LEFT);
        Element result=interpolation(pk,lhs_pk,rhs_pk,lhs_el,rhs_el);
        iter.value().AddElement(result.width,result.grad,result.type);

        }
        if(s==RIGHT){
        Element lhs_el=FirstIt.value().last(RIGHT);
        Element rhs_el=LastIt.value().last(RIGHT);
        Element result=interpolation(pk,lhs_pk,rhs_pk,lhs_el,rhs_el);
        iter.value().AddElement(result.width,result.grad,result.type);
        }

        iter++;
    }

}
