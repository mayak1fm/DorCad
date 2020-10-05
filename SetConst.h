#pragma once

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include "Element.h"
#include "PlanView.h"
#include"ProjectBase.h"
class SetConst: public QDialog
{
    Q_OBJECT
public:
    explicit SetConst(ProjectBase& Base,QWidget *pwgt =0);

private:
    ProjectBase& base;
    QPushButton* Okey;
    QPushButton* Cancel;
    QCheckBox* AllElementsChoice;
    QLabel* Description;
    QLabel* AllElemChoiceLabel;
    QLabel* PkBeginLabel;
    QLabel* PkEndLabel;
    QLabel* ConChoiceLabel;
    QLabel* TypeElemChoiseLabel;
    QComboBox* ConstuctiveChoise;
    QComboBox* TypeElementChoise;
    QLineEdit* PkBegin;
    QLineEdit* PkEnd;
    PlanView* plan;
    side Side;
    int LaneNumber;

private slots:
    void OkeySlot();
    void CancelSlot();
    void CheckBoxSlot();
};

