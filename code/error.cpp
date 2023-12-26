#include "error.h"
#include "ui_error.h"
#include <QMessageBox>

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    setWindowTitle("Incorrect");
}

error::~error()
{
    delete ui;
}

void error::on_sol_clicked()
{
    ui->stackedWidget1->setCurrentIndex(1);
}

void error::on_back_clicked()
{
    close();
}

void error::on_pushButton_clicked()
{
    ui->stackedWidget1->setCurrentIndex(0);
}

void error::on_enterButton_clicked()
{
    if(findChild<QLineEdit *>("password")->text() == "0000"){
        ui->stackedWidget1->setCurrentIndex(2);
        setWindowTitle("Solution");
    }else{
        QMessageBox::warning(this,"Wrong Password","Password Incorrect");
    }
}
