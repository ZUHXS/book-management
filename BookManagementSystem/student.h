#ifndef STUDENT_H
#define STUDENT_H
#include <QDialog>
#include <ui_student_window.h>
#include <QDebug>
#include <QTime>
#include <main.h>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QTextCodec>
#include<QSqlDatabase>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRelationalTableModel>
#include<QSqlError>

namespace Ui {
    class student_window;
}
class student : public QMainWindow
{
    Q_OBJECT
public:
    explicit student(QSqlDatabase db, QWidget *parent = 0);
    ~student();

private slots:
    void on_pushButton_clicked();

private:
    Ui::student_window *ui;
    QSqlDatabase database;
};
#endif // STUDENT_H
