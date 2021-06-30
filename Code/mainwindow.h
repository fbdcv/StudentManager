#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<cstdio>
#include<cstring>
#include <QMainWindow>
#include<QtWidgets>

#define word_no			20
#define word_name 		16
#define word_age		4
#define word_sex		5
#define word_room		40
#define word_phone		15

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
    Q_OBJECT

private slots:
    void searchWords();
    void displayAll();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FILE* fp;
    QStandardItemModel* model = new QStandardItemModel; //创建一个标准的条目模型
};
#endif // MAINWINDOW_H
