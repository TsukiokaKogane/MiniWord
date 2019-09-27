#ifndef _MAIN_H
#define _MAIN_H
void vecrowlist_clear();
void vecrowlist_init(QString allstring);
int get_rowlen(int x);
void Insert(int x,int y, QString str);
void Delete(int x,int y);
void Backspace(int x,int y);
int ch2_eng1(int x,int y);
int inverse_ch2_eng1(int x,int num);
QString Blockcpy(int x1,int y1,int x2,int y2);
void Blockdelete(int x1,int y1,int x2,int y2);//块删除
bool cmp(int x0,int y0,int x1,int y1);
#endif // MAIN_H
