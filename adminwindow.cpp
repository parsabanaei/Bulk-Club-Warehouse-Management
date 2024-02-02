#include "adminwindow.h"
#include "ui_adminwindow.h"

adminwindow::adminwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);
}

adminwindow::~adminwindow()
{
    delete ui;
}

void adminwindow::on_pushButton_clicked()
{
    // Edit Members Button
}


void adminwindow::on_pushButton_2_clicked()
{
    // Edit Items Button
}

