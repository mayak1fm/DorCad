#pragma once

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPair>



class CreateNewObWindow : public QDialog
{
    Q_OBJECT
public:
   explicit CreateNewObWindow(QWidget *pwgt =0);
   private slots:
    void ChoiceF();
    void CancelSlot();
    void OKeySlot();
private:
    
    QString nameObject;
    QString adrees;
    QFormLayout* LayForm;
    QPushButton* Okey;
    QPushButton* Cancel ;
    QPushButton* Folder ;
    QLabel* TextName ;
    QLabel* TextCatalog ;
    QLabel* TextCatalogChoise;
    QLabel* CatalogChoise;
    QLineEdit* NameEdit;




signals:
 void createw(QPair<QString,QString>);
};

