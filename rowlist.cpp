#include "rowlist.h"
#include <qdebug.h>
unit::unit()
{
    store=new QChar[100];
    unit_length=0;

}
unit::~unit()
{
    delete store;
}
unit::unit(const unit &r)
{
    store=new QChar[100];
    unit_length=r.unit_length;
    for(int i=1;i<=unit_length;i++)
     store[i-1]=r.store[i-1];
}
void unit::init(QString str,int &st)
{
    int strlength=str.length();
     for(unit_length=1;unit_length<=100;unit_length++)
    {
        store[unit_length-1]=str[st++];
        if(st==strlength)break;
    }
     if(unit_length==101)unit_length--;
     //qDebug()<<store;
}
QChar unit::get_lastword()
{
    return store[unit_length-1];
}
QChar unit::get_firstword()
{
    return store[0];
}
int unit::get_length()
{
    return unit_length;
}
void unit::_insert(int pos,QChar ch)
{
    int i;
    for(i=pos;i<unit_length;i++)
    {
        QChar temp=ch;
        ch=store[i];
        store[i]=temp;

    }
    if(i<100)
     {
      unit_length++;
      store[i]=ch;
    }
}
void unit::_delete_unit(int pos,QChar ch)
{
    for(int i=pos;i<unit_length-1;i++)
    {
        store[i]=store[i+1];
    }
    store[unit_length-1]=ch;
}
void unit::_delete_last_unit(int pos)
{
    if(pos==(unit_length-1))
        unit_length--;
    else
    {
        for(int i=pos;i<=unit_length-2;i++)
        {
            store[i]=store[i+1];
        }
        unit_length--;
    }

}
QString unit::get_store()
{
    QString s="";
    for(int i=0;i<unit_length;i++)
    s+=store[i];
    return s;
}

rowlist::rowlist()
{
    label = new myqlabel;
    row_length=unit_num=0;
    vecunit.clear();
    nextrowlistptr=NULL;
}
rowlist::~rowlist()
{
    delete label;
}
int rowlist::get_unit_num()
{
    return unit_num;
}
void rowlist::rowlist_init(QString s)
{
    int init_index=0;
    row_length=s.length();
    unit_num=(row_length/100)+(row_length%100!=0);
    init_index=0;
    for(int i=0;i<unit_num;i++)
    {
        unit *unit_to_add=new unit;
        unit_to_add->init(s,init_index);
        vecunit.push_back(*unit_to_add);
    }
    QStore="";
    for(int i=0;i<unit_num;i++)
    QStore+=vecunit[i].get_store();
    label->setText(QStore);
}
void rowlist::_insert(QChar insert_char, int insert_position){
    int insert_unit=insert_position/100;
    int insert_index=insert_position%100;
    if(unit_num==0)
    {
        unit *newnunit=new unit;
        vecunit.push_back(*newnunit);
        unit_num++;
    }
    if(insert_char!='\r')
    {
        QChar lastword=insert_char;
        bool flag=0;
       // qDebug()<<"store[0]="<<vecunit[0].get_store()<<"\n";
        if(vecunit[unit_num-1].get_length()==100)
        {
            unit *unit_to_add=new unit;
            vecunit.push_back(*unit_to_add);
            unit_num++;
        }

        for(int i=insert_unit;i<unit_num;i++)
        {

           // qDebug()<<"unit_num="<<unit_num<<"\n";
            QChar temp='\0';
            if(i<=unit_num-2)
            {temp=vecunit[i].get_lastword();
             //qDebug()<<"temp="<<temp<<"\n";
             //qDebug()<<"lastword="<<lastword<<"\n";
            }

            vecunit[i]._insert(insert_index,lastword);
            //qDebug()<<"firstword="<<vecunit[i].get_firstword()<<"\n";
            insert_index=0;
            lastword=temp;
        }
        int init_index=0;
        ++row_length;
        QStore="";
        for(int i=0;i<unit_num;i++)
        {
            //qDebug()<<"store="<<vecunit[i].get_store()<<"\n";
            QStore+=vecunit[i].get_store();

        }
        //mouse_col=insert_position+1;
    }
    else
    {
        rowlist* rowlist_to_add=new rowlist;
        QString add_string="";
        for(int i=insert_position;i<row_length;i++)
        {
            add_string+=QStore[i];
        }
        rowlist_to_add->rowlist_init(add_string);
        rowlist_to_add->nextrowlistptr=nextrowlistptr;
        nextrowlistptr=rowlist_to_add;
        int delete_time=row_length;
        for(int i=insert_position;i<delete_time;i++)
        {
            _delete(insert_position);
        }

        QStore="";
        for(int i=0;i<unit_num;i++)
        QStore+=vecunit[i].get_store();
    }
   label->setText(QStore);
}

   void rowlist::_delete(int delete_position)//delete backward
   {

      //qDebug()<<"delete!";
      int delete_unit=delete_position/100;
      int delete_index=delete_position%100;
      if(delete_position<row_length)
      {
          qDebug()<<delete_position<<" "<<row_length<<"henhen"<<QStore;
          bool flag=0;
          if(vecunit[unit_num-1].get_length()==1)flag=1;
          if(delete_unit!=unit_num-1)
          {
              QChar firstword=vecunit[delete_unit+1].get_firstword();
              vecunit[delete_unit]._delete_unit(delete_index,firstword);
              for(int i=delete_unit+1;i<unit_num-1;i++)
              {
                   firstword=vecunit[i+1].get_firstword();
                   vecunit[i]._delete_unit(0,firstword);
              }
              if(flag)
              {
                  vecunit.erase(vecunit.begin()+unit_num-1);
                  unit_num--;

                 //
              }
          }
          else
          {
             // qDebug()<<"pipippipip\n";
              vecunit[delete_unit]._delete_last_unit(delete_index);

              if(vecunit[delete_unit].get_length()==0)
              {vecunit.erase(vecunit.begin()+unit_num-1);unit_num--;}

          }
          row_length--;
      }
      else//row gather
      {
          if(nextrowlistptr!=NULL)
          {
              int j=nextrowlistptr->get_row_length();
              for(int i=0;i<j;i++)
              {
                  QChar insert_char=nextrowlistptr->vecunit[0].get_firstword();
                  _insert(insert_char,row_length);

                  nextrowlistptr->_delete(0);
              }
               //mouse_col=delete_position;
              _delete_next_row();
              //rowlist_num--;
          }
      }
      QStore="";
      for(int i=0;i<unit_num;i++)
      {

          QStore+=vecunit[i].get_store();
      }
      label->setText(QStore);
   }
   void rowlist::_backspace(int backspace_position,rowlist* exptr)//delete forward
   {
       //qDebug()<<"backspace!";
       if(backspace_position==0)
       {if(exptr!=NULL)exptr->_delete(exptr->get_row_length());
       }
       else
       {
           _delete(backspace_position-1);
       }

   }
   int rowlist::find_string(int index,QString s)
   {
       qDebug()<<"find_string work";
       QString t="";

       for(int i=index;i<row_length;i++)
       {
           t+=QStore[i];
       }
       int tlength=t.length();
       int slength=s.length();
       int next[100];
       next[0] = -1;
       int i,j;
       //build next[100]
           for (i=1;i<tlength;i++)
           {
               j=next[i-1];
               while (t[j+1]!=t[i]&&(j>=0))
               {
                   j=next[j];
               }
               if (t[i]==t[j+1])
               {
                   next[i]=j+1;
               }
               else
               {
                   next[i]=-1;
               }
           }
           //start finding
           int s_i=0,t_i=0;

           while (s_i<slength&&t_i<tlength)
           {
               if (s[s_i]==t[t_i])
               {
                   s_i++;
                   t_i++;
               }
               else
               {
                   if (s_i==0)
                   {
                       t_i++;
                   }
                   else
                   {
                       s_i=next[s_i-1]+1;
                   }
               }
           }

           if (s_i==slength)
              {mouse_col=t_i - slength+index;
               return t_i - slength+index;}

           else
               return -1;
   }
   int rowlist::exchange_string(int index, QString exstring, QString newstring)
   {
       QString t="";

       for(int i=index;i<row_length;i++)
       {
           t+=QStore[i];
       }
       int tlength=t.length();
       int exstringlength=exstring.length();
       int next[100];
       next[0] = -1;
       int i,j;
       //build next[100]
           for (i=1;i<tlength;i++)
           {
               j=next[i-1];
               while (t[j+1]!=t[i]&&(j>=0))
               {
                   j=next[j];
               }
               if (t[i]==t[j+1])
               {
                   next[i]=j+1;
               }
               else
               {
                   next[i]=-1;
               }
           }
           //start finding
           int s_i=0,t_i=0;

           while (s_i<exstringlength&&t_i<tlength)
           {
               if (exstring[s_i]==t[t_i])
               {
                   s_i++;
                   t_i++;
               }
               else
               {
                   if (s_i==0)
                   {
                       t_i++;
                   }
                   else
                   {
                       s_i=next[s_i-1]+1;
                   }
               }
           }
           int exchange_index;
           if (s_i==exstringlength)
           {
                 exchange_index=t_i - exstringlength+index;
                 for(int i=0;i<exstringlength;i++)
                 {
                     _delete(exchange_index);
                 }
                 int newstring_length=newstring.length();
                 for(int i=0;i<newstring_length;i++)
                 {
                     _insert(newstring[i],exchange_index+i);
                 }
                 mouse_col=exchange_index;
                 return exchange_index;
           }

           else
           {
               exchange_index=-1;
               return -1;
           }


   }
