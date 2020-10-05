#include "dorcad_tests.h"


QTextStream& operator <<(QTextStream& stream,const QVector<Element>& el){
    for (const auto& i:el){
        stream<<i.width<<'|';
        stream<<i.grad<<'|';
        stream<<i.type<<'|';
    }
    return stream;
}

QTextStream& operator <<(QTextStream& stream,Element& el){
    stream<<el.width<<'|'<<el.grad<<'|'<<el.type;
    return stream;
}

QDebug& operator <<(QDebug& stream,const Element& el){
    stream<<el.width<<'|'<<el.grad<<'|'<<el.type;
    return stream;
}




DorCad_Tests::DorCad_Tests(QObject *parent): QObject(parent)
{

    axis.push_back("0,100");
    axis.push_back("10,200");
    axis.push_back("20,300");
    axis.push_back("30,400");
    axis.push_back("40,500");
}

void DorCad_Tests::math_element()
{
    Element lhs(10,10,lane);
    Element rhs(2,2,lane);
    Element result=lhs-rhs;
    //qDebug() <<result.width<<"|"<<result.grad;
    QCOMPARE(result,Element (8,8,lane));

    result=lhs-rhs;
    //qDebug() <<result.width<<"|"<<result.grad;
    QCOMPARE(result,Element (8,8,lane));
    result=lhs-rhs+rhs;
    //qDebug() <<result.width<<"|"<<result.grad;
    QCOMPARE(result,Element (10,10,lane));
    result=(lhs-rhs+rhs)/2;
    //qDebug() <<result.width<<"|"<<result.grad;
    QCOMPARE(result,Element (5,5,lane));

}

void DorCad_Tests::MathVectorElement()

{
    QVectorELement lhs;
    QVectorELement rhs;
    lhs.vector={Element(100,10,lane),Element(-100,10,lane)};
    rhs.vector={Element(50,2,lane),Element(-50,2,lane)};
    QVector<Element>result=lhs+rhs;
    //qDebug()<<result;
    QVector<Element> t {Element(150,12,lane),Element(-150,12,lane)};
    QCOMPARE(result,t);
    result=(lhs-rhs.vector+rhs)/2;
    //qDebug()<<result;
    t={Element(50,5,lane),Element(-50,5,lane)};
    QCOMPARE(result,t);
}

void DorCad_Tests ::MathUnitBaseElement()
{
    UnitBase lhs (100,QVector<Element>{Element(100,10,lane),Element(100,10,lane)},
                      QVector<Element>{Element(100,10,lane),Element(100,10,lane)},
                      false,QVector<Element>{},QVector<Element>{},true);

    UnitBase rhs (50,QVector<Element>{Element(50,5,lane),Element(50,5,lane)},
                 QVector<Element>{Element(50,5,lane),Element(50,5,lane)},
                 false,QVector<Element>{},QVector<Element>{},true);
    UnitBase need (50,QVector<Element>{Element(50,5,lane),Element(50,5,lane)},
                 QVector<Element>{Element(50,5,lane),Element(50,5,lane)},
                 false,QVector<Element>{},QVector<Element>{},true);


    UnitBase result=(lhs-rhs+rhs)/2;

//    qDebug()<<result.GetMark();
//    qDebug()<<result.GetLeftElements();
//    qDebug()<<result.GetRightElements();
    QCOMPARE(result,need);
}

void DorCad_Tests::AddAxis(){
   QStringList axis_empty;
   QCOMPARE(base.AddAxis(axis_empty),false);
   expected_base[0] =UnitBase(100);
   expected_base[10]=UnitBase(200);
   expected_base[20]=UnitBase(300);
   expected_base[30]=UnitBase(400);
   expected_base[40]=UnitBase(500);
   base.AddAxis(axis);
   QCOMPARE(base.GetBase(), expected_base);

}
void DorCad_Tests::AddElementsLeft(){
    QStringList left;
    QCOMPARE(base.AddElements(left,TypeElement::lane),false);
    QCOMPARE(base.GetBase(),expected_base);
    left.push_back("0,-3.75,-0.02");
    QCOMPARE(base.AddElements(left,TypeElement::lane),false);
    QCOMPARE(base.GetBase(),expected_base);

    left.clear();
    left.push_back("0,-100,10");
    left.push_back("10,-100,20");
    left.push_back("20,-200,30");
    left.push_back("30,-300,40");
    left.push_back("40,-400,50");

    QCOMPARE(base.AddElements(left,TypeElement::lane),true);

        QCOMPARE(base.GetBase()[00].GetMark(),100);
        QCOMPARE(base.GetBase()[10].GetMark(),200);
        QCOMPARE(base.GetBase()[20].GetMark(),300);
        QCOMPARE(base.GetBase()[30].GetMark(),400);
        QCOMPARE(base.GetBase()[40].GetMark(),500);

        QCOMPARE(base.GetBase()[00].GetLeftElements(),QVector<Element>{Element(-100,10,lane)});
        QCOMPARE(base.GetBase()[10].GetLeftElements(),QVector<Element>{Element(-100,20,lane)});
        QCOMPARE(base.GetBase()[20].GetLeftElements(),QVector<Element>{Element(-200,30,lane)});
        QCOMPARE(base.GetBase()[30].GetLeftElements(),QVector<Element>{Element(-300,40,lane)});
        QCOMPARE(base.GetBase()[40].GetLeftElements(),QVector<Element>{Element(-400,50,lane)});


        QCOMPARE(base.GetBase()[00].isMarked(),true);
        QCOMPARE(base.GetBase()[10].isMarked(),true);
        QCOMPARE(base.GetBase()[20].isMarked(),true);
        QCOMPARE(base.GetBase()[30].isMarked(),true);
        QCOMPARE(base.GetBase()[40].isMarked(),true);


}

void DorCad_Tests::AddElementsRight()
{
    QStringList right;
    QCOMPARE(base.AddElements(right,TypeElement::lane),false);

    right.push_back("0,3.75,-0.02");
    QCOMPARE(base.AddElements(right,TypeElement::lane),false);

    right.clear();
    right.push_back("0,100,10");
    right.push_back("10,100,20");
    right.push_back("20,200,30");
    right.push_back("30,300,40");
    right.push_back("40,400,50");

    QCOMPARE(base.AddElements(right,TypeElement::lane),true);

    QCOMPARE(base.GetBase()[00].GetMark(),100);
    QCOMPARE(base.GetBase()[10].GetMark(),200);
    QCOMPARE(base.GetBase()[20].GetMark(),300);
    QCOMPARE(base.GetBase()[30].GetMark(),400);
    QCOMPARE(base.GetBase()[40].GetMark(),500);

    QCOMPARE(base.GetBase()[00].GetLeftElements(),QVector<Element>{Element(-100,10,lane)});
    QCOMPARE(base.GetBase()[10].GetLeftElements(),QVector<Element>{Element(-100,20,lane)});
    QCOMPARE(base.GetBase()[20].GetLeftElements(),QVector<Element>{Element(-200,30,lane)});
    QCOMPARE(base.GetBase()[30].GetLeftElements(),QVector<Element>{Element(-300,40,lane)});
    QCOMPARE(base.GetBase()[40].GetLeftElements(),QVector<Element>{Element(-400,50,lane)});


    QCOMPARE(base.GetBase()[00].GetRightElements(),QVector<Element>{Element(100,10,lane)});
    QCOMPARE(base.GetBase()[10].GetRightElements(),QVector<Element>{Element(100,20,lane)});
    QCOMPARE(base.GetBase()[20].GetRightElements(),QVector<Element>{Element(200,30,lane)});
    QCOMPARE(base.GetBase()[30].GetRightElements(),QVector<Element>{Element(300,40,lane)});
    QCOMPARE(base.GetBase()[40].GetRightElements(),QVector<Element>{Element(400,50,lane)});


    QCOMPARE(base.GetBase()[00].isMarked(),true);
    QCOMPARE(base.GetBase()[10].isMarked(),true);
    QCOMPARE(base.GetBase()[20].isMarked(),true);
    QCOMPARE(base.GetBase()[30].isMarked(),true);
    QCOMPARE(base.GetBase()[40].isMarked(),true);


}

void DorCad_Tests::AddTwoElements()
{
    QStringList left;
    QStringList right;



    left.push_back("0,-1000,100");
    left.push_back("10,-1000,200");
    left.push_back("20,-2000,300");
    left.push_back("30,-3000,400");
    left.push_back("40,-4000,500");

    QCOMPARE(base.AddElements(left,TypeElement::lane),true);

    right.push_back("0,1000,100");
    right.push_back("10,1000,200");
    right.push_back("20,2000,300");
    right.push_back("30,3000,400");
    right.push_back("40,4000,500");

    QCOMPARE(base.AddElements(right,TypeElement::lane),true);

    QCOMPARE(base.GetBase()[00].GetMark(),100);
    QCOMPARE(base.GetBase()[10].GetMark(),200);
    QCOMPARE(base.GetBase()[20].GetMark(),300);
    QCOMPARE(base.GetBase()[30].GetMark(),400);
    QCOMPARE(base.GetBase()[40].GetMark(),500);


    QCOMPARE(base.GetBase()[00].GetLeftElements(),(QVector<Element>{Element(-100,10,lane),Element(-1000,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetLeftElements(),(QVector<Element>{Element(-100,20,lane),Element(-1000,200,lane)}));
    QCOMPARE(base.GetBase()[20].GetLeftElements(),(QVector<Element>{Element(-200,30,lane),Element(-2000,300,lane)}));
    QCOMPARE(base.GetBase()[30].GetLeftElements(),(QVector<Element>{Element(-300,40,lane),Element(-3000,400,lane)}));
    QCOMPARE(base.GetBase()[40].GetLeftElements(),(QVector<Element>{Element(-400,50,lane),Element(-4000,500,lane)}));


    QCOMPARE(base.GetBase()[00].GetRightElements(),(QVector<Element>{Element(100,10,lane),Element(1000,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetRightElements(),(QVector<Element>{Element(100,20,lane),Element(1000,200,lane)}));
    QCOMPARE(base.GetBase()[20].GetRightElements(),(QVector<Element>{Element(200,30,lane),Element(2000,300,lane)}));
    QCOMPARE(base.GetBase()[30].GetRightElements(),(QVector<Element>{Element(300,40,lane),Element(3000,400,lane)}));
    QCOMPARE(base.GetBase()[40].GetRightElements(),(QVector<Element>{Element(400,50,lane),Element(4000,500,lane)}));


    QCOMPARE(base.GetBase()[00].isMarked(),true);
    QCOMPARE(base.GetBase()[10].isMarked(),true);
    QCOMPARE(base.GetBase()[20].isMarked(),true);
    QCOMPARE(base.GetBase()[30].isMarked(),true);
    QCOMPARE(base.GetBase()[40].isMarked(),true);



}



void DorCad_Tests::AddRangeElemnts()
{
    QStringList left;
    QStringList right;



    left.push_back("0,-100,100");
    left.push_back("40,-100,500");

    QCOMPARE(base.AddElements(left,TypeElement::lane),true);

    right.push_back("0,100,100");;
    right.push_back("40,400,500");

    QCOMPARE(base.AddElements(right,TypeElement::lane),true);


    QCOMPARE(base.GetBase()[00].GetMark(),100);
    QCOMPARE(base.GetBase()[10].GetMark(),200);
    QCOMPARE(base.GetBase()[20].GetMark(),300);
    QCOMPARE(base.GetBase()[30].GetMark(),400);
    QCOMPARE(base.GetBase()[40].GetMark(),500);



    QCOMPARE(base.GetBase()[00].GetLeftElements(),(QVector<Element>{Element(-100,10,lane),Element(-1000,100,lane),Element(-100,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetLeftElements(),(QVector<Element>{Element(-100,20,lane),Element(-1000,200,lane),Element(-100,200,lane)}));
    QCOMPARE(base.GetBase()[20].GetLeftElements(),(QVector<Element>{Element(-200,30,lane),Element(-2000,300,lane),Element(-100,300,lane)}));
    QCOMPARE(base.GetBase()[30].GetLeftElements(),(QVector<Element>{Element(-300,40,lane),Element(-3000,400,lane),Element(-100,400,lane)}));
    QCOMPARE(base.GetBase()[40].GetLeftElements(),(QVector<Element>{Element(-400,50,lane),Element(-4000,500,lane),Element(-100,500,lane)}));



    QCOMPARE(base.GetBase()[00].GetRightElements(),(QVector<Element>{Element(100,10,lane),Element(1000,100,lane),Element(100,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetRightElements(),(QVector<Element>{Element(100,20,lane),Element(1000,200,lane),Element(175,200,lane)}));
    QCOMPARE(base.GetBase()[20].GetRightElements(),(QVector<Element>{Element(200,30,lane),Element(2000,300,lane),Element(250,300,lane)}));
    QCOMPARE(base.GetBase()[30].GetRightElements(),(QVector<Element>{Element(300,40,lane),Element(3000,400,lane),Element(325,400,lane)}));
    QCOMPARE(base.GetBase()[40].GetRightElements(),(QVector<Element>{Element(400,50,lane),Element(4000,500,lane),Element(400,500,lane)}));


    QCOMPARE(base.GetBase()[00].isMarked(),true);
    QCOMPARE(base.GetBase()[10].isMarked(),true);
    QCOMPARE(base.GetBase()[20].isMarked(),true);
    QCOMPARE(base.GetBase()[30].isMarked(),true);
    QCOMPARE(base.GetBase()[40].isMarked(),true);


}

void DorCad_Tests::AddUniquePkElemnts()

//Проверка на добавление уникальных елементов, проверка фнкции inser_new_pk

{
    QStringList left;
    QStringList right;

    left.push_back("11,-100,100");
    left.push_back("15,-100,100");
    left.push_back("19,-400,500");

    QCOMPARE(base.AddElements(left,TypeElement::lane),true);


    QCOMPARE(base.GetBase()[00].GetLeftElements(),(QVector<Element>{Element(-100,10,lane),Element(-1000,100,lane),Element(-100,100,lane)}));

    QCOMPARE(base.GetBase()[10].GetLeftElements(),(QVector<Element>{Element(-100,20,lane),Element(-1000,200,lane),Element(-100,200,lane)}));



    QCOMPARE(base.GetBase()[11].GetLeftElements(),(QVector<Element>{Element(-110,21,lane),
                                                                    Element(-1100,210,lane),
                                                                    Element(-100,210,lane),
                                                                    Element(-100,100,lane)}));

    QCOMPARE(base.GetBase()[15].GetLeftElements(),(QVector<Element>{Element(-150,25,lane),
                                                                    Element(-1500,250,lane),
                                                                    Element(-100,250,lane),
                                                                    Element(-100,100,lane)}));

    QCOMPARE(base.GetBase()[19].GetLeftElements(),(QVector<Element>{Element(-190,29,lane),
                                                                    Element(-1900,290,lane),
                                                                    Element(-100,290,lane),
                                                                    Element(-400,500,lane)}));

    QCOMPARE(base.GetBase()[20].GetLeftElements(),(QVector<Element>{Element(-200,30,lane),Element(-2000,300,lane),Element(-100,300,lane)}));

    QCOMPARE(base.GetBase()[30].GetLeftElements(),(QVector<Element>{Element(-300,40,lane),Element(-3000,400,lane),Element(-100,400,lane)}));

    QCOMPARE(base.GetBase()[40].GetLeftElements(),(QVector<Element>{Element(-400,50,lane),Element(-4000,500,lane),Element(-100,500,lane)}));



    QCOMPARE(base.GetBase()[00].GetRightElements(),(QVector<Element>{Element(100,10,lane),Element(1000,100,lane),Element(100,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetRightElements(),(QVector<Element>{Element(100,20,lane),Element(1000,200,lane),Element(175,200,lane)}));

    QCOMPARE(base.GetBase()[11].GetRightElements(),(QVector<Element>{Element(110,21,lane),Element(1100,210,lane),Element(182.5,210,lane)}));
    QCOMPARE(base.GetBase()[15].GetRightElements(),(QVector<Element>{Element(150,25,lane),Element(1500,250,lane),Element(212.5,250,lane)}));
    QCOMPARE(base.GetBase()[19].GetRightElements(),(QVector<Element>{Element(190,29,lane),Element(1900,290,lane),Element(242.5,290,lane)}));

    QCOMPARE(base.GetBase()[20].GetRightElements(),(QVector<Element>{Element(200,30,lane),Element(2000,300,lane),Element(250,300,lane)}));
    QCOMPARE(base.GetBase()[30].GetRightElements(),(QVector<Element>{Element(300,40,lane),Element(3000,400,lane),Element(325,400,lane)}));
    QCOMPARE(base.GetBase()[40].GetRightElements(),(QVector<Element>{Element(400,50,lane),Element(4000,500,lane),Element(400,500,lane)}));


    right.push_back("25,100,100");;
    right.push_back("35,400,500");

    QCOMPARE(base.AddElements(right,TypeElement::lane),true);

    QCOMPARE(base.GetBase()[00].GetRightElements(),(QVector<Element>{Element(100,10,lane),Element(1000,100,lane),Element(100,100,lane)}));
    QCOMPARE(base.GetBase()[10].GetRightElements(),(QVector<Element>{Element(100,20,lane),Element(1000,200,lane),Element(175,200,lane)}));

    QCOMPARE(base.GetBase()[11].GetRightElements(),(QVector<Element>{Element(110,21,lane),Element(1100,210,lane),Element(182.5,210,lane)}));
    QCOMPARE(base.GetBase()[15].GetRightElements(),(QVector<Element>{Element(150,25,lane),Element(1500,250,lane),Element(212.5,250,lane)}));
    QCOMPARE(base.GetBase()[19].GetRightElements(),(QVector<Element>{Element(190,29,lane),Element(1900,290,lane),Element(242.5,290,lane)}));

    QCOMPARE(base.GetBase()[20].GetRightElements(),(QVector<Element>{Element(200,30,lane),Element(2000,300,lane),Element(250,300,lane)}));

    QCOMPARE(base.GetBase()[25].GetRightElements(),(QVector<Element>{Element(250,35,lane),
                                                                     Element(2500,350,lane),
                                                                     Element(287.5,350,lane),
                                                                     Element(100,100,lane)}));

    qDebug()<<base.GetBase()[30].GetRightElements();
    QCOMPARE(base.GetBase()[30].GetRightElements(),(QVector<Element>{Element(300,40,lane),Element(3000,400,lane),Element(325,400,lane),Element(250,300,lane)}));

    QCOMPARE(base.GetBase()[35].GetRightElements(),(QVector<Element>{Element(350,45,lane),
                                                                     Element(3500,450,lane),
                                                                     Element(362.5,450,lane),
                                                                     Element(400,500,lane)}));



    QCOMPARE(base.GetBase()[40].GetRightElements(),(QVector<Element>{Element(400,50,lane),Element(4000,500,lane),Element(400,500,lane)}));





    QCOMPARE(base.AddElements(left,TypeElement::lane),true);

    XmlSaver saverbase(base);
    saverbase.save("D:/Новая папка/test.xml");

}

void DorCad_Tests::XMLLOADER(){
    XmlLoader load(base);
    load.load("D:/Новая папка/Дорога.xml");
}
