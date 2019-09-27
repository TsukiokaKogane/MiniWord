#include "rowlist.h"
#include <QApplication>
#include "main.h"
#include "mainwindow.h"
rowlist *headptr=NULL;
int mouse_row,mouse_col,rowlist_num,mposx0,mposy0,mposx1,mposy1;
bool file_is_saved=1;
QString _clipboard="";
bool cmp(int x0,int y0,int x1,int y1)
{
    return x1>x0||x1==x0&&y1>=y0;
}
void vecrowlist_clear()
{

    rowlist *temp=NULL;
    while(headptr!=NULL)
    {
        temp=headptr->nextrowlistptr;
        delete headptr;
        headptr=temp;
    }
    headptr=temp=NULL;

}
void vecrowlist_init(QString allstring)
{

   rowlist* temp=NULL,*currentptr=NULL;
   vecrowlist_clear();
   mouse_row=mouse_col=rowlist_num=0;
   int length=allstring.length();
   int index=0;
   QString tempstring="";
   while(index!=length)
   {

       if(allstring[index]!='\n')
       {
           tempstring+=allstring[index];

       }
       else
       {
           qDebug()<<"insert "<<tempstring<<"\n";
         rowlist_num++;
           temp=new rowlist;
           temp->rowlist_init(tempstring);
           if(headptr==NULL)headptr=temp;
           else currentptr->nextrowlistptr=temp;
           currentptr=temp;
           currentptr->nextrowlistptr=NULL;
           tempstring="";

       }
       index++;
   }
   if(tempstring!="")
   {
       rowlist_num++;
       temp=new rowlist;
       temp->rowlist_init(tempstring);
       if(headptr==NULL)headptr=temp;
       else currentptr->nextrowlistptr=temp;
       currentptr=temp;
       currentptr->nextrowlistptr=NULL;
       tempstring="";

   }
   if(headptr==NULL){headptr=new rowlist;rowlist_num++;}
}
int get_rowlen(int x)
{
    rowlist *temp=headptr;
    while(x)
    {
       temp=temp->nextrowlistptr;
        x--;
    }
    return temp->get_row_length();
}
void Insert(int x,int y, QString str)
{
    rowlist *temp=headptr,*exptr=NULL;
    while(x)
    {
        exptr=temp;
        temp=temp->nextrowlistptr;
        x--;
    }
    QChar temp_char;
    int str_length=str.length();
     rowlist *newrow=new rowlist;
    for(int i=0;i<str_length;i++)
    {
        temp_char=str[i];
        if(temp_char!='\r'&&temp_char!='\n') {mouse_col++;temp->_insert(temp_char,y);y++;}
        else
        {
         rowlist_num++;
         mouse_row++;
         if(y==temp->get_row_length())
         {

             newrow->nextrowlistptr=temp->nextrowlistptr;
             temp->nextrowlistptr=newrow;
             temp=newrow;
             mouse_col=0;
             y=0;
              continue;
         }
         else  if(y==0)
         {
           if(exptr!=NULL)exptr->nextrowlistptr=newrow;
           else headptr=newrow;
           newrow->nextrowlistptr=temp;
           mouse_col=0;
           continue;
         }
         else
         {
             int j=0;

             for(int k=y;k<temp->get_row_length();k++)
             {
                 //puts("yes?");
                 QChar tc=temp->get_store()[k];
                 //qDebug()<<"ch="<<tc<<"\n";
                 newrow->_insert(tc,j++);

             }
             while(temp->get_row_length()>y)
             {
                 qDebug()<<"haha"<<temp->get_store()[y-1]<<"\n";
                 temp->_delete(y);
                 qDebug()<<"lala"<<temp->get_store()<<"\n";

             }
             newrow->nextrowlistptr=temp->nextrowlistptr;
             temp->nextrowlistptr=newrow;
             exptr=temp;
             temp=newrow;
            // qDebug()<<"quaquuququ"<<exptr->get_store();
            // rowlist_num++;
             mouse_col=0;
             y=0;
         }
        }
    }
    qDebug()<<"afssafag"<<rowlist_num<<"\n";

}
void Delete(int x,int y)
{
    file_is_saved=0;
    rowlist *temp=headptr;
        while(x)
        {
            temp=temp->nextrowlistptr;
            x--;
        }
        temp->_delete(y);
}
void Backspace(int x,int y)
{
    file_is_saved=0;
    if(y)
    {
        Delete(x,y-1);
        mouse_col--;
    }
    else if(x)
    {
       int nx=x-1,ny=get_rowlen(x-1);
        Delete(nx,ny);
        mouse_row=nx;
        mouse_col=ny;
    }

   /* rowlist *temp=headptr;
    rowlist *extemp=NULL;
    qDebug()<<"1 "<<x<<" "<<y<<"\n";
    if(!x&&!y)return;
    while(x)
    {
        extemp=temp;
        temp=temp->nextrowlistptr;
        x--;
    }
    int backspace_position=y,pre_len=0;
    if(extemp!=NULL) pre_len=extemp->get_row_length();
    temp->_backspace(backspace_position,extemp);
    if(mouse_col)mouse_col--;
    else if(mouse_row){mouse_row--;mouse_col=pre_len;rowlist_num--;}
    //qDebug()<<"2 "<<mouse_row<<" "<<mouse_col<<"\n";
    */
}
int ch2_eng1(int x,int y)
{
    int count=0;
    rowlist *temp=headptr;
   // if(temp==NULL)return 0;
    while(x)
    {
        temp=temp->nextrowlistptr;
        x--;
    }
    for(int i=0;i<y;i++)
    {
        QChar cha = temp->get_store()[i];
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            count+=2;
        }
        else
        {
            count+=1;
        }
    }
    return count;
}
int inverse_ch2_eng1(int x,int num)
{
    rowlist *temp=headptr;
    while(x)
    {
        temp=temp->nextrowlistptr;
        x--;
    }
    int i=0;
    while(num!=0&&i<temp->get_row_length())
    {
        QChar cha = temp->get_store()[i];
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            num-=2;
        }
        else
        {
            num-=1;
        }
        ++i;
        if(num<0)
        {--i;
         break;
        }
    }
    qDebug()<<"i="<<i<<"\n";
    return i;
}
QString Blockcpy(int x1,int y1,int x2,int y2)
{
   qDebug()<<"blockcpy work!";
    QString s="";
    int x=x1;
    //qDebug()<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
    rowlist *temp=headptr;
    while(x)
    {
        temp=temp->nextrowlistptr;
        x--;
    }
    if(x1==x2)
    {
     for(int i=y1;i<y2;i++)
     {
         s+=temp->get_store()[i];
     }
     return s;
    }
   for(int i=y1;i<temp->get_row_length();i++)
    {
        s+=temp->get_store()[i];
    }
   // qDebug()<<s<<" ?fkff?\n";

    x=x1+1;
    temp=temp->nextrowlistptr;
    s+="\r";
    while(x<x2)
    {
        s+=temp->get_store();
        s+="\r";
        x++;
        temp=temp->nextrowlistptr;
    }

    //temp=temp->nextrowlistptr;
    for(int i=0;i<y2;i++)
    {
         s+=temp->get_store()[i];
    }
    qDebug()<<_clipboard<<"what happenned?";
    return s;
}
void Blockdelete(int x1, int y1, int x2, int y2)
{
    qDebug()<<"here\n";
    mouse_row=x2;mouse_col=y2;
    while(1)
    {   if(mouse_row==x1&&mouse_col==y1)break;
        qDebug()<<mouse_row<<" "<<mouse_col<<"\n";
        puts("!");
        Backspace(mouse_row,mouse_col);
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MiniWord");
    w.show();
    return a.exec();
}
/*
1

3
*/
