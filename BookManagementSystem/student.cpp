#include "student.h"

student::student(QSqlDatabase db, QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::student_window),
    database(db),
    student_name(name)
{
    ui->setupUi(this);
    ui->read_name->setText(name);
    QSqlQuery query(database);
    query.exec("select id from student where name = '" + student_name + "';");
    query.next();
    id = query.value(0).toString();
    ui->read_id->setText(id);
    //qDebug() << name << id;
}

student::~student()
{
    delete ui;
}

void student::on_pushButton_clicked()    // find books
{
    if(ui->find_bookid->text().indexOf("'") != -1 || ui->find_bookname->text().indexOf("'") != -1 || ui->find_press->text().indexOf("'") != -1 || ui->find_press->text().indexOf("'") != -1){
        QMessageBox::warning(this, tr("injection detected!"),
               tr("injection detected!\n""Contain ' in input!"),
               QMessageBox::Cancel);
        return;
    }


    QString sqlString = "select * from book where book_id like '%" + ui->find_bookid->text() + "%' and book_name like '%" +\
            ui->find_bookname->text() + "%' and author_name like '%" + ui->find_writer->text() + "%' and press_name like '%" + \
            ui->find_press->text() + "%';";
    qDebug() << sqlString;

    QSqlQuery query(database);
    if (!query.exec(sqlString))
    {
        qDebug() << query.lastError();
    }
    else
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        while(query.next())
        {
            QString book_id = query.value(0).toString();
            QString book_name = query.value(1).toString();
            QString author_name = query.value(2).toString();
            QString press_name = query.value(3).toString();
            float price = query.value(4).toFloat();
            int storage = query.value(5).toInt();
            int rowIndex = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(rowIndex+1);
            QTableWidgetItem *item = new QTableWidgetItem (book_id);
            ui->tableWidget->setItem(rowIndex, 0, item);
            item = new QTableWidgetItem (book_name);
            ui->tableWidget->setItem(rowIndex, 1, item);
            item = new QTableWidgetItem (author_name);
            ui->tableWidget->setItem(rowIndex, 2, item);
            item = new QTableWidgetItem (press_name);
            ui->tableWidget->setItem(rowIndex, 3, item);
            item = new QTableWidgetItem (QString("%1").arg(price));
            ui->tableWidget->setItem(rowIndex, 4, item);
            item = new QTableWidgetItem (QString("%1").arg(storage));
            ui->tableWidget->setItem(rowIndex, 5, item);
        }


    }


}

