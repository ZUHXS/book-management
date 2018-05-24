#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDebug>
#include "student.h"

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
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
