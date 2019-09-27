#include "replacedialog.h"
#include "ui_replacedialog.h"

replaceDialog::replaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::replaceDialog)
{
    ui->setupUi(this);
    setWindowTitle("Replace");
    Layout = new QGridLayout;
    Layout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    line1 =new QLineEdit;
    line2 =new QLineEdit;
    QLabel *label1=new QLabel;
    label1->setText("Find content:");
    Layout->addWidget(label1,0,0);

    QLabel *label2=new QLabel;
    label2->setText("Replace to:");
    Layout->addWidget(label2,1,0);

    ui->pushButton->setText("replace next");
    Layout->addWidget(line1,0,1);
    Layout->addWidget(line2,1,1);
    Layout->addWidget(ui->pushButton,0,2);
    this->setLayout(Layout);
}

replaceDialog::~replaceDialog()
{
    delete ui;
}

void replaceDialog::on_pushButton_clicked()
{
    QString temp1=line1->text(),temp2=line2->text();
    if(temp1=="")
    {
     QMessageBox::critical(NULL, "Warning", "the context can't be empty", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
        else
    {
        emit sendData(temp1,temp2);
    }
}
