#ifndef CUTVIEW_H
#define CUTVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

#include "ProjectBase.h"
#include "dormath.h"
#include <QMouseEvent>
class CutView: public QGraphicsView
{
    Q_OBJECT
public:

    explicit CutView(ProjectBase&  Base, QWidget *pwgt =0);
public slots:
    void PaintCut(double pk);
    void updateLastPK();
protected:
    void wheelEvent(QWheelEvent *event) override;


private:
    int m_originX;
    int m_originY;
    QPen* AsixRed;
    QPen* LineBlack;
    QPen* RoadSideGreen;
    QPen* SlopeGreen;
    QPen* DitchBlack;
    ProjectBase& base;
    QGraphicsScene* CutScene;
    QVector<QPair<TypeElement,QLineF>> cutV;
    double lastPK=0;
    bool isLastPK;

    void BildCut(const QVector<Element>& elementsSide);


};

#endif // CUTVIEW_H
