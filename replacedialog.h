#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include<QLayout>
#include<QLineEdit>
#include<QMessageBox>
#include <QLabel>
namespace Ui {
class replaceDialog;
}

class replaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit replaceDialog(QWidget *parent = 0);
    ~replaceDialog();

private slots:
    void on_pushButton_clicked();
signals:
    void sendData(QString,QString);
private:
    Ui::replaceDialog *ui;
    QGridLayout *Layout;
    QLineEdit *line1,*line2;

};

#endif // REPLACEDIALOG_H
