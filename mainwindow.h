#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>
#include<QLayout>
#include<QAction>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QTextCodec>
#include<QEvent>
#include<QKeyEvent>
#include<QTextEdit>
#include<QScrollBar>
#include<QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Clearlabel();
    void Addlabel();
    QString t1,t2;


private slots:

    void contextMenuEvent(QContextMenuEvent *event);
    void on_Openfile_triggered();
    void on_Statusbar_triggered(bool);
    void on_Savefile_triggered();
    void on_Newfile_triggered();
    void on_AboutMiniWord_triggered();
    void on_Exit_triggered();
    void on_Delete_triggered();
    void getFilename(QString);
    void on_Find_triggered();
    void on_Replace_triggered();
    void Find_t(QString);
    void Replace_t(QString,QString);

    void on_Cut_triggered();

    void on_Copy_triggered();

    void on_Paste_triggered();

    void on_SelectAll_triggered();

protected:
     void mouseDoubleClickEvent(QMouseEvent *);
     void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
     void keyPressEvent(QKeyEvent *);
     void inputMethodEvent(QInputMethodEvent*);
     void setInitMode();
     void setEditMode();
     void setClipboard();
     bool eventFilter(QObject *, QEvent *);

private:
   Ui::MainWindow *ui;
   QVBoxLayout *Layout;
   QMenu *pop_menu;
   QString filepath,filename;
   QLabel *slabel;

};

#endif // MAINWINDOW_H
