#ifndef FILESAVEDIALOG_H
#define FILESAVEDIALOG_H

#include <QDialog>
#include<QLayout>
#include <QLineEdit>
#include<QLabel>
#include<QEvent>
#include<QDebug>
namespace Ui {
class filesaveDialog;
}

class filesaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filesaveDialog(QWidget *parent = 0);
    ~filesaveDialog();
    void getData(QString);

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *);
    //int exec();
signals:
    void sendData(QString);
private:
    Ui::filesaveDialog *ui;
    QGridLayout *Layout;
    QLineEdit *line;
    QString filename;
    bool flag;
};

#endif // FILESAVEDIALOG_H
