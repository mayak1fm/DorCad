#pragma once

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>




class AddAxis : public QDialog
{
    Q_OBJECT
public:
   explicit AddAxis(QWidget *pwgt =0);
   private slots:
   void OpenSlot();
   void OkeySlot();
   void CancelSlot();
private:
    QString adress;
    QFormLayout* LayForm=new QFormLayout;
    QPushButton* Okey= new QPushButton("OK");
    QPushButton* Cancel= new QPushButton("Cancel");
    QPushButton* Open= new QPushButton("Open");
    QLabel* adressString=new QLabel("Местоположение файла");

signals:
  void CreateAxis(QString&);
};

