#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    qDebug() << "select password from student where name = '" + ui->stu_id_text->text() + "';";
    query.exec("select password from student where name = '" + ui->stu_id_text->text() + "';");
    query.next();
    if (ui->stu_password->text() == query.value(0).toString())
    {
        this->hide();
        student *stu_window = new student(db);
        stu_window->show();
        return;
    }

    QMessageBox::warning(this, tr("injection detected!"),
       tr("Wrong student name or wrong password!"),
       QMessageBox::Cancel);

}
