#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("book management system");
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("127.0.0.1");    //数据库主机名
    db.setDatabaseName("bookmanagement");    //数据库名
    db.setUserName("root");        //数据库用户名
    db.setPassword("qwertyui");        //数据库密码
    bool ok=db.open();
    if(ok)
    {
        //qDebug()<<"open database success";
    }
    else
    {
        //qDebug()<<"error open database because";
    }
    //QSqlQuery query(db);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   // 学生登录
{

    if (ui->stu_id_text->text().isEmpty() || ui->stu_password->text().isEmpty())
    {
        QMessageBox::warning(this, tr("injection detected!"),
           tr("Please input your name and password!"),
           QMessageBox::Cancel);
        return;
    }
    QSqlQuery query(db);
    if (ui->stu_id_text->text().indexOf("'") != -1 || ui->stu_password->text().indexOf("'") != -1){   // sql injection
        QMessageBox::warning(this, tr("injection detected!"),
           tr("injection detected!\n""Contain ' in input!"),
           QMessageBox::Cancel);
        return;
    }
    //qDebug() << "select password from student where name = '" + ui->stu_id_text->text() + "';";
    query.exec("select password from student where name = '" + ui->stu_id_text->text() + "';");
    query.next();
    if (ui->stu_password->text() == query.value(0).toString())
    {
        this->hide();
        student *stu_window = new student(db, ui->stu_id_text->text());
        stu_window->show();
        return;
    }

    QMessageBox::warning(this, tr("injection detected!"),
       tr("Wrong student name or wrong password!"),
       QMessageBox::Cancel);

}

void MainWindow::on_pushButton_2_clicked()    // 管理员登录
{
    if (ui->manager_name->text().isEmpty() || ui->manager_password->text().isEmpty())
    {
        QMessageBox::warning(this, tr("injection detected!"),
           tr("Please input your name and password!"),
           QMessageBox::Cancel);
        return;
    }
    QSqlQuery query(db);
    if (ui->stu_id_text->text().indexOf("'") != -1 || ui->stu_password->text().indexOf("'") != -1){   // sql injection
        QMessageBox::warning(this, tr("injection detected!"),
           tr("injection detected!\n""Contain ' in input!"),
           QMessageBox::Cancel);
        return;
    }
    query.exec("select password from admin where name = '" + ui->manager_name->text() + "';");
    query.next();
    if(ui->manager_password->text() == query.value(0).toString())
    {
        this->hide();
        qDebug() << "manager";
        manager *man_window = new manager(db, ui->manager_name->text(), this);
        man_window->show();
        return;
    }
}


void MainWindow::on_reg_clicked()   // 注册
{
    if (ui->reg_name->text().isEmpty() || ui->reg_id->text().isEmpty() || ui->reg_grade->text().isEmpty() || ui->reg_password->text().isEmpty() || ui->reg_password_rep->text().isEmpty())
    {
        QMessageBox::warning(this, tr("injection detected!"),
           tr("Please input all the blanks!"),
           QMessageBox::Cancel);
        return;
    }
    if (ui->reg_name->text().indexOf("'") != -1 || ui->reg_id->text().indexOf("'") != -1 || ui->reg_password->text().indexOf("'") != -1 || ui->reg_password_rep->text().indexOf("'") != -1 || ui->reg_grade->text().indexOf("'") != -1){   // sql injection
        QMessageBox::warning(this, tr("injection detected!"),
           tr("injection detected!\n""Contain ' in input!"),
           QMessageBox::Cancel);
        return;
    }
    if (ui->reg_password->text() != ui->reg_password_rep->text());
    QString sqlString;
    sqlString = "insert into student values('" + ui->reg_name->text() + "', '" + ui->reg_id->text() + "', " + ui->reg_grade->text() + ", '" + ui->reg_password->text() + "');";
    QSqlQuery query(db);
    if (!query.exec(sqlString))
    {
        qDebug() << query.lastError();
        QString error = query.lastError().text();
        QByteArray errorx = error.toLatin1();
        QMessageBox::warning(this, tr("Error!"),
               tr(errorx.data()),
               QMessageBox::Cancel);
        return;
    }
    else{
        QMessageBox::information(this, tr("Success!"),
               tr("register successed!"),
               QMessageBox::Cancel);
        return;
    }
}
