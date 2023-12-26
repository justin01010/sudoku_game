#ifndef SUDOKU_H
#define SUDOKU_H

#include <QApplication>
#include <QMainWindow>
#include <puzzle.h>
#include <warning.h>
#include <error.h>

QT_BEGIN_NAMESPACE
namespace Ui { class sudoku; }
QT_END_NAMESPACE

class sudoku : public QMainWindow
{
    Q_OBJECT

public:
    sudoku(QWidget *parent = nullptr);
    ~sudoku();
    QString gridcode = "00";
    puzzle *p;
    error *e;
    warning *w;

private slots:  //used function call with slots (to access with button....)

    void changeColorOriginal();
    void changeColorTemp();
    void numPressed();
    void gridPressed();

    void on_menuButton_clicked();
    void difficultyPressed();
    void startgame(QString diff);
    void popupClosed();
    void on_clearButton_clicked();
    void on_resetButton_clicked();
    void on_hintButton_clicked();
    void on_checkButton_clicked();
    void eClose();
    void autofill();


private:
    Ui::sudoku *ui;
};
#endif // SUDOKU_H
