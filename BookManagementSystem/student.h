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
#include "main.h"
#include "mainwindow.h"

namespace Ui {
    class student_window;
}
class student : public QMainWindow
{
    Q_OBJECT
public:
    explicit student(QSqlDatabase db, QString name, QMainWindow *parent = 0);
    ~student();

private slots:
    void on_pushButton_clicked(int x = 0);   // find books

    void on_fresh_borrow_clicked();

    void on_borrow_clicked();

    void on_ret_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::student_window *ui;
    QSqlDatabase database;
    QString student_name;
    QString id;
    QMainWindow *stu_parent;
};

#endif // STUDENT_H
