#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>
#include <QTableView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //设定QLineEdit的输入限制和提示

    //需要的正则表达式
    QRegExp regx_patient_id("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][X0-9]+$");
    QRegExp regx_chinese("[\u4e00-\u9fa5]+$");
    QRegExp regx_phone("[0-9]+$");
    QRegExp regx_id("[a-zA-Z0-9]+$");
    QRegExp regx_address("[\u4e00-\u9fa50-9-]+$");



    //-------------------------添加病人窗口-------------------------

    //身份证号的限制和提示
    QValidator *validator_id_1 = new QRegExpValidator(regx_patient_id, ui->LINE_ID);
    ui->LINE_ID->setValidator(validator_id_1);
    ui->LINE_ID->setPlaceholderText(tr("若需输入X请输入大写"));
    //姓名的限制
    QValidator *validator_name_1 = new QRegExpValidator(regx_chinese, ui->LINE_NAME);
    ui->LINE_NAME->setValidator(validator_name_1);
    //联系电话的限制
    QValidator *validator_phone_1 = new QRegExpValidator(regx_phone, ui->LINE_PHONE);
    ui->LINE_PHONE->setValidator(validator_phone_1);
    ui->LINE_PHONE->setPlaceholderText(tr("请输入11位手机号"));
    //家庭住址的限制
    QValidator *validator_address_1 = new QRegExpValidator(regx_address, ui->LINE_ADDRESS);
    ui->LINE_ADDRESS->setValidator(validator_address_1);

    //-------------------------添加医生窗口-------------------------

    //ID的限制和提示
    QValidator *validator_id_2 = new QRegExpValidator(regx_id, ui->LINE_ID_2);
    ui->LINE_ID_2->setValidator(validator_id_2);
    ui->LINE_ID_2->setPlaceholderText(tr("请输入不超过10位的医生ID"));
    //姓名的限制
    QValidator *validator_name_2 = new QRegExpValidator(regx_chinese, ui->LINE_NAME_2);
    ui->LINE_NAME_2->setValidator(validator_name_2);
    //联系电话的限制
    QValidator *validator_phone_2 = new QRegExpValidator(regx_phone, ui->LINE_PHONE_2);
    ui->LINE_PHONE_2->setValidator(validator_phone_2);
    ui->LINE_PHONE_2->setPlaceholderText(tr("请输入11位手机号"));

    //-------------------------处方开立窗口-------------------------

    //ID的限制和提示
    QValidator *validator_id_3 = new QRegExpValidator(regx_id, ui->LINE_ID_3);
    ui->LINE_ID_3->setValidator(validator_id_3);
    ui->LINE_ID_3->setPlaceholderText(tr("请输入不超过20位的处方ID"));

    //-------------------------检查项目开立窗口-------------------------

    //ID的限制和提示
    QValidator *validator_id_4 = new QRegExpValidator(regx_id, ui->LINE_ID_4);
    ui->LINE_ID_4->setValidator(validator_id_4);
    ui->LINE_ID_4->setPlaceholderText(tr("请输入不超过20位的检查项目ID"));

    //-------------------------病人缴费窗口-------------------------

    //ID的限制和提示
    QValidator *validator_id_6 = new QRegExpValidator(regx_id, ui->LINE_ID_6);
    ui->LINE_ID_6->setValidator(validator_id_6);
    ui->LINE_ID_6->setPlaceholderText(tr("请输入不超过20位的流水账单ID"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//-------------------------添加病人-------------------------


void MainWindow::on_add_patients_clicked()
{


    /*if(ui->LINE_ID->text().size()!=18)
        QMessageBox::information(this,"提示", "请输入18位身份证号");
    */

    add_patients AP;
    //获取病人信息
    AP.setPatient_id(ui->LINE_ID->text());
    AP.setPatient_name(ui->LINE_NAME->text());
    AP.setPatient_sex(ui->COMBOBOX_SEX->currentText());
    AP.setPatient_age(ui->SPINBOX_AGE->value());
    AP.setPatient_phone(ui->LINE_PHONE->text());
    AP.setPatient_address(ui->LINE_ADDRESS->text());
    AP.setStart_time();
    AP.setPatient_sickroom(ui->LINE_SICKROOM->text());
    AP.setPatient_bed(ui->SPINBOX_BED->value());
    AP.setPatient_account(ui->DOUBLESPINBOX_ACCOUNT->value());
    AP.setDoctor_id(ui->LINE_DOCTOR->text());


    /*QSqlQuery transaction_start;
    QSqlQuery transaction_COMMIT;
    QSqlQuery transaction_ROLLBACK;
    QSqlQuery query_insert;
    QSqlQuery query_delete;

    transaction_start.exec("START TRANSACTION");//开始事务。使用BEGIN也可以
    bool ok1=AP.insertDataToPatient();
    bool ok2=AP.insertDataToPatient_doctor();
    bool ok3=AP.updateSickroom();
    qDebug()<<ok1<<ok2<<ok3;
    if(ok1 && ok2 &&ok3)
    {
        transaction_COMMIT.exec("COMMIT");//提交
    }else
    {
        transaction_ROLLBACK.exec("ROLLBACK");//回滚
    }*/


    if(ui->LINE_ID->text().size()!=18)
    {
        QMessageBox::information(this,"提示", "请输入正确的身份证号");
        goto L1;
    }
    if(ui->SPINBOX_AGE->value()==0)
    {
        QMessageBox::information(this,"提示", "请输入正确的年龄");
        goto L1;
    }
    if(ui->LINE_PHONE->text().size()!=11)
    {
        QMessageBox::information(this,"提示", "请输入正确的手机号");
        goto L1;
    }
    if(ui->SPINBOX_BED->value()==0)
    {
        QMessageBox::information(this,"提示", "请选择正确的床位号");
        goto L1;
    }


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;   //记录错误信息

        //执行下面各种数据库操作
        bool ok1=AP.createPatient_user();
        if(!ok1)
            errorMessage=AP.sql_query.lastError().text();
        bool ok2=AP.grantToUser();
        if(!ok2)
            errorMessage=AP.sql_query.lastError().text();
        bool ok3=AP.setToUser();
        if(!ok3)
            errorMessage=AP.sql_query.lastError().text();

        bool ok4=AP.insertDataToPatient();
        if(!ok4)
            errorMessage=AP.sql_query.lastError().text();
        bool ok5=AP.insertDataToPatient_doctor();
        if(!ok5)
            errorMessage=AP.sql_query.lastError().text();
        bool ok6=AP.updateSickroom();
        if(!ok6)
            errorMessage=AP.sql_query.lastError().text();




        qDebug()<<ok1<<ok2<<ok3<<ok4<<ok5<<ok6;

        if(ok1 && ok2 && ok3 && ok4 && ok5 && ok6)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "添加成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "添加失败：" + errorMessage);
        }

        /*
        if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "添加失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
        {
            QMessageBox::information(this,"成功", "添加成功！");
        }*/

    }

    /*
    //执行插入的SQL语句
    if(!AP.insertDataToPatient())
        QMessageBox::warning(this,"错误", "添加失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    if(!AP.insertDataToPatient_doctor())
        QMessageBox::warning(this,"错误", "添加失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    if(!AP.updateSickroom())
        QMessageBox::warning(this,"错误", "更新失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");*/

L1: ;

}

void MainWindow::on_select_department_name_clicked()
{
    display_department* DD=new display_department;
    DD->show();
    connect(DD, SIGNAL(sendDepartment_nameToAdd_patients(QString)), this, SLOT(receiveDepartment_name(QString)));
}

void MainWindow::receiveDepartment_name(QString data)
{
    ui->LINE_DEPARTMENT->setText(data);     //获取选择的科室名
}

void MainWindow::on_select_sickroom_clicked()
{
    if(ui->LINE_DEPARTMENT->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择科室");
    else
    {
        display_sickrooms* DS=new display_sickrooms;

        connect(DS, SIGNAL(sendSickroom_id(QString)), this, SLOT(receiveSickroom_id(QString))); //连接DS窗口选择的病房号和主窗口的病房号
        connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DS, SLOT(receiveDepartment_nameFromMainwindow(QString))); //连接主窗口的科室名和DS窗口的科室名

        emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT->text());   //传递主窗口中已经选择好的科室名

        DS->show();
    }
}

void MainWindow::receiveSickroom_id(QString data)
{
    ui->LINE_SICKROOM->setText(data);     //获取传递过来的病房号
}

void MainWindow::on_select_bed_clicked()
{
    if(ui->LINE_SICKROOM->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择病房");
    else
    {
        display_beds* DB=new display_beds;
        connect(this, SIGNAL(sendSickroom_id(QString)), DB, SLOT(receiveSickroom_id(QString)));
        emit sendSickroom_id(ui->LINE_SICKROOM->text());           //传递病房的id
        DB->show();
        connect(DB, SIGNAL(sendBed(int)), this, SLOT(receiveBed(int)));
        DB->judge();
    }
}

void MainWindow::receiveBed(int data)
{
    ui->SPINBOX_BED->setValue(data);     //获取传递过来的数据
}

void MainWindow::on_select_doctor_clicked()
{
    if(ui->LINE_DEPARTMENT->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择科室");
    else
    {
        display_doctors* DD=new display_doctors;
        connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DD, SLOT(receiveDepartment_name(QString)));
        emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT->text());   //传递主窗口中已经选择好的科室名
        DD->show();
        connect(DD, SIGNAL(sendDoctor_id(QString)), this, SLOT(receiveDoctor_id(QString)));
    }
}

void MainWindow::receiveDoctor_id(QString data)
{
    ui->LINE_DOCTOR->setText(data);     //获取传递过来的数据
}



//-------------------------添加医生-------------------------


void MainWindow::on_add_doctors_clicked()
{
    add_doctors AD;
    //获取医生信息
    AD.setDoctor_id(ui->LINE_ID_2->text());
    AD.setDoctor_name(ui->LINE_NAME_2->text());
    AD.setDoctor_sex(ui->COMBOBOX_SEX_2->currentText());
    AD.setDoctor_age(ui->SPINBOX_AGE_2->value());
    AD.setDoctor_phone(ui->LINE_PHONE_2->text());
    AD.setDoctor_department(ui->LINE_DEPARTMENT_2->text());
    AD.setDoctor_professional(ui->COMBOBOX_PRO->currentText());



    if(ui->SPINBOX_AGE_2->value()==0)
    {
        QMessageBox::information(this,"提示", "请输入正确的年龄");
        goto L1;
    }
    if(ui->LINE_PHONE_2->text().size()!=11)
    {
        QMessageBox::information(this,"提示", "请输入正确的手机号");
        goto L1;
    }


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;
        //下面执行各种数据库操作
        bool ok=AD.insertDataToDoctor();
        if(!ok)
            errorMessage=AD.sql_query.lastError().text();

        if(ok)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "添加成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "添加失败：" + errorMessage);
        }





        /*
        if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "添加失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
            QMessageBox::information(this,"成功", "添加成功！");*/
    }


    /*
    //向doctor表中添加信息
    if(!AD.insertDataToDoctor())
        QMessageBox::warning(this,"错误", "添加失败：" + AD.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");*/
L1: ;
}

void MainWindow::on_select_department_clicked()
{
    display_department* DD=new display_department;
    DD->show();
    connect(DD, SIGNAL(sendDepartment_nameToAdd_patients(QString)), this, SLOT(receiveDepartment_id(QString)));
}

void MainWindow::receiveDepartment_id(QString data)
{
    ui->LINE_DEPARTMENT_2->setText(data);     //获取传递过来的数据
}


//-------------------------处方开立-------------------------



void MainWindow::on_add_prescriptions_clicked()
{
    add_prescriptions AP;
    //获取处方信息
    AP.setPrescription_id(ui->LINE_ID_3->text());
    AP.setPrescription_content(ui->CONTENT_TEXT_3->toPlainText());
    AP.setDoctor_id(ui->LINE_DOCTOR_3->text());
    AP.setPatient_id(ui->LINE_PATIENT_3->text());
    AP.setCost(ui->DOUBLESPINBOX_COST->value());


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;
        //下面执行各种数据库操作
        bool ok1=AP.insertDataToPrescription();
        if(!ok1)
            errorMessage=AP.sql_query.lastError().text();
        bool ok2=AP.insertDataToPatient_prescription();
        if(!ok2)
            errorMessage=AP.sql_query.lastError().text();
        bool ok3=AP.updatePatient();
        if(!ok3)
            errorMessage=AP.sql_query.lastError().text();


        if(ok1 && ok2 && ok3)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "处方开立成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "处方开立失败：" + errorMessage);
        }


        /*if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "处方开立失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
            QMessageBox::information(this,"成功", "处方开立成功！");*/
    }

    /*
    //向prescription表中添加信息
    if(!AP.insertDataToPrescription())
        QMessageBox::warning(this,"错误", "添加失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    //向patient_prescription表中添加信息
    if(!AP.insertDataToPatient_prescription())
        QMessageBox::warning(this,"错误", "添加失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    //向patient表中更新信息
    if(!AP.updatePatient())
        QMessageBox::warning(this,"错误", "更新失败：" + AP.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");
    */
}

void MainWindow::on_select_department_3_clicked()
{
    display_department* DD=new display_department;
    DD->show();
    connect(DD, SIGNAL(sendDepartment_nameToAdd_patients(QString)), this, SLOT(receiveDepartment_name_3(QString)));
}

void MainWindow::receiveDepartment_name_3(QString data)
{
    ui->LINE_DEPARTMENT_3->setText(data);
}


void MainWindow::on_select_doctor_3_clicked()
{
    display_doctors* DD=new display_doctors;

    connect(DD, SIGNAL(sendDoctor_id(QString)), this, SLOT(receiveDoctor_id_3(QString)));
    connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DD, SLOT(receiveDepartment_name(QString))); //连接主窗口的科室名和DD窗口的科室名
    emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT_3->text());   //传递主窗口中已经选择好的科室名

    DD->show();
}

void MainWindow::receiveDoctor_id_3(QString data)
{
    ui->LINE_DOCTOR_3->setText(data);     //获取传递过来的数据
}

void MainWindow::on_select_patient_3_clicked()
{
    display_patients* DP=new display_patients;

    connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DP, SLOT(receiveDepartment_name(QString))); //连接主窗口的科室名和DP窗口的科室名
    connect(DP, SIGNAL(sendPatient_id(QString)), this, SLOT(receivePatient_id_3(QString)));
    emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT_3->text());   //传递主窗口中已经选择好的科室名

    DP->show();
}

void MainWindow::receivePatient_id_3(QString data)
{
    ui->LINE_PATIENT_3->setText(data);     //获取传递过来的数据
}





//-------------------------检查项目开立-------------------------



void MainWindow::on_add_inspection_items_clicked()
{
    add_inspection_items AI;
    //获取检查项目信息
    AI.setInspection_id(ui->LINE_ID_4->text());
    AI.setInspection_content(ui->CONTENT_TEXT_4->toPlainText());
    AI.setPatient_id(ui->LINE_PATIENT_4->text());
    AI.setPlace(ui->LINE_PLACE_4->text());
    AI.setCost(ui->DOUBLESPINBOX_COST_4->value());


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;
        //下面执行各种数据库操作
        bool ok1=AI.insertDataToInspection_items();
        if(!ok1)
            errorMessage=AI.sql_query.lastError().text();
        bool ok2=AI.insertDataToPatient_inspection();
        if(!ok2)
            errorMessage=AI.sql_query.lastError().text();
        bool ok3=AI.updatePatient();
        if(!ok3)
            errorMessage=AI.sql_query.lastError().text();



        if(ok1 && ok2 && ok3)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "检查项目开立成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "检查项目开立失败：" + errorMessage);
        }



        /*
        if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "检查项目开立失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
            QMessageBox::information(this,"成功", "检查项目开立成功！");*/
    }

    /*
    //向inspection_items表中添加信息
    if(!AI.insertDataToInspection_items())
        QMessageBox::warning(this,"错误", "添加失败：" + AI.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    //向patient_inspection表中添加信息
    if(!AI.insertDataToPatient_inspection())
        QMessageBox::warning(this,"错误", "添加失败：" + AI.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    //向patient表中更新信息
    if(!AI.updatePatient())
        QMessageBox::warning(this,"错误", "更新失败：" + AI.sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");
    */
}

void MainWindow::on_select_department_4_clicked()
{
    display_department* DD=new display_department;
    DD->show();
    connect(DD, SIGNAL(sendDepartment_nameToAdd_patients(QString)), this, SLOT(receiveDepartment_name_4(QString)));
}

void MainWindow::receiveDepartment_name_4(QString data)
{
    ui->LINE_DEPARTMENT_4->setText(data);
}

void MainWindow::on_select_patient_4_clicked()
{
    display_patients* DP=new display_patients;
    connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DP, SLOT(receiveDepartment_name(QString))); //连接主窗口的科室名和DP窗口的科室名
    connect(DP, SIGNAL(sendPatient_id(QString)), this, SLOT(receivePatient_id_4(QString)));
    emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT_4->text());   //传递主窗口中已经选择好的科室名
    DP->show();

}

void MainWindow::receivePatient_id_4(QString data)
{
    ui->LINE_PATIENT_4->setText(data);    //获取传递过来的数据
}



//-------------------------病人转科室-------------------------


void MainWindow::on_select_patient_5_cur_clicked()
{
    show_patients* SP=new show_patients;
    SP->show();
    connect(SP, SIGNAL(sendPatient_id(QString)), this, SLOT(receivePatient_id_5(QString)));
}

void MainWindow::receivePatient_id_5(QString data)
{
    ui->LINE_PATIENT_ID_5->setText(data);     //获取传递过来的数据

    QString doctor_id;
    //补充剩余信息
    QSqlQuery query;
    QString select_str = QString("select id,name,sex,age,sickroom_id,bed_id,doctor_id from patient,patient_doctor where id='%1' and patient_doctor.patient_id=id ").arg(data);
    query.exec(select_str);
    while(query.next())
    {
        ui->LINE_PATIENT_NAME_5->setText(query.value(1).toString());
        ui->LINE_PATIENT_SEX_5->setText(query.value(2).toString());
        ui->SPINBOX_AGE_5->setValue(query.value(3).toInt());
        ui->LINE_SICKROOM_5_CUR->setText(query.value(4).toString());
        ui->SPINBOX_BED_5_CUR->setValue(query.value(5).toInt());
        doctor_id=query.value(6).toString();
    }

    QSqlQuery query_;
    QString select_str_ = QString("select doctor.id,doctor.name,department.id,department.name from doctor,department where doctor.id='%1' and doctor.department=department.id ").arg(doctor_id);
    query_.exec(select_str_);
    while(query_.next())
    {
        ui->LINE_DOCTOR_ID_5_CUR->setText(query_.value(0).toString());
        ui->LINE_DOCTOR_NAME_5_CUR->setText(query_.value(1).toString());
        ui->LINE_DEPARTMENT_ID_5_CUR->setText(query_.value(2).toString());
        ui->LINE_DEPARTMENT_NAME_5_CUR->setText(query_.value(3).toString());
    }
}

void MainWindow::on_select_department_5_tar_clicked()
{
    display_department* DD=new display_department;
    DD->show();
    connect(DD, SIGNAL(sendDepartment_nameToAdd_patients(QString)), this, SLOT(receiveDepartment_name_5(QString)));
}

void MainWindow::receiveDepartment_name_5(QString data)
{
    ui->LINE_DEPARTMENT_5_TAR->setText(data);
}

void MainWindow::on_select_sickroom_5_tar_clicked()
{
    if(ui->LINE_DEPARTMENT_5_TAR->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择科室");
    else
    {
        display_sickrooms* DS=new display_sickrooms;

        connect(DS, SIGNAL(sendSickroom_id(QString)), this, SLOT(receiveSickroom_id_5(QString))); //连接DS窗口选择的病房号和主窗口的病房号
        connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DS, SLOT(receiveDepartment_nameFromMainwindow(QString))); //连接主窗口的科室名和DS窗口的科室名

        emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT_5_TAR->text());   //传递主窗口中已经选择好的科室名

        DS->show();
    }
}

void MainWindow::receiveSickroom_id_5(QString data)
{
    ui->LINE_SICKROOM_5_TAR->setText(data);     //获取传递过来的病房号
}


void MainWindow::on_select_bed_5_tar_clicked()
{
    if(ui->LINE_SICKROOM_5_TAR->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择病房");
    else
    {
        display_beds* DB=new display_beds;
        connect(this, SIGNAL(sendSickroom_id(QString)), DB, SLOT(receiveSickroom_id(QString)));
        emit sendSickroom_id(ui->LINE_SICKROOM_5_TAR->text());           //传递病房的id
        DB->show();
        connect(DB, SIGNAL(sendBed(int)), this, SLOT(receiveBed_5(int)));
        DB->judge();
    }
}

void MainWindow::receiveBed_5(int data)
{
    ui->SPINBOX_BED_5_TAR->setValue(data);     //获取传递过来的数据
}

void MainWindow::on_select_doctor_5_tar_clicked()
{
    if(ui->LINE_DEPARTMENT_5_TAR->text()==NULL)
         QMessageBox::information(this,"提示", "请先选择科室");
    else
    {
        display_doctors* DD=new display_doctors;
        connect(this, SIGNAL(sendDepartment_nameToAdd_patients(QString)), DD, SLOT(receiveDepartment_name(QString)));
        emit sendDepartment_nameToAdd_patients(ui->LINE_DEPARTMENT_5_TAR->text());   //传递主窗口中已经选择好的科室名
        DD->show();
        connect(DD, SIGNAL(sendDoctor_id(QString)), this, SLOT(receiveDoctor_id_5(QString)));
    }
}

void MainWindow::receiveDoctor_id_5(QString data)
{
    ui->LINE_DOCTOR_5_TAR->setText(data);     //获取传递过来的数据
}

void MainWindow::on_change_department_clicked()
{
    change_department* CD=new change_department;

    //获取转科室需要的相关信息
    CD->setPatient_id(ui->LINE_PATIENT_ID_5->text());
    CD->setPatient_name(ui->LINE_PATIENT_NAME_5->text());
    CD->setPatient_sex(ui->LINE_PATIENT_SEX_5->text());
    CD->setPatient_age(ui->SPINBOX_AGE_5->value());

    CD->setPatient_sickroom_cur(ui->LINE_SICKROOM_5_CUR->text());
    CD->setPatient_bed_cur(ui->SPINBOX_BED_5_CUR->value());
    CD->setDoctor_id_cur(ui->LINE_DOCTOR_ID_5_CUR->text());
    CD->setDepartment_id_cur(ui->LINE_DEPARTMENT_ID_5_CUR->text());

    CD->setDepartment_name_tar(ui->LINE_DEPARTMENT_5_TAR->text());
    CD->setPatient_sickroom_tar(ui->LINE_SICKROOM_5_TAR->text());
    CD->setPatient_bed_tar(ui->SPINBOX_BED_5_TAR->value());
    CD->setDoctor_id_tar(ui->LINE_DOCTOR_5_TAR->text());


    if(ui->SPINBOX_BED_5_TAR->value()==0)
    {
        QMessageBox::information(this,"提示", "请选择正确的床位号");
        goto L1;
    }


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;
        //下面执行各种数据库操作
        bool ok1=CD->updatePatient();
        if(!ok1)
            errorMessage=CD->update_query.lastError().text();
        bool ok2=CD->updatePatient_doctor();
        if(!ok2)
            errorMessage=CD->update_query.lastError().text();
        bool ok3=CD->updateSickroom_cur();
        if(!ok3)
            errorMessage=CD->update_query.lastError().text();
        bool ok4=CD->updateSickroom_tar();
        if(!ok4)
            errorMessage=CD->update_query.lastError().text();


        if(ok1 && ok2 && ok3 && ok4)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "转科室成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "转科室失败：" + errorMessage);
        }



        /*
        if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "转科室失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
            QMessageBox::information(this,"成功", "转科室成功！");*/
    }

    /*
    //向patient表中更新信息
    if(!CD->updatePatient())
        QMessageBox::warning(this,"错误", "更新失败：" + CD->update_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");

    //向patient_doctor表中更新信息
    if(!CD->updatePatient_doctor())
        QMessageBox::warning(this,"错误", "更新失败：" + CD->update_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");

    //向sickroom表中更新信息
    if(!CD->updateSickroom_cur())
        QMessageBox::warning(this,"错误", "更新失败：" + CD->update_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");
    if(!CD->updateSickroom_tar())
        QMessageBox::warning(this,"错误", "更新失败：" + CD->update_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");
    */
L1: ;
}



//-------------------------病人缴费-------------------------


void MainWindow::on_select_patient_6_clicked()
{
    show_patients* SP=new show_patients;
    SP->show();
    connect(SP, SIGNAL(sendPatient_id(QString)), this, SLOT(receivePatient_id_6(QString)));
}

void MainWindow::receivePatient_id_6(QString data)
{
    ui->LINE_PATIENT_6->setText(data);     //获取传递过来的数据

    //查询账户余额
    QSqlQuery query;
    QString select_str = QString("select account from patient where id='%1' ").arg(data);
    query.exec(select_str);
    while(query.next())
        ui->LINE_ACCOUNT_6->setText(query.value(0).toString());
}

void MainWindow::on_pay_clicked()
{
    add_payments* AP=new add_payments;

    //获取病人缴费需要的相关信息
    AP->setPayment_id(ui->LINE_ID_6->text());
    AP->setPatient_id(ui->LINE_PATIENT_6->text());
    AP->setMoney(ui->DOUBLESPINBOX_PAY_6->value());


    if(QSqlDatabase::database().transaction()) //启动事务操作
    {
        QString errorMessage;
        //下面执行各种数据库操作
        bool ok1=AP->insertPayment();
        if(!ok1)
            errorMessage=AP->sql_query.lastError().text();
        bool ok2=AP->insertPatient_payment();
        if(!ok2)
            errorMessage=AP->sql_query.lastError().text();
        bool ok3=AP->updatePatient();
        if(!ok3)
            errorMessage=AP->sql_query.lastError().text();


        if(ok1 && ok2 &&ok3)
        {
            if(!QSqlDatabase::database().commit())
            {
                QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
            }

            QMessageBox::information(this,"成功", "缴费成功！");
        }
        else
        {
            //开始回滚
            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

            QMessageBox::warning(this,"错误", "缴费失败：" + errorMessage);
        }


        /*
        if(!QSqlDatabase::database().commit())//提交失败，开始回滚
        {
            QMessageBox::warning(this,"错误", "缴费失败：" + QSqlDatabase::database().lastError().text());

            if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
        }
        else
            QMessageBox::information(this,"成功", "缴费成功！");*/
    }

    /*
    //向payment表中插入信息
    if(!AP->insertPayment())
        QMessageBox::warning(this,"错误", "添加失败：" + AP->sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "添加成功！");

    //向patient表中更新信息
    if(!AP->updatePatient())
        QMessageBox::warning(this,"错误", "更新失败：" + AP->sql_query.lastError().text());
    else
        QMessageBox::information(this,"成功", "更新成功！");
    */
}



//-------------------------病人出院-------------------------

void MainWindow::on_select_patient_7_clicked()
{
    show_patients* SP=new show_patients;
    SP->show();
    connect(SP, SIGNAL(sendPatient_id(QString)), this, SLOT(receivePatient_id_7(QString)));
}

void MainWindow::receivePatient_id_7(QString data)
{
    ui->LINE_PATIENT_7->setText(data);     //获取传递过来的数据

    //查询账户余额
    QSqlQuery query;
    QString select_str = QString("select start_time,account from patient where id='%1' ").arg(data);
    query.exec(select_str);
    while(query.next())
    {
        ui->START_TIME->setDateTime(query.value(0).toDateTime());
        ui->LINE_ACCOUNT_7->setText(query.value(1).toString());
        ui->LEAVE_TIME->setDateTime(QDateTime::currentDateTime());
    }
}

void MainWindow::on_leave_hospital_clicked()
{
    double account=ui->LINE_ACCOUNT_7->text().toDouble();
    if(account<0)
    {
        QString needToPay=ui->LINE_ACCOUNT_7->text();
        needToPay.remove("-");  //删除字符串中的负号
        QMessageBox::information(this,"提示", "当前账户欠费" + needToPay + "元，请缴费后办理出院");
    }
    else
    {
        //退回账户剩余的金额
        if(account>0)
            QMessageBox::information(this,"提示", "当前账户剩余" + ui->LINE_ACCOUNT_7->text() + "元，即将退回");

        leave_hospital LH;
        LH.setPatient_id(ui->LINE_PATIENT_7->text());
        LH.setAmount(account);

        //相关表的删除和更新

        if(QSqlDatabase::database().transaction()) //启动事务操作
        {
            QString errorMessage;
            //下面执行各种数据库操作
            bool ok1=LH.deletePatient_doctor();
            if(!ok1)
                errorMessage=LH.sql_query.lastError().text();
            bool ok2=LH.deletePatient_inspection();
            if(!ok2)
                errorMessage=LH.sql_query.lastError().text();
            bool ok8=LH.deletePatient_prescription();
            if(!ok8)
                errorMessage=LH.sql_query.lastError().text();
            bool ok3=LH.deletePatient_payment();
            if(!ok3)
                errorMessage=LH.sql_query.lastError().text();
            bool ok4=LH.updateSickroom();
            if(!ok4)
                errorMessage=LH.sql_query.lastError().text();
            bool ok5=LH.deletePatient();    //注意删除顺序（考虑外码约束）
            if(!ok5)
                errorMessage=LH.sql_query.lastError().text();

            bool ok6=true;
            if(account>0)
            {
                ok6=LH.insertPayback();
                if(!ok6)
                    errorMessage=LH.sql_query.lastError().text();
            }

            bool ok7=LH.dropUser();

            if(ok1 && ok2 && ok3 && ok4 &&ok5 && ok6 &&ok7 &&ok8)
            {
                if(!QSqlDatabase::database().commit())
                {
                    QMessageBox::warning(this,"错误", "提交失败：" + QSqlDatabase::database().lastError().text());

                    //开始回滚
                    if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                        QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());
                }

                QMessageBox::information(this,"成功", "出院成功！祝您身体健康！");
            }
            else
            {
                //开始回滚
                if(!QSqlDatabase::database().rollback())    //回滚失败，输出错误信息
                    QMessageBox::warning(this,"错误", "回滚失败：" + QSqlDatabase::database().lastError().text());

                QMessageBox::warning(this,"错误", "出院失败：" + errorMessage);
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
    LoginWindow* LW=new LoginWindow;
    LW->show();
}

//-----------------------------重置---------------------------------

void MainWindow::on_add_patients_2_clicked()
{
    ui->LINE_ID->clear();
    ui->LINE_NAME->clear();
    //ui->COMBOBOX_SEX->clear();
    ui->SPINBOX_AGE->setValue(0);
    ui->LINE_PHONE->clear();
    ui->LINE_ADDRESS->clear();
    ui->LINE_DEPARTMENT->clear();
    ui->LINE_SICKROOM->clear();
    ui->SPINBOX_BED->setValue(0);
    ui->DOUBLESPINBOX_ACCOUNT->setValue(0);
    ui->LINE_DOCTOR->clear();
}

void MainWindow::on_add_doctors_2_clicked()
{
    ui->LINE_ID_2->clear();
    ui->LINE_NAME_2->clear();
    //ui->COMBOBOX_SEX->clear();
    ui->SPINBOX_AGE_2->setValue(0);
    ui->LINE_PHONE_2->clear();
    ui->LINE_DEPARTMENT_2->clear();
}

void MainWindow::on_add_prescriptions_2_clicked()
{
    ui->LINE_ID_3->clear();
    ui->CONTENT_TEXT_3->clear();
    ui->LINE_DEPARTMENT_3->clear();
    ui->LINE_DOCTOR_3->clear();
    ui->LINE_PATIENT_3->clear();
    ui->DOUBLESPINBOX_COST->setValue(0);
}

void MainWindow::on_add_inspection_items_2_clicked()
{
    ui->LINE_ID_4->clear();
    ui->CONTENT_TEXT_4->clear();
    ui->LINE_DEPARTMENT_4->clear();
    ui->LINE_PATIENT_4->clear();
    ui->LINE_PLACE_4->clear();
    ui->DOUBLESPINBOX_COST->setValue(0);
}

void MainWindow::on_change_department_2_clicked()
{
    ui->LINE_PATIENT_ID_5->clear();
    ui->LINE_PATIENT_NAME_5->clear();
    ui->LINE_PATIENT_SEX_5->clear();
    ui->SPINBOX_AGE_5->setValue(0);
    ui->LINE_SICKROOM_5_CUR->clear();
    ui->SPINBOX_BED_5_CUR->setValue(0);
    ui->LINE_DOCTOR_ID_5_CUR->clear();
    ui->LINE_DOCTOR_NAME_5_CUR->clear();
    ui->LINE_DEPARTMENT_ID_5_CUR->clear();
    ui->LINE_DEPARTMENT_NAME_5_CUR->clear();
    ui->LINE_DEPARTMENT_5_TAR->clear();
    ui->LINE_SICKROOM_5_TAR->clear();
    ui->SPINBOX_BED_5_TAR->setValue(0);
    ui->LINE_DOCTOR_5_TAR->clear();
}

void MainWindow::on_pay_2_clicked()
{
    ui->LINE_ID_6->clear();
    ui->LINE_PATIENT_6->clear();
    ui->LINE_ACCOUNT_6->clear();
    ui->DOUBLESPINBOX_PAY_6->setValue(0);
}

void MainWindow::on_leave_hospital_2_clicked()
{
    ui->LINE_PATIENT_7->clear();
    ui->LINE_ACCOUNT_7->clear();

    QString s = "2000/01/01 00:00";
    QDateTime time = QDateTime::fromString(s,"yyyy/MM/dd hh:mm");
    ui->START_TIME->setDateTime(time);
    ui->LEAVE_TIME->setDateTime(time);
}
