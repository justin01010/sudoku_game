#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class error;
}

class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QWidget *parent = nullptr);
    ~error();

private slots:
    void on_sol_clicked();
    void on_back_clicked();
    void on_pushButton_clicked();
    void on_enterButton_clicked();

private:
    Ui::error *ui;
};

#endif // ERROR_H
