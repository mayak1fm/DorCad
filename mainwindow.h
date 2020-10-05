#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include "ui_mainwindow.h"
#include "createnewobwindow.h"
#include "ObjectWindow.h"
#include "ProjectBase.h"
#include "unitedxml.h"
#include "deletenumbers.h"
#include "XmlLoader.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMenu* File;
    QAction* NewOb = new QAction (tr("New ojbject"),this);
    QAction* OpenConst=new QAction(tr("Open Construction"),this);
    QAction* Save= new QAction(tr("Save Construction"),this);

    QMenu* Project;
    QAction* NewConst= new QAction (tr("New const"),this);
    QAction* AddAxis = new QAction (tr("Add Axis"),this);
    QAction* AddElement=new QAction(tr("Add Element"),this);
    QAction* SetConst=new QAction(tr("SetConst"),this);
public slots:
void CreateProjectWindow(QPair<QString,QString> str);
void NewC();

void open();
private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
