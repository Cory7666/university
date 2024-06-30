#include <iostream>
#include "mainwindow.hxx"
#include "./ui_mainwindow.h"

#define REPLACED_CHAR_PLACEHOLDER "*"
#define REPLACED_CHAR_LATIN       "a"
#define REPLACED_CHAR_CYRILLIC    "а"

using std::clog;
using std::endl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->changeTitleButton, SIGNAL(clicked(bool)), this, SLOT(onChangeTitle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChangeTitle()
{
    const auto& newTitle = ui->newTitleField->toPlainText();

    if (newTitle.isEmpty())
    {
        clog << "The user wanted to change the title of the window, but did not enter anything." << endl;
    }
    else
    {
        clog << "Change Window Title to " << newTitle.toStdString() << endl;
        this->setWindowTitle(newTitle);
    }
}

void MainWindow::on_originTextField_textChanged(const QString &text)
{
    QString modifiedText = text;
    modifiedText.replace(REPLACED_CHAR_LATIN, REPLACED_CHAR_PLACEHOLDER, Qt::CaseInsensitive)
                .replace(REPLACED_CHAR_CYRILLIC, REPLACED_CHAR_PLACEHOLDER, Qt::CaseInsensitive);

    const qsizetype restrictedCharsCount = text.count(REPLACED_CHAR_LATIN, Qt::CaseInsensitive)
                                           + text.count(REPLACED_CHAR_CYRILLIC, Qt::CaseInsensitive);

    QString statusMessage{""};

    if (10 <= restrictedCharsCount)
    {
        clog << "Disable input field." << endl;
        statusMessage = " (ввод отключён)";
        ui->originTextField->setDisabled(true);
    } else {}
    ui->statusTextField->setText(QString::number(restrictedCharsCount) + statusMessage);
    ui->clearedTextField->setText(modifiedText);
}

