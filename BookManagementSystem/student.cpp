#include "student.h"

student::student(QSqlDatabase db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::student_window),
    database(db)
{
    ui->setupUi(this);
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

    if (ui->find_bookid->text().isEmpty() || ui->find_bookname->text().isEmpty() || ui->find_press->text().isEmpty() || ui->find_press->text().isEmpty())
    {
        QSqlQuery query(database);
        if (!query.exec("select * from book"))
        {
            qDebug() << query.lastError();
        }
        else
        {
            while(query.next())
            {
                QString book_id = query.value(0).toString();
                QString book_name = query.value(1).toString();
                QString author_name = query.value(2).toString();
                QString press_name = query.value(3).toString();
                float price = query.value(4).toFloat();
                int stroage = query.value(5).toInt();
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
            }


        }
    }

}

