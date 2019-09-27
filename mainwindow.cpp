#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include "rowlist.h"
#include "QClipboard"
#include <QMessageBox>
#include"filesavedialog.h"
#include "finddialog.h"
#include "replacedialog.h"
extern rowlist *headptr;
extern int mouse_row,mouse_col,rowlist_num,mposx0,mposy0,mposx1,mposy1;
extern QString _clipboard;
extern bool file_is_saved;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filename=filepath="";
    this->setAttribute(Qt::WA_InputMethodEnabled);
    this->resize(840,480);
    ui->scrollArea->setAttribute(Qt::WA_InputMethodEnabled);
    ui->scrollArea->installEventFilter(this);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    Layout=new QVBoxLayout;
    Layout->setSizeConstraint(QVBoxLayout::SetFixedSize);
    ui->centralWidget->setStyleSheet("background-color:white;");
    ui->scrollAreaWidgetContents->setLayout(Layout);
    ui->scrollAreaWidgetContents->setContentsMargins(0,0,0,0);
    ui->Statusbar->setCheckable(true);
    ui->Statusbar->setChecked(true);
    ui->statusBar->show();
    slabel = new  QLabel;
    //slabel->setText("row: "+QString::number(mouse_row+1)+"   "+"colunm: "+QString::number(mouse_col+1));
    slabel->setAlignment(Qt::AlignRight);
    ui->statusBar->addWidget(slabel);
   // ui->Copy->setEnabled(false);
    setInitMode();
}
bool  MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::InputMethod)
    {
        QInputMethodEvent *keyEvent = static_cast<QInputMethodEvent *>(event);
        MainWindow::inputMethodEvent(keyEvent);
         return true;

    }
        else if(event->type()==QEvent::KeyPress)
    {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
         MainWindow::keyPressEvent(keyEvent);
         return true;
    }
    return QMainWindow::eventFilter(obj,event);
}
void MainWindow::getFilename(QString data)
{
    filename=data;
}
void MainWindow::Find_t(QString data)//where to find
{
     Clearlabel();
    rowlist *temp=headptr;
    int i=mouse_row;
    while(i)
    {
        //qDebug()<<"cnm";
        temp=temp->nextrowlistptr;
        i--;
    }
    int j=mouse_col;
    int return_num;
    return_num=temp->find_string(j,data);
    if(return_num!=-1)mouse_col=return_num;
    else
    {
        qDebug()<<return_num;
        while(temp->nextrowlistptr!=NULL)
        {
            temp=temp->nextrowlistptr;
            mouse_row++;
            return_num=temp->find_string(0,data);
            if(return_num!=-1)
            {
                mouse_col=return_num;
                break;
            }
        }

    }

    if(return_num==-1){mouse_col=get_rowlen(mouse_row);QMessageBox::about(NULL, "Can't find anymore", "Can't find next : "+data+" after cursor in the text.");}
 Addlabel();
    //qDebug()<<data<<"\n";
}
void MainWindow::Replace_t(QString data1,QString data2)//data1:  data to replace || data2: replace content
{
    Clearlabel();
    rowlist *temp=headptr;
    int i=mouse_row;
    while(i)
    {
        temp=temp->nextrowlistptr;
        i--;
    }
    int j=mouse_col;
    int return_num;
    return_num=temp->exchange_string(j,data1,data2);
    if(return_num==-1)
    {
        while(temp->nextrowlistptr!=NULL)
        {
            temp=temp->nextrowlistptr;
            ++mouse_row;
            return_num=temp->exchange_string(0,data1,data2);
            if(return_num!=-1)
            {
                mouse_col=return_num;
                break;
            }
        }
    }
    else mouse_col=return_num;

    if(return_num==-1){mouse_col=get_rowlen(mouse_row);QMessageBox::about(NULL, "Can't replace anymore", "Can't find next : "+data1+" after cursor in the text.");}
Addlabel();
   qDebug()<<data1<<" "<<data2<<"\n";
}
void MainWindow::setInitMode()
{

   ui->Copy->setEnabled(false);
    ui->Cut->setEnabled(false);
    ui->Delete->setEnabled(false);
    ui->Paste->setEnabled(false);
    ui->Find->setEnabled(false);
    ui->Replace->setEnabled(false);
    ui->SelectAll->setEnabled(false);
   ui->Savefile->setEnabled(false);
   file_is_saved=1;
}
void MainWindow::setClipboard()
{
 QClipboard *board = QApplication::clipboard();
 _clipboard= board->text();
 if(_clipboard!="")ui->Paste->setEnabled(true);
    else ui->Paste->setEnabled(false);
 }
void MainWindow::setEditMode()
{
     ui->Copy->setEnabled(true);
     ui->Cut->setEnabled(true);
     ui->Delete->setEnabled(true);
     ui->Find->setEnabled(true);
     ui->Replace->setEnabled(true);
     ui->SelectAll->setEnabled(true);
     ui->Savefile->setEnabled(true);
   setClipboard();

}
MainWindow::~MainWindow()
{
    delete ui;
    delete Layout;
}
void MainWindow::Clearlabel()
{
    rowlist *temp=headptr;
    while(temp!=NULL)
    {
       //qDebug()<<"1111111";
        temp->label->setParent(nullptr);
        Layout->removeWidget(temp->label);
        temp=temp->nextrowlistptr;
    }
    QLayoutItem *child;
    while ((child = Layout->takeAt(0)) != 0)delete child;
    slabel->setParent(nullptr);
    ui->statusBar->removeWidget(slabel);

}
void MainWindow::Addlabel()
{
    int i=0;
    QFont font;
    font.setPixelSize(20);
    font.setFixedPitch(1);
    rowlist *temp=headptr;
    int mpx0=mposx0;
    int mpy0=mposy0;
    int mpx1=mposx1;
   int  mpy1=mposy1;
     if(!cmp(mpx0,mpy0,mpx1,mpy1))
     {
         std::swap(mpx0,mpx1);
         std::swap(mpy0,mpy1);
     }
     int nx=0,ny=0;
     qDebug()<<"?????";
    while(temp!=NULL)
    {
        //if(i>20)break;
        qDebug()<<" "<<temp->get_store()<<"\n";
        temp->label->setFont(font);
        temp->label->setText(temp->get_store());
        temp->label->setCursor(Qt::IBeamCursor);
        Layout->addWidget(temp->label);

        if(i==mouse_row)
        {
            temp->label->Getpos(1,ch2_eng1(mouse_row,mouse_col));
            QPoint p=temp->label->pos();
            nx=p.x()+mouse_row*temp->label->height();
            ny=p.y()+ch2_eng1(mouse_row,mouse_col)*10;

        }
         else temp->label->Getpos(0,ch2_eng1(mouse_row,mouse_col));
        if(mpx0==mpx1&&mpy1==mpy0||mpx0>i||mpx1<i)temp->label->Getarea(0,0);
        else
        {
            int lx;
            if(mpx0<i)lx=0;
             else lx=ch2_eng1(i,mpy0);
            int rx;
            if(mpx1>i)rx=ch2_eng1(i,temp->get_row_length());
             else rx=ch2_eng1(i,mpy1);
            temp->label->Getarea(lx,rx);
            qDebug()<<"pos: "<<i<<" "<<lx<<" "<<rx<<"\n";
        }
        temp->label->update();
        temp=temp->nextrowlistptr;
        i++;
    }
    slabel->setText("row: "+QString::number(mouse_row+1)+"   "+"colunm: "+QString::number(mouse_col+1));
    ui->statusBar->addWidget(slabel);
     qDebug()<<"final!!!"<<nx<<" "<<ny<<"\n";
   //  ui->scrollArea->horizontalScrollBar()->setValue(40);
   //  ui->scrollArea->horizontalScrollBar()->setSliderPosition(ui->scrollArea->horizontalScrollBar()->value());

}
void MainWindow::mouseReleaseEvent(QMouseEvent *evt)
{
    qDebug()<<"?????"<<ui->scrollArea->horizontalScrollBar()->sliderPosition()<<"\n";

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    //窗口关闭之前需要的操作~
    MainWindow::on_Exit_triggered();

}
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    pop_menu=new QMenu(this);//创建菜单
    //菜单添加信号
    pop_menu->addAction(ui->Cut);
    pop_menu->addAction(ui->Copy);
    pop_menu->addAction(ui->Paste);
    pop_menu->addAction(ui->Delete);
    QAction *tempaction=new QAction(this);
    tempaction->setSeparator(true);
    pop_menu->addAction(tempaction);
    pop_menu->addAction(ui->SelectAll);
    //获取鼠标位置
    QCursor cur=this->cursor();
    pop_menu->exec(cur.pos());
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!ui->Savefile->isEnabled())return;
    Clearlabel();
    qDebug()<<"x:"<<mouse_row<<" y:"<<mouse_col<<" "<<rowlist_num<<"\n";
    switch(event->key())
    {
       case Qt::Key_Home:mouse_col=0;break;
       case Qt::Key_End:mouse_col=get_rowlen(mouse_row);break;
       case Qt::Key_Enter : Insert(mouse_row,mouse_col,"\n");break;
       case Qt::Key_Space : Insert(mouse_row,mouse_col," ");break;
       case Qt::Key_Tab :Insert(mouse_row,mouse_col,"  ");break;
       case Qt::Key_Backspace :
       if(mposx0!=mposx1||mposy0!=mposy1)on_Cut_triggered();
       else {Backspace(mouse_row,mouse_col);}
         break;
       case Qt::Key_Up :
       if(mouse_row){mouse_row--;mouse_col=inverse_ch2_eng1(mouse_row,ch2_eng1(mouse_row+1,mouse_col));}
       break;
       case Qt::Key_Down :if(mouse_row<rowlist_num-1){mouse_row++;mouse_col=inverse_ch2_eng1(mouse_row,ch2_eng1(mouse_row-1,mouse_col));}
       break;
       case Qt::Key_Left :
       if(mouse_col)mouse_col--;
       else if(mouse_row){mouse_row--;mouse_col=get_rowlen(mouse_row);}
       break;
       case Qt::Key_Right :
      if(mouse_col<get_rowlen(mouse_row))mouse_col++;
       else if(mouse_row<rowlist_num-1){mouse_row++;mouse_col=0;}
      break;
       default:Insert(mouse_row,mouse_col,event->text());file_is_saved=0;
    }

  if(!file_is_saved) setWindowTitle("*"+filename+" - Miniword");
  Clearlabel();
  Addlabel();
}
void MainWindow::inputMethodEvent(QInputMethodEvent *event)
{
    // qDebug()<<"x:"<<mouse_row<<" y:"<<mouse_col<<"\n";
    if(!ui->Savefile->isEnabled())return;
    Clearlabel();
    file_is_saved=0;
    Insert(mouse_row,mouse_col,event->commitString());
    file_is_saved=0;
    Addlabel();
    if(!file_is_saved) setWindowTitle("*"+filename+" - Miniword");
}

void MainWindow::on_Openfile_triggered()
{
    if(file_is_saved==0)MainWindow::on_Exit_triggered();
    Clearlabel();
    QFile file;
    filepath = QFileDialog::getOpenFileName(this, QString("open"), QString("/"),QString("TEXT(*.txt)"));
    file.setFileName(filepath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QFileInfo fi =QFileInfo(filepath);
        filename =fi.baseName();
        filepath =fi.absolutePath();
        filepath+="/";
        qDebug()<<filepath<<"\n";
        QByteArray t ;
        while(!file.atEnd())t+= file.readLine();
        file.close();
        QTextCodec *codec =QTextCodec::codecForLocale();
        vecrowlist_init(codec->toUnicode(t));
        Addlabel();
      setEditMode();
      file_is_saved=1;
      setWindowTitle(filename+" - Miniword");
    }
    else
    {
        QMessageBox::warning(NULL, "Warning","No file is opened", QMessageBox::Ok, QMessageBox::Ok);

    }

}

void MainWindow::on_Statusbar_triggered(bool checked)
{
    if(checked)  {ui->statusBar->show(); ui->Statusbar->setChecked(true);}
      else {ui->statusBar->hide(); ui->Statusbar->setChecked(false);}
}

void MainWindow::on_Savefile_triggered()
{
    if(filepath=="")
    {
        filepath=QString (QCoreApplication::applicationDirPath());
        filepath+="/";
        qDebug()<<filepath<<"\n";

    }
    filesaveDialog *w=new filesaveDialog;
    connect(w,SIGNAL(sendData(QString)),this,SLOT(getFilename(QString)));
    w->getData(filename);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
    int x=w->exec();
    if(x==QDialog::Accepted)
    {
        QString temp;
        temp=filepath+filename+".txt";
        QFileInfo fi(temp);
        if(fi.isFile())
        {
          QMessageBox::StandardButton msg = QMessageBox::question(NULL, "Warning", "The file is already exsited ,Do you want to overwrite it?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          if(msg==QMessageBox::No)
          {
              QMessageBox::warning(NULL, "Warning","save session is canceled", QMessageBox::Ok, QMessageBox::Ok);
              return ;
          }
        }
         QFile file(temp);
         qDebug()<<temp<<"\n";
         if(file.open(QIODevice::ReadWrite|QIODevice::Text| QIODevice::Truncate))
         {
             QTextStream out(&file);
             rowlist *temp=headptr;
              while(temp!=NULL)
              {
                   out<<temp->get_store();
                   temp=temp->nextrowlistptr;
                   if(temp!=NULL)out<<"\n";
              }
              file_is_saved=1;
              setWindowTitle(filename+" - Miniword");
           }
           else
           {
               QMessageBox::warning(NULL, "Warning","can't open the file ", QMessageBox::Ok, QMessageBox::Ok);
           }
    }
    else
    {
         QMessageBox::warning(NULL, "Warning","save session is canceled", QMessageBox::Ok, QMessageBox::Ok);
         return ;
    }
}

void MainWindow::on_Newfile_triggered()
{
    if(file_is_saved==0)MainWindow::on_Exit_triggered();
    file_is_saved=0;
    vecrowlist_clear();
    setEditMode();
    filepath="";
    filename="Newtxt";
    setWindowTitle("*"+filename+" - Miniword");
    vecrowlist_init("");
}

void MainWindow::on_AboutMiniWord_triggered()
{

  QMessageBox::information(NULL, "About MinWord", "This is a Boyang Chen and Hayang Li's project build by QT \nCopyright(c) 2018\nAll rights reserved\nVersion: v1.0.0", QMessageBox::Ok, QMessageBox::Ok);

}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
  Clearlabel();
  mposx0=mposx1;
  mposy0=mposy1;
  mposx1=mouse_row;
  mposy1=mouse_col;
  Addlabel();
  qDebug()<<mposx0<<" "<<mposy0<<"\n";
};

void MainWindow::on_Exit_triggered()
{
    mouse_col=mouse_row=0;
    mposx0=mposx1=mposy0=mposy1=0;
    while(!file_is_saved)
    {
        QMessageBox::StandardButton msg = QMessageBox::question(NULL, "Warning", "Current file isn't saved, do you want to save it?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
         Clearlabel();
        if(msg==QMessageBox::Yes)MainWindow::on_Savefile_triggered();
         else break;
    }


    vecrowlist_clear();
    setWindowTitle("Miniword");
    setInitMode();
}

void MainWindow::on_Delete_triggered()
{
    if(mposx0!=mposx1||mposy0!=mposy1)on_Cut_triggered();
    else
    {
      Clearlabel();
      Delete(mouse_row,mouse_col);
      file_is_saved=0;
      Addlabel();
    }
}

void MainWindow::on_Find_triggered()
{

    findDialog *w=new findDialog;
    connect(w,SIGNAL(sendData(QString)),this,SLOT(Find_t(QString)));
    w->show();

}

void MainWindow::on_Replace_triggered()
{

    replaceDialog *w=new replaceDialog;
    connect(w,SIGNAL(sendData(QString,QString)),this,SLOT(Replace_t(QString,QString)));
    w->show();


}

void MainWindow::on_Cut_triggered()
{
    Clearlabel();
    int mpx0=mposx0;
    int mpy0=mposy0;
    int mpx1=mposx1;
    int mpy1=mposy1;
     if(!cmp(mpx0,mpy0,mpx1,mpy1))
     {
         std::swap(mpx0,mpx1);
         std::swap(mpy0,mpy1);
     }
     qDebug()<<"cnm"<<mpx0<<" "<<mpy0<<" "<<mpx1<<" "<<mpy1;
     Blockdelete(mpx0,mpy0,mpx1,mpy1);
     mposx1=mposx0=mpx0;
     mposy1=mposy0=mpy0;
     qDebug()<<mposx0<<"hahahha  "<<mposy0;
     mouse_row=mpx0;
     mouse_col=mpy0;
     Addlabel();

}

void MainWindow::on_Copy_triggered()
{
    Clearlabel();
    _clipboard="";
    int mpx0=mposx0;
    int mpy0=mposy0;
    int mpx1=mposx1;
    int mpy1=mposy1;
     if(!cmp(mpx0,mpy0,mpx1,mpy1))
     {
         std::swap(mpx0,mpx1);
         std::swap(mpy0,mpy1);
     }
     //qDebug()<<"wtf?\n";
     _clipboard=Blockcpy(mpx0,mpy0,mpx1,mpy1);
     qDebug()<<_clipboard<<"cnmaaaaaaaaaa";
     QClipboard *board = QApplication::clipboard();
      board->setText(_clipboard);
     Addlabel();
     qDebug()<<"!!!!!"<<_clipboard;
}

void MainWindow::on_Paste_triggered()
{
    if(mposx0!=mposx1||mposy0!=mposy1)on_Cut_triggered();
    //qDebug()<<mposx0<<" "<<mposy0<<" "<<mposx1<<" "<<mposy1<<"\n";
    //return;
    Clearlabel();
    qDebug()<<_clipboard<<"\n";
    Insert(mouse_row,mouse_col,_clipboard);
    //qDebug()<<headptr->get_store()<<" end?"<<"\n";
    mposx0=mposx1=mouse_row;
    mposy0=mposy1=mouse_col;
    Addlabel();
}

void MainWindow::on_SelectAll_triggered()
{
  Clearlabel();
 rowlist *temp=headptr;
 mposx0=0;
 mposy0=0;
 int i=0;
 while(temp->nextrowlistptr!=NULL){temp=temp->nextrowlistptr;i++;}
 mposx1=i;
 mposy1=temp->get_row_length();
 Addlabel();
}
/*
12
*/
