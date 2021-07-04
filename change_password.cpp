#include "change_password.h"
#include "ui_change_password.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

change_password::change_password(QString &id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
    patient_id=id;
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_pushButton_clicked()
{
    if(ui->lineEdit->text()!=ui->lineEdit_2->text())
        QMessageBox::information(this,"提示", "两次密码输入不一致，请重新输入");
    else
    {
        QSqlQuery sql_query;
        QString alter_sql=QString("ALTER USER '%1'@'localhost' IDENTIFIED BY '%2' ").arg(patient_id,ui->lineEdit->text());

        bool ok=sql_query.exec(alter_sql);
        if(ok)
            QMessageBox::information(this,"成功", "修改成功！");
        else
            QMessageBox::information(this,"错误", "修改失败！");
    }
}

void change_password::on_pushButton_2_clicked()
{
    this->close();
}
