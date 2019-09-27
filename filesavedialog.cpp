#include "filesavedialog.h"
#include "ui_filesavedialog.h"

filesaveDialog::filesaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filesaveDialog)
{
    ui->setupUi(this);
    flag=0;
    setWindowTitle("Save File");
    filename="";
    Layout= new QGridLayout;
    Layout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    QLabel *label =new QLabel;
    label->setText("Save the file by following name(.txt)?");

    Layout->addWidget(label,0,0,Qt::AlignHCenter);
    line =new QLineEdit;
    line->setFixedWidth(100);
    line->setToolTip("input file name here");
    Layout->addWidget(line,1,0,Qt::AlignHCenter);
    QLabel *label1 =new QLabel;
    label1->setText(".txt");
    Layout->addWidget(label1,1,1,Qt::AlignHCenter);

    Layout->setHorizontalSpacing(0);
    ui->pushButton->setFixedSize(80, 30);
    ui->pushButton->setText("OK");
    Layout->addWidget(ui->pushButton,2,0,Qt::AlignHCenter);
    setLayout(Layout);
}

filesaveDialog::~filesaveDialog()
{
    delete ui;
}
void filesaveDialog::getData(QString s)
{
    filename=s;
    line->setText(filename);
}
void filesaveDialog::on_pushButton_clicked()
{
    QString s1=line->text();
    if(s1=="")line->setToolTip("The file name cant be empty");
    else {emit sendData(line->text());flag=1;close();}
}
void filesaveDialog::closeEvent(QCloseEvent *e)
{

    if(flag)done(Accepted);
      else   done(Rejected);
}
