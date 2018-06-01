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
    explicit manager(QSqlDatabase db, QString name, QWidget *parent = 0);
    ~manager();
private slots:
    void on_add_clicked();

    void on_find_clicked(int x = 0);

    void on_delete_book_clicked();
    void update_student_list();

    void on_delete_stu_clicked();
    void update_loan_list(int unreturn);  // unreturn = 1, update only unreturned records

    void on_if_only_unreturn_clicked(bool checked);

private:
    Ui::manager_window *ui;
    QSqlDatabase database;
    QString manager_name;
};

#endif // MANAGER_H
