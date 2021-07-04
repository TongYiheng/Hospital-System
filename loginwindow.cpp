#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "patientwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);

    QRegExp regx("[a-zA-Z0-9]+$");
    QValidator *validator_user = new QRegExpValidator(regx, ui->userText);
    ui->userText->setValidator(validator_user);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    //ui->userText->setText("root");
    //ui->passwordText->setText("root123456");

    QString username=ui->userText->text();
    QString password=ui->passwordText->text();

    if(username==""||password=="")
    {
        QMessageBox::warning(this,"错误","用户名或密码不能为空");
    }
    else
    {//使用MySQL数据库驱动，连接数据库

        QSqlDatabase database;
        database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName("localhost");
        database.setDatabaseName("hospitalsystem");
        database.setUserName(username);
        database.setPassword(password);
        database.setPort(3306);

        bool ok = database.open();
        if(ok)
        {
            this->close();

            //判定是root用户
            //显示mainWindow窗口
            if(username.size()==4)
            {
                MainWindow* mw=new MainWindow;
                mw->show();
            }


            //判定是patient用户
            //显示patientwindow窗口
            if(username.size()==18)
            {
                patientwindow* pw=new patientwindow(username);
                pw->show();
            }

        }
        else
        {
            QMessageBox::warning(this,"错误","用户名不存在或密码错误");
        }
    }
}

void LoginWindow::on_pushButton_2_clicked()
{
    this->close();  //关闭本窗口
}
