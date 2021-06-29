#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("终端管理系统"));

    ui->sexComboBox->clear();
    ui->sexComboBox->addItem(tr("男"));
    ui->sexComboBox->addItem(tr("女"));

    ui->ageSlider->setValue(18);
    ui->ageSlider->setRange(0,100);

    ui->agespinBox->setValue(18);
    ui->agespinBox->setRange(0,100);


    if(!(fp=fopen("./words.txt","r")))
    {
        fp=fopen("./words.txt","w");
    }
    fclose(fp);
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchWords()));
    connect(ui->displayallButton,SIGNAL(clicked()),this,SLOT(displayAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAll()
{
    ui->textBrowser->clear();
    word w;
    QString     no;
    QString 	name;
    QString     sex;
    QString 	age;
    QString 	room;
    QString     phone;
    ui->textBrowser->insertPlainText("学号\t姓名\t性别\t年龄\t班级\t\t电话\n");
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
    while(!feof(fp))
    {
      fscanf(fp,"%s%s%s%s%s%s",w.no,w.name,w.sex,w.age,w.room,w.phone);
      fgetc(fp);
      if(feof(fp)!=0)
          break;
      ui->textBrowser->insertPlainText(w.no);     ui->textBrowser->insertPlainText("\t");
      ui->textBrowser->insertPlainText(w.name);   ui->textBrowser->insertPlainText("\t");
      ui->textBrowser->insertPlainText(w.sex);    ui->textBrowser->insertPlainText("\t");
      ui->textBrowser->insertPlainText(w.age);    ui->textBrowser->insertPlainText("\t");
      ui->textBrowser->insertPlainText(w.room);   ui->textBrowser->insertPlainText("  \t");
      ui->textBrowser->insertPlainText(w.phone);
      ui->textBrowser->insertPlainText("\n");
         ui->textBrowser->moveCursor(QTextCursor::End);
     }
    fclose(fp);
}

void MainWindow::searchWords()
{
        ui->textBrowser->clear();
        word w;
        FILE *fp2;
        fp2=fopen("./choice.txt","w");
        fprintf(fp2,"学号\t姓名\t性别\t年龄\t班级\t\t电话\n");
        QString     no;
        QString 	name;
        QString     sex;
        QString 	age;
        QString 	room;
        QString     phone;
        ui->textBrowser->insertPlainText("学号\t姓名\t性别\t年龄\t班级\t\t电话\n");
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
      while(!feof(fp))
        {
          fscanf(fp,"%s%s%s%s%s%s",w.no,w.name,w.sex,w.age,w.room,w.phone);
          fgetc(fp);
          if(feof(fp)!=0)
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
                ui->textBrowser->insertPlainText(w.no);     ui->textBrowser->insertPlainText("\t");
                ui->textBrowser->insertPlainText(w.name);   ui->textBrowser->insertPlainText("\t");
                ui->textBrowser->insertPlainText(w.sex);    ui->textBrowser->insertPlainText("\t");
                ui->textBrowser->insertPlainText(w.age);    ui->textBrowser->insertPlainText("\t");
                ui->textBrowser->insertPlainText(w.room);   ui->textBrowser->insertPlainText("  \t");
                ui->textBrowser->insertPlainText(w.phone);
                ui->textBrowser->insertPlainText("\n");
                fprintf(fp2,"%s\t%s\t%s\t%s\t%s\t%s\n",w.no,w.name,w.sex,w.age,w.room,w.phone);
                //qDebug()<<w.no<<w.name<<w.sex<<w.age<<w.room<<w.phone;
                ui->textBrowser->moveCursor(QTextCursor::End);
         }
       }
        fclose(fp2);
        fclose(fp);
}
