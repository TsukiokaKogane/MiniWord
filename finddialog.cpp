#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    Layout = new QGridLayout;
    Layout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    line =new QLineEdit;
    this->setWindowTitle("Find");
    ui->PushButton->setText("Find next");
    QLabel *label =new   QLabel;
    label->setText("Find content:");
    Layout->addWidget(label,0,0);
    Layout->addWidget(line,0,1);
    Layout->addWidget(ui->PushButton,0,2);
    this->setLayout(Layout);
}

findDialog::~findDialog()
{
    delete ui;
}

void findDialog::on_PushButton_clicked()
{
   QString temp=line->text();
   if(temp=="")
   {
    QMessageBox::critical(NULL, "Warning", "the context can't be empty", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
   }
       else
   {
       emit sendData(temp);
   }
}
