#include "manager.h"

manager::manager(QSqlDatabase db, QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager_window),
    database(db),
    manager_name(name)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin");
    on_find_clicked(1);
    update_student_list();
    update_loan_list(ui->if_only_unreturn->isTristate());
}

manager::~manager()
{
    delete ui;
}

void manager::on_add_clicked()
{
    if(ui->find_bookid->text().isEmpty() || ui->find_bookname->text().isEmpty() || ui->find_press->text().isEmpty() || ui->find_writer->text().isEmpty() || ui->find_price->text().isEmpty() || ui->find_storage->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Empty!"),
               tr("Please fill in all the blanks!"),
               QMessageBox::Cancel);
        return;
    }

    QString sqlString;
    sqlString = "insert into book values('" + ui->find_bookid->text() + "', '" + ui->find_bookname->text() + "', '" + ui->find_writer->text() + "', '" \
            + ui->find_press->text() + "', " + ui->find_price->text() + ", " + ui->find_storage->text() + ");";
    QSqlQuery query(database);
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
    on_find_clicked(1);

}

void manager::on_find_clicked(int x)
{
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
        QString error = query.lastError().text();
        QByteArray errorx = error.toLatin1();
        QMessageBox::warning(this, tr("Error!"),
               tr(errorx.data()),
               QMessageBox::Cancel);
        return;
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

void manager::on_delete_book_clicked()
{
    QString sqlString;
    sqlString = "delete from book where book_id = '" + ui->delete_book_id->text() + "';";
    QSqlQuery query(database);
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
    on_find_clicked(1);
}


void manager::update_student_list()
{
    QString sqlString;
    sqlString = "select * from student";


    QSqlQuery query(database);
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
    else
    {
        ui->student_table->clearContents();
        ui->student_table->setRowCount(0);
        while(query.next())
        {
            QString stu_name = query.value(0).toString();
            QString stu_id = query.value(1).toString();
            int stu_grade = query.value(2).toInt();
            QString password = query.value(3).toString();

            int rowIndex = ui->student_table->rowCount();
            ui->student_table->setRowCount(rowIndex+1);
            QTableWidgetItem *item = new QTableWidgetItem (stu_name);
            ui->student_table->setItem(rowIndex, 0, item);
            item = new QTableWidgetItem (stu_id);
            ui->student_table->setItem(rowIndex, 1, item);
            item = new QTableWidgetItem (QString("%1").arg(stu_grade));
            ui->student_table->setItem(rowIndex, 2, item);
            item = new QTableWidgetItem (password);
            ui->student_table->setItem(rowIndex, 3, item);
        }


    }
}

void manager::on_delete_stu_clicked()
{
    QString sqlString;
    QSqlQuery query(database);

    if (ui->delete_stu_name->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Input name!"),
               tr("Please input the name of the student you want to delete!"),
               QMessageBox::Cancel);
        return;
    }

    //first delete from student table
    sqlString = "delete from student where name = '" + ui->delete_stu_name->text() + "';";
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

    //second updata table from loan
    sqlString = "delete from loan where stu_name = '" + ui->delete_stu_name->text() + "';";
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
    update_student_list();

}


void manager::update_loan_list(int unreturn)
{
    QString sqlString;
    QSqlQuery query(database);
    if (unreturn)
    {
        sqlString = "select * from loan natural join book where return_time is NULL;";
    }
    else{
        sqlString = "select * from loan natural join book;";
    }
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

    else
    {
        ui->loan_table->clearContents();
        ui->loan_table->setRowCount(0);
        while(query.next())
        {
            QString loan_id = query.value(0).toString();
            QString book_id = query.value(1).toString();
            QString book_name = query.value(2).toString();
            int storage = query.value(9).toInt();
            float price = query.value(8).toFloat();
            QString stu_name = query.value(3).toString();
            QString borrow_time = query.value(4).toString();
            QString return_time = query.value(5).toString();

            int rowIndex = ui->loan_table->rowCount();
            ui->loan_table->setRowCount(rowIndex+1);
            QTableWidgetItem *item = new QTableWidgetItem (loan_id);
            ui->loan_table->setItem(rowIndex, 0, item);
            item = new QTableWidgetItem (book_id);
            ui->loan_table->setItem(rowIndex, 1, item);
            item = new QTableWidgetItem (book_name);
            ui->loan_table->setItem(rowIndex, 2, item);
            item = new QTableWidgetItem (QString("%1").arg(storage));
            ui->loan_table->setItem(rowIndex, 3, item);
            item = new QTableWidgetItem (QString("%1").arg(price));
            ui->loan_table->setItem(rowIndex, 4, item);
            item = new QTableWidgetItem (stu_name);
            ui->loan_table->setItem(rowIndex, 5, item);
            item = new QTableWidgetItem (borrow_time);
            ui->loan_table->setItem(rowIndex, 6, item);
            item = new QTableWidgetItem (return_time);
            ui->loan_table->setItem(rowIndex, 7, item);
        }
    }

}

void manager::on_if_only_unreturn_clicked(bool checked)
{
    update_loan_list(checked);
}
