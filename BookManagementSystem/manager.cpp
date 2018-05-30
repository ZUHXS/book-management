#include "manager.h"

manager::manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager_window)
{
    ui->setupUi(this);
}

manager::~manager()
{
    delete ui;
}
