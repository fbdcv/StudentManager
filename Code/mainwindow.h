#ifndef MAINWINDOW_H    //如果没有宏定义了MAINWINDOW_H，执行以下程序
/***************************************************************/
#define MAINWINDOW_H

#include<cstdio>
#include<cstring>
#include <QMainWindow>              //主界面头文件
#include<QtWidgets>                 //部件头文件

#define word_no			20
#define word_name 		16
#define word_age		4
#define word_sex		5
#define word_room		40
#define word_phone		15

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }    //建立命名空间Ui，防止类命名冲突（防止其他不同的MainWindow类）
QT_END_NAMESPACE

class word
{
public:
    char	no[word_no];
    char 	name[word_name];
    char	sex[word_sex];
    char 	age[word_age];
    char 	room[word_room];
    char	phone[word_phone];
};

class MainWindow : public QMainWindow
{
    Q_OBJECT                        //QT中的包含信号-槽实现的宏

private slots:                      //槽函数
    void searchWords();
    void displayAll();
public:
    MainWindow(QWidget *parent = nullptr);  //c++中 null是0的宏，而nullptr是((void*)0)的宏
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FILE* fp;
    QStandardItemModel* model = new QStandardItemModel; //创建一个标准的条目模型
};

/***************************************************************/
#endif // MAINWINDOW_H宏定义判定完毕
