#include "objectwindowform.h"
#include "ui_objectwindowform.h"

ObjectWindowForm::ObjectWindowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectWindowForm)
{
    ui->setupUi(this);
}

ObjectWindowForm::~ObjectWindowForm()
{
    delete ui;
}
