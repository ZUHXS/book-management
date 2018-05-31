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
    this->on_fresh_borrow_clicked();
    this->on_pushButton_clicked(1);
    //qDebug() << name << id;
}

student::~student()
{
    delete ui;
}

void student::on_pushButton_clicked(int x)    // find books
{
    if(ui->find_bookid->text().indexOf("'") != -1 || ui->find_bookname->text().indexOf("'") != -1 || ui->find_press->text().indexOf("'") != -1 || ui->find_writer->text().indexOf("'") != -1){
        QMessageBox::warning(this, tr("injection detected!"),
               tr("injection detected!\n""Contain ' in input!"),
               QMessageBox::Cancel);
        return;
    }
    QString sqlString;
    if (x == 1)    // used for initialize
    {
        sqlString = "select * from book;";
    }
    else{     // used when x is 0
    sqlString = "select * from book where book_id like '%" + ui->find_bookid->text() + "%' and book_name like '%" +\
            ui->find_bookname->text() + "%' and author_name like '%" + ui->find_writer->text() + "%' and press_name like '%" + \
            ui->find_press->text() + "%';";
    }
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


void student::on_fresh_borrow_clicked()
{
    QString sqlString = "select * from loan where stu_name = '" + student_name + "';";
    qDebug() << sqlString;
    QSqlQuery query(database);
    if (!query.exec(sqlString))
    {
        qDebug() << query.lastError();
    }
    else
    {
        ui->tableWidget_2->clearContents();
        ui->tableWidget_2->setRowCount(0);
        while(query.next())
        {
            QString book_id = query.value(1).toString();
            QString book_name = query.value(2).toString();
            QString borrow_time = query.value(4).toString();
            QString return_time = query.value(5).toString();
            int rowIndex = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->setRowCount(rowIndex+1);
            QTableWidgetItem *item = new QTableWidgetItem (book_id);
            ui->tableWidget_2->setItem(rowIndex, 0, item);
            item = new QTableWidgetItem (book_name);
            ui->tableWidget_2->setItem(rowIndex, 1, item);
            item = new QTableWidgetItem (borrow_time);
            ui->tableWidget_2->setItem(rowIndex, 2, item);
            item = new QTableWidgetItem (return_time);
            ui->tableWidget_2->setItem(rowIndex, 3, item);
        }
    }
}

void student::on_borrow_clicked()
{
    QString sqlString = "select count(load_id) from loan";
    QSqlQuery query(database);
    int loan_number;
    if (!query.exec(sqlString))
    {
        qDebug() << query.lastError();
    }
    else{
        query.next();
        loan_number = query.value(0).toInt();
        qDebug() << loan_number;
    }
    if(ui->borrow_bookid->text().indexOf("'") != -1){
        QMessageBox::warning(this, tr("injection detected!"),
               tr("injection detected!\n""Contain ' in input!"),
               QMessageBox::Cancel);
        return;
    }

    // first check if have borrowed this book
    sqlString = "select * from loan where stu_name = '" + student_name + "' and book_id = '" + ui->borrow_bookid->text() + "' and return_time is NULL;";
    qDebug() << sqlString;
    if(!query.exec(sqlString))
    {
        QString error = query.lastError().text();
        QByteArray errorx = error.toLatin1();
        QMessageBox::warning(this, tr("Book not found!"),
               tr(errorx.data()),
               QMessageBox::Cancel);
        return;
    }
    else{
        if (query.next())
        {
            QMessageBox::warning(this, tr("Book not found!"),
                   tr("You have already borrowed this book! Return first!"),
                   QMessageBox::Cancel);
            return;
        }
    }



    sqlString = "select book_name from book where book_id = '" + ui->borrow_bookid->text() + "';";
    QString book_name;
    query.exec(sqlString);
    if (!query.next()){
        QString error = query.lastError().text();
        QByteArray errorx = error.toLatin1();
        QMessageBox::warning(this, tr("Book not found!"),
               tr("Book not Found! Check first!"),
               QMessageBox::Cancel);
        return;
    }

    else{
        book_name = query.value(0).toString();
        qDebug() << book_name;
    }

    QDateTime timestamp = QDateTime::currentDateTime();
    timestamp.addDays(1);
    QString time = timestamp.toString("yyyy-MM-dd hh:mm:ss");

    sqlString = "insert into loan values('" + QString::number(loan_number+1) + "', '" +
            ui->borrow_bookid->text() + "', '" + book_name + "', '" + student_name + "', '" + time + "', NULL);";
    qDebug() << sqlString;
    query.exec(sqlString);
    this->on_fresh_borrow_clicked();

}

void student::on_ret_clicked()
{
    QDateTime timestamp = QDateTime::currentDateTime();
    timestamp.addDays(1);
    QString time = timestamp.toString("yyyy-MM-dd hh:mm:ss");

    QString sqlString = "update loan set return_time = '" + time + "' where book_id = '" + ui->return_bookid->text() + "' and stu_name = '" + student_name + "' and return_time is NULL;";
    qDebug() << sqlString;
    QSqlQuery query(database);
    query.exec(sqlString);
    this->on_fresh_borrow_clicked();
}
