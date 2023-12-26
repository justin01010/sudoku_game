#include "sudoku.h"
#include "ui_sudoku.h"
#include "puzzle.h"
#include "warning.h"
#include "error.h"
#include <QThread>

sudoku::sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sudoku)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //number buttons setup
    QPushButton *numButtons[9];
    for(int i=0;i<9;i++){
        QString butName = "num" + QString::number(i+1);
        numButtons[i]= sudoku::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(numPressed()));
    }

    //interface grid setup
    QPushButton *gridButtons[9][9];
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            QString butName = "sudokuGrid" + QString::number(i)+QString::number(j);

            gridButtons[i][j]= sudoku::findChild<QPushButton *>(butName);
            gridcode = QString::number(i) + QString::number(j);
            changeColorOriginal();
            connect(gridButtons[i][j],SIGNAL(released()),this,SLOT(gridPressed()));
        }
    }

    //difficulty button setup
    connect(sudoku::findChild<QPushButton *>("easy"),SIGNAL(released()),this,SLOT(difficultyPressed()));
    connect(sudoku::findChild<QPushButton *>("intermediate"),SIGNAL(released()),this,SLOT(difficultyPressed()));
    connect(sudoku::findChild<QPushButton *>("hard"),SIGNAL(released()),this,SLOT(difficultyPressed()));
    connect(sudoku::findChild<QPushButton *>("expert"),SIGNAL(released()),this,SLOT(difficultyPressed()));

    //initialize puzzle
    p = new puzzle("easy");
    w= new warning;
    e = new error(this);

    //connect buttons on popup window
    connect(w->findChild<QPushButton *>("Yes"), SIGNAL(clicked()), this, SLOT(popupClosed()));
    connect(e->findChild<QPushButton *>("backtomenu"), SIGNAL(clicked()), this, SLOT(eClose()));
    connect(e->findChild<QPushButton *>("autofill"), SIGNAL(clicked()), this, SLOT(autofill()));

}

sudoku::~sudoku()
{
    delete ui;
}


void sudoku::difficultyPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString diff = button->objectName();
    startgame(diff);
    ui->stackedWidget->setCurrentIndex(1);
    p->printsol();
}

void sudoku::startgame(QString diff){
    delete p;
    p = new puzzle(diff);
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            QPushButton *gridButton = sudoku::findChild<QPushButton *>("sudokuGrid"+QString::number(j)+QString::number(i));
            if(p->vtr[j][i] == 0){
                gridButton->setText("");
                gridButton->setDisabled(false);
            }else{
                gridButton->setText(QString::number(p->vtr[j][i]));
                gridButton->setDisabled(true);
            }
            changeColorOriginal();
        }
    }
    p->startStatus =false;
}

void sudoku::on_menuButton_clicked()
{
    w->setModal(true);
    w->exec();
}

void sudoku::popupClosed(){
    w->close();
    ui->stackedWidget->setCurrentIndex(0);
}

void sudoku::eClose(){
    ui->stackedWidget->setCurrentIndex(0);
    e->close();
}

void sudoku::numPressed(){
    if(p->startStatus == true){
        QPushButton *numButton = (QPushButton *)sender();
        QString gridName = "sudokuGrid" + gridcode;
        QPushButton *gridButton = sudoku::findChild<QPushButton *>(gridName);
        QString buttonNumber = numButton->text();
        gridButton->setText(buttonNumber);
        QString tmp1 = gridcode[0];
        QString tmp2 = gridcode[1];
        p->sheet[tmp1.toInt()][tmp2.toInt()] = buttonNumber.toInt();
    }
}

void sudoku::gridPressed(){
    QPushButton *gridButton = (QPushButton *)sender();
    QString code = (gridButton->objectName());
    changeColorOriginal();
    gridcode = QString(code[code.length()-2]) + QString(code[code.length()-1]);
    changeColorTemp();
    p->startStatus =true;
}

void sudoku::changeColorOriginal(){
    int row = gridcode.toInt()%10;
    int col = gridcode.toInt()/10;
    QString gridName = "sudokuGrid" + gridcode;
    QPushButton *gridButton = sudoku::findChild<QPushButton *>(gridName);
    if(((row<=2||row>=6)&&(col<=2||col>=6))||((row>=3&&row<=5)&&(col>=3&&col<=5))){
        gridButton->setStyleSheet("background-color:#F5DEB3");  //F5DEB3
    }else{
        gridButton->setStyleSheet("background-color:#FFDA89");  //E6BF83
    }
}

void sudoku::changeColorTemp(){
    QString gridName = "sudokuGrid" + gridcode;
    QPushButton *gridButton = sudoku::findChild<QPushButton *>(gridName);
    gridButton->setStyleSheet("background-color:#FFFFE0");  //FFFFE0
}

void sudoku::on_clearButton_clicked()
{
    QString gridName = "sudokuGrid" + gridcode;
    QPushButton *gridButton = sudoku::findChild<QPushButton *>(gridName);
    if(gridButton->isEnabled()==true){
        gridButton->setText("");
        gridButton->setDisabled(false);
        QString tmp1 = gridcode[0];
        QString tmp2 = gridcode[1];
        p->sheet[tmp1.toInt()][tmp2.toInt()] = 0;
    }
}

void sudoku::on_resetButton_clicked()
{
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            QPushButton *gridButton = sudoku::findChild<QPushButton *>("sudokuGrid"+QString::number(j)+QString::number(i));
            if(p->vtr[j][i] == 0){
                gridButton->setText("");
            }else{
                gridButton->setText(QString::number(p->vtr[j][i]));
                gridButton->setDisabled(true);
            }
            changeColorOriginal();
        }
    }
    p->sheet = p->vtr;
    p->startStatus = false;
}

void sudoku::on_hintButton_clicked()
{
    if(p->startStatus==true){
        QString gridName = "sudokuGrid" + gridcode;
        QPushButton *gridButton = sudoku::findChild<QPushButton *>(gridName);
        QString tmp1 = gridcode[0];
        QString tmp2 = gridcode[1];
        int tmp =p->sol[tmp1.toInt()][tmp2.toInt()];
        if(tmp != p->vtr[tmp1.toInt()][tmp2.toInt()]){
            gridButton->setDisabled(true);
            gridButton->setText(QString::number(tmp));
            p->sheet[tmp1.toInt()][tmp2.toInt()] = tmp;
            p->vtr[tmp1.toInt()][tmp2.toInt()] = tmp;
            p->hint++;
        }
    }
}


void sudoku::on_checkButton_clicked()
{
    if(p->sheet==p->sol){
        e->findChild<QStackedWidget *>("stackedWidget1")->setCurrentIndex(3);
        e->setWindowTitle("Correct!");
        e->findChild<QLabel *>("finalLabel")->setText("You have finished:\n  Difficulty:  "+p->difficulty+"\n  Hint used:  "+QString::number(p->hint));
        e->show();
    }else{
        int tmp=0;
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                if(p->sheet[j][i] != p->sol[j][i]){
                    tmp++;
                }
            }
        }
        e->findChild<QLabel *>("displayIncorrect")->setText(QString::number(tmp)+ " Incorrect numbers");
        e->findChild<QStackedWidget *>("stackedWidget1")->setCurrentIndex(0);
        QString temp="";
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                temp += QString::number(p->sol[i][j])+"   ";
                if(j==2||j==5){
                    temp +="  ";
                }
            }
            temp += "\n";
            if(i==2||i==5){
                temp +="\n";
            }
        }
        e->findChild<QLabel *>("solution")->setText(temp);
        e->setWindowTitle("Incorrect");
        e->show();
    }
}

void sudoku::autofill(){
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            int tmp = p->sol[i][j];
            if(tmp != p->vtr[i][j]){
                QPushButton* gridButton = sudoku::findChild<QPushButton *>("sudokuGrid"+QString::number(i)+QString::number(j));
                gridButton->setText(QString::number(tmp));
                p->sheet[i][j] = tmp;
            }
        }
    }
}



