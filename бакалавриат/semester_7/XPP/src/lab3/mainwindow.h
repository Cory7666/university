#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userdataservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void sendUserData(void);

private:
    Ui::MainWindow *ui;

    bool _areInputFieldsValid(void) const;
    UserData _packToStruct(void) const;
    void _clearFields(void);
};
#endif // MAINWINDOW_H
