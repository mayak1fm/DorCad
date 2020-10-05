#include "CutView.h"


CutView::CutView (ProjectBase &Base, QWidget *parent):base(Base),
                                                      QGraphicsView(parent)
{
    CutScene= new QGraphicsScene;
    CutScene->setSceneRect(QRectF(-200,-200,400,400));
    setScene(CutScene);
    AsixRed=new QPen(Qt::red,0.1,Qt::DashLine);
    LineBlack=new QPen(Qt::black,0.1,Qt::SolidLine);
    RoadSideGreen=new QPen(Qt::green,0.1,Qt::SolidLine);
    SlopeGreen=new QPen(Qt::green,0.1,Qt::SolidLine);
    DitchBlack=new QPen(Qt::black,0.1,Qt::SolidLine);
    setDragMode(QGraphicsView::ScrollHandDrag);
    isLastPK=false;
}

void CutView::BildCut(const QVector<Element>& elementsSide)
{
    if(elementsSide.isEmpty()) {return;}
    QPoint ConnectPoint(0,0);

    for(const auto&i:elementsSide){
        double x=ConnectPoint.x()+i.width;
        double y=ConnectPoint.y()-(std::abs(i.width)*i.grad);
        QPoint ResultPoint(x,y);
        QLineF line (ConnectPoint,ResultPoint);
        cutV.push_back(qMakePair(i.type,line));
        ConnectPoint=ResultPoint;
    }

}
void CutView::PaintCut(double pk){
    CutScene->clear();
    cutV.clear();
    lastPK=pk;
    isLastPK=true;
    UnitBase cut=base.GetCut(pk);
    QLineF Asix(0,10,0,-10);
    cutV.push_back(qMakePair(TypeElement::asix,Asix));


    CutScene->addText(PkFormat(pk));

    BildCut(cut.GetLeftElements());
    BildCut(cut.GetRightElements());

    for(auto i:cutV){

        switch (i.first){
            case asix: CutScene->addLine(i.second,*AsixRed);
            break;
            case lane: CutScene->addLine(i.second,*LineBlack);
            break;
            case roadside: CutScene->addLine(i.second,*RoadSideGreen);
            break;
            case slope: CutScene->addLine(i.second,*SlopeGreen);
            break;
            case ditch: CutScene->addLine(i.second,*DitchBlack);
            break;

        }
    }
    this->setRenderHint(QPainter::Antialiasing,true);

}

void CutView::wheelEvent(QWheelEvent *event)
{



    const double scaleFactor = 1.15;

    if(event->delta() > 0)
    {
        // Zoom in
        scale(scaleFactor, scaleFactor);
        update();
    }
    else
    {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        update();

    }

    }

void CutView::updateLastPK(){
    if(isLastPK){
        PaintCut(lastPK);}
}

