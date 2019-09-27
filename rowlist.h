#ifndef _ROWLIST_H
#define _ROWLIST_H
#include <QString>
#include<QLabel>
#include "myqlabel.h"
extern int mouse_row,mouse_col,rowlist_num,block_x1,block_y1,block_x2,block_y2;
class unit
{
    public:

    unit();
    ~unit();
    unit(const unit&);
    void init(QString str,int &st);
    QChar get_lastword();
    QChar get_firstword();
    int get_length();
    void _insert(int pos,QChar ch);
    void _delete_unit(int pos,QChar ch);
    void _delete_last_unit(int pos);
    QString get_store();
    private:
    QChar *store;
    int unit_length;

};
class rowlist
{
    public:
    myqlabel *label;
    rowlist();
    ~rowlist();
    void rowlist_init(QString s);
    int get_unit_num();
    void _insert(QChar insert_char, int insert_position);
    void _delete(int delete_position);//delete backward
    void _backspace(int backspace_position,rowlist* exptr);//delete forward
    void _delete_next_row()
    {
        nextrowlistptr=nextrowlistptr->nextrowlistptr;
        --rowlist_num;
    }
    void _add_row(int n);
    int find_string(int index,QString s);
    int exchange_string(int index, QString exstring, QString newstring);
    int get_row_length()
    {
        return row_length;
    }
    QString get_store()
    {
        return QStore;
    }
    rowlist* nextrowlistptr;
    private:
    std::vector<unit> vecunit;
    QString QStore;
    int row_length;
    int unit_num;

};

#endif // ROWLIST_H
