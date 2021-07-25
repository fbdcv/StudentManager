#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                          //QT设计师实现
    this->setWindowTitle(tr("终端管理系统"));

    ui->sexComboBox->clear();
    ui->sexComboBox->addItem(tr("男"));
    ui->sexComboBox->addItem(tr("女"));

    ui->ageSlider->setValue(18);
    ui->ageSlider->setRange(0,100);

    ui->agespinBox->setValue(18);
    ui->agespinBox->setRange(0,100);

    /***************使文件存在*****************************/
    if(!(fp=fopen("./words.txt","r")))      //打开或创建文件
    {
        fp=fopen("./words.txt","w");
    }
    fclose(fp);                             //关闭文件
    /***************************************************/
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchWords()));
    connect(ui->displayallButton,SIGNAL(clicked()),this,SLOT(displayAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAll()
{
    model->clear();
    word w;
    int t;
    int count=0;
    model->setHorizontalHeaderLabels({tr("学号"), tr("姓名"), tr("性别"), tr("年龄"), tr("班级"), tr("电话")});
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //自适应所有列，让它布满空间
    fp=fopen("./words.txt","r+");
    while(1)
    {
      t= fscanf(fp,"%s%s%s%s%s%s",w.no,w.name,w.sex,w.age,w.room,w.phone);
      //读到文件末，跳出循环
      if(t==EOF&&feof(fp)!=0)
          break;
       model->setItem(count,0,new QStandardItem(w.no));
       model->setItem(count,1,new QStandardItem(w.name));
       model->setItem(count,2,new QStandardItem(w.sex));
       model->setItem(count,3,new QStandardItem(w.age));
       model->setItem(count,4,new QStandardItem(w.room));
       model->setItem(count,5,new QStandardItem(w.phone));
       count++;
     }
    fclose(fp);
    ui->tableView->setModel(model);
    ui->tableView->show();

}

void MainWindow::searchWords()
{
        model->clear();
        word w;
        int t;
        int count=0;
        FILE *fp2;
        QString     no;
        QString 	name;
        QString     sex;
        QString 	age;
        QString 	room;
        QString     phone;
        fp2=fopen("./choice.txt","w");
        fprintf(fp2,"学号\t姓名\t性别\t年龄\t班级\t\t电话\n");
         model->setHorizontalHeaderLabels({tr("学号"), tr("姓名"), tr("性别"), tr("年龄"), tr("班级"), tr("电话")});
         /* 自适应所有列，让它布满空间 */
         ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        no      =   ui->cnoEdit->text();
        name    =   ui->nameEdit->text();
        sex     =   ui->sexComboBox->currentText();
        if(!(ui->sexcheckBox->isChecked()))
            sex.clear();
        age     =   QString::number(ui->agespinBox->value());
        if(!(ui->agecheckBox->isChecked()))
            age.clear();
        room    =   ui->roomEdit->text();
        phone   =   ui->phoneEdit->text();
        fp=fopen("./words.txt","r+");
      while(1)
        {
          t=fscanf(fp,"%s%s%s%s%s%s",w.no,w.name,w.sex,w.age,w.room,w.phone);
          if(t==EOF&&feof(fp)!=0)
              break;
          if(
                  ((no.isEmpty()||strcmp(no.toStdString().c_str(),w.no)==0)&&
                  (name.isEmpty()||strcmp(name.toStdString().c_str(),w.name)==0)&&
                  (sex.isEmpty()||strcmp(sex.toStdString().c_str(),w.sex)==0)&&
                  (age.isEmpty()||strcmp(age.toStdString().c_str(),w.age)==0)&&
                  (room.isEmpty()||strcmp(room.toStdString().c_str(),w.room)==0)&&
                  (phone.isEmpty()||strcmp(phone.toStdString().c_str(),w.phone)==0))
              &&
                  (!no.isEmpty()||!name.isEmpty()||!sex.isEmpty()||!age.isEmpty()||!room.isEmpty()||!phone.isEmpty())
              )
          {
              model->setItem(count,0,new QStandardItem(w.no));
              model->setItem(count,1,new QStandardItem(w.name));
              model->setItem(count,2,new QStandardItem(w.sex));
              model->setItem(count,3,new QStandardItem(w.age));
              model->setItem(count,4,new QStandardItem(w.room));
              model->setItem(count,5,new QStandardItem(w.phone));
             fprintf(fp2,"%s\t%s\t%s\t%s\t%s\t%s\n",w.no,w.name,w.sex,w.age,w.room,w.phone);
             count++;
         }
       }
        fclose(fp2);
        fclose(fp);
        ui->tableView->setModel(model);

        ui->tableView->show();
}
