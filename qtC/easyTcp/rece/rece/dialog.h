#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT



public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


private slots:

    void acceptConnection();
    void readClient();

    void on_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    int c_port;
    void updateLabel(void);
};

#endif // DIALOG_H
