#pragma once

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>
#include "Element.h"
#include <QHBoxLayout>




class AddElement : public QDialog
{
    Q_OBJECT
public:
   explicit AddElement (QWidget *pwgt =0);
   private slots:
   void OpenSlot();
   void OkeySlot();
   void CancelSlot();
private:
    QStringList types={"полоса","обочина","откос","кювет"};
    QString adress;
    QComboBox* ElementTypes= new QComboBox;
    QHBoxLayout* LayH=new QHBoxLayout;
    QFormLayout* LayForm=new QFormLayout;
    QPushButton* Okey= new QPushButton("OK");
    QPushButton* Cancel= new QPushButton("Cancel");
    QPushButton* Open= new QPushButton("Open");
    QLabel* adressString=new QLabel("Местоположение файла");

signals:
  void CreateElement(QString&,TypeElement);
};

