#ifndef MANAGER_H
#define MANAGER_H
#include <QDialog>
#include <ui_manager_window.h>
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
    class manager_window;
}
class manager : public QMainWindow
{
    Q_OBJECT
public:
    explicit manager(QWidget *parent);
    ~manager();
private:
    Ui::manager_window *ui;
};

#endif // MANAGER_H
