#pragma once

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPair>
#include <QTableWidget>
#include "Element.h"


class AddConst : public QDialog
{
    Q_OBJECT
public:
   explicit AddConst(QWidget *pwgt =0);
   private slots:
    void CancelSlot();
    void OkeySlot();
    void AddlaySlot();
    void DellaySlot();
private:
    QVector<UnitConst> list;
    QFormLayout* LayForm=new QFormLayout;
    QHBoxLayout* LayVertical= new QHBoxLayout;
    QPushButton* Okey= new QPushButton("OK");
    QPushButton* Cancel= new QPushButton("Cancel");
    QPushButton* Addlay= new QPushButton("AddLay");
    QPushButton* Dellay= new QPushButton("DelLay");
    QLabel* textNameconst=new QLabel("Имя конструктива");
    QLabel* textNamelay=new QLabel("Имя слоя");
    QLabel* textLayh=new QLabel("Толщина слоя");
    QLineEdit* editNameconst=new QLineEdit;
    QLineEdit* editNamelay=new QLineEdit;
    QLineEdit* editLayh=new QLineEdit;
    QTableWidget* table=new QTableWidget;
    void bildtable();
signals:
 void CreatConst(QPair<QString, QVector<UnitConst>>);
};

