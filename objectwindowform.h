#ifndef OBJECTWINDOWFORM_H
#define OBJECTWINDOWFORM_H

#include <QWidget>

namespace Ui {
class ObjectWindowForm;
}

class ObjectWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectWindowForm(QWidget *parent = nullptr);
    ~ObjectWindowForm();

private:
    Ui::ObjectWindowForm *ui;
};

#endif // OBJECTWINDOWFORM_H
