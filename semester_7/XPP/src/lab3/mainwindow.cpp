#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myemailvalidator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->acceptButton, SIGNAL(clicked(bool)), this, SLOT(sendUserData()));
    ui->emailInputField->setValidator(new MyEmailValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendUserData(void)
{
    using std::clog;
    using std::cerr;
    using std::endl;

    if (this->_areInputFieldsValid())
    {
        const bool send_res = UserDataService().send(this->_packToStruct());
        if (send_res)
        {
            this->_clearFields();
        }
        else
        {
            cerr << "Failed to save data." << endl;
        }
    }
    else
    {
        cerr << "Incorrect user data." << endl;
    }
}

bool MainWindow::_areInputFieldsValid() const
{
    return ui->emailInputField->hasAcceptableInput()
           && (not ui->nameInputField->text().isEmpty())
           && (not ui->titleInputField->text().isEmpty())
           && (not ui->bodyInputField->toHtml().isEmpty());
}

UserData MainWindow::_packToStruct(void) const
{
    return UserData{
        ui->nameInputField->text(),
        ui->emailInputField->text(),
        ui->titleInputField->text(),
        ui->bodyInputField->toHtml()
    };
}

void MainWindow::_clearFields(void)
{
    ui->nameInputField->clear();
    ui->emailInputField->clear();
    ui->titleInputField->clear();
    ui->bodyInputField->clear();
}
