#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include<QLayout>
#include<QLineEdit>
#include<QMessageBox>
#include <QLabel>
namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT

public:
    explicit findDialog(QWidget *parent = 0);
    ~findDialog();

private slots:
    void on_PushButton_clicked();
signals:
    void sendData(QString);
private:
    Ui::findDialog *ui;
    QGridLayout *Layout;
    QLineEdit *line;

};

#endif // FINDDIALOG_H
