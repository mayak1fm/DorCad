#ifndef CUTCHOISE_H
#define CUTCHOISE_H
#include <QComboBox>
#include "ProjectBase.h"
class CutChoise :public QComboBox
{
    Q_OBJECT
public:
    CutChoise(ProjectBase& Base, QWidget *pwgt=0);
private:
    ProjectBase& base;
    QStringList pkString;
    QVector<double> pkDouble;
public:
    void update();
private slots:
     void ShowCut(int n);
signals:
    void show(double pk);
};

#endif // CUTCHOISE_H
