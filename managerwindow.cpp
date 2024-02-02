#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "salesreportform.h"
#include "memberspurchasesform.h"
#include "itemsalesreportform.h"
#include "rebatesform.h"
#include "membersexpirationform.h"


ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_pushButton_clicked()
{
    //hide();
    SalesReportForm *saleReportForm;
    saleReportForm = new SalesReportForm(this);
    saleReportForm->show();


}


void ManagerWindow::on_pushButton_2_clicked()
{
    //hide();
    memberspurchasesform *form;
    form = new memberspurchasesform(this);
    form->show();
}


void ManagerWindow::on_pushButton_3_clicked()
{
    //hide();
    itemsalesreportform *form;
    form = new itemsalesreportform(this);
    form->show();
}


void ManagerWindow::on_pushButton_4_clicked()
{
    //hide();
    rebatesform *form;
    form = new rebatesform(this);
    form->show();
}


void ManagerWindow::on_pushButton_5_clicked()
{
    //hide();
    membersexpirationform *form;
    form = new membersexpirationform(this);
    form->show();
}

