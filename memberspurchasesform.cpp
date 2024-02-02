#include "memberspurchasesform.h"
#include "ui_memberspurchasesform.h"
#include "dbhandler.h"

#include <QStandardItemModel>

void showReport(Ui::memberspurchasesform* ui);


memberspurchasesform::memberspurchasesform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memberspurchasesform)
{
    ui->setupUi(this);

    showReport(ui);

    /*
    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QSqlQuery query,itemQuery;

        query.exec("SELECT Name, MembershipNumber FROM Member_tbl");

        QString name, membershipNumber;
        double total= 0, grandTotal = 0;
        int row=0, column=0;

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Purchases"));


        ui->tableView->setModel(model);
        ui->tableView->show();

        while(query.next())
        {
            name = query.value(0).toString();
            membershipNumber = query.value(1).toString();

            itemQuery.exec("SELECT Total FROM Purchases_tbl WHERE CustomerMembershipNumber LIKE '%"+membershipNumber+"%'");
            while(itemQuery.next())
            {
                total += itemQuery.value(0).toDouble();
                grandTotal += itemQuery.value(0).toDouble();
            }



            QStandardItem *item0 = new QStandardItem(QString(name));
            model->setItem(row,column++,item0);

            QStandardItem *item1 = new QStandardItem(QString(membershipNumber));
            model->setItem(row,column++,item1);

            QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
            model->setItem(row,column++,item2);


            ui->tableView->update();


            row++;
            column = 0;
            total = 0;
        }

        ui->label_3->setText(QString::number(grandTotal));

        //queryModel->setQuery("SELECT  total, CustomerMembershipNumber, QuantityOfPurchase, Total FROM Purchases_tbl WHERE Day LIKE '%"+QString::number(day)+"%'");
        //queryModel->setQuery("SELECT  Name, MembershipNumber FROM Member_tbl");
        //queryModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
        //queryModel->setHeaderData(1, Qt::Horizontal, tr("Salary"));
        //ui->tableView->setModel(queryModel);
        //ui->tableView->show();




        dbHandler.close();
    }
*/


}

memberspurchasesform::~memberspurchasesform()
{
    delete ui;
}

void memberspurchasesform::on_pushButton_clicked()
{
    // Search button

    QString key; // name or membership number from textbox
    key = ui->textEdit->toPlainText();

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open() && (key!="" || key!=" " )) // key != "" does not work
    {
        ui->label_3->setVisible(false);
        ui->label_2->setVisible(false);

        QSqlQuery query, itemQuery;
        QString name, membershipNumber;
        double total = 0;

        QStandardItemModel *model = new QStandardItemModel(0,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Purchases Including Tax"));


        ui->tableView->setModel(model);
        ui->tableView->show();

        query.exec("SELECT Name, MembershipNumber FROM Member_tbl WHERE MembershipNumber LIKE '%"+key+"%' OR Name LIKE '%"+key+"%'");
        query.next();

        name = query.value(0).toString();
        membershipNumber = query.value(1).toString();

        itemQuery.exec("SELECT Total FROM Purchases_tbl WHERE CustomerMembershipNumber LIKE '%"+membershipNumber+"%'");
        while(itemQuery.next())
        {
            total += itemQuery.value(0).toDouble();
        }

        QStandardItem *item0 = new QStandardItem(QString(name));
        model->setItem(0,0,item0);

        QStandardItem *item1 = new QStandardItem(QString(membershipNumber));
        model->setItem(0,1,item1);

        QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
        model->setItem(0,2,item2);


        ui->tableView->update();


        dbHandler.close();
    }


}


void memberspurchasesform::on_pushButton_2_clicked()
{
    // Reset buuton
    showReport(ui);
    ui->textEdit->setText("");
}



void showReport(Ui::memberspurchasesform* ui)
{

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {
        ui->label_3->setVisible(true);
        ui->label_2->setVisible(true);

        QSqlQuery query,itemQuery;

        query.exec("SELECT Name, MembershipNumber FROM Member_tbl");

        QString name, membershipNumber;
        double total= 0, grandTotal = 0;
        int row=0, column=0;

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Purchases Including Tax"));


        ui->tableView->setModel(model);
        ui->tableView->show();

        while(query.next())
        {
            name = query.value(0).toString();
            membershipNumber = query.value(1).toString();

            itemQuery.exec("SELECT Total FROM Purchases_tbl WHERE CustomerMembershipNumber LIKE '%"+membershipNumber+"%'");
            while(itemQuery.next())
            {
                total += itemQuery.value(0).toDouble();
                grandTotal += itemQuery.value(0).toDouble();
            }



            QStandardItem *item0 = new QStandardItem(QString(name));
            model->setItem(row,column++,item0);

            QStandardItem *item1 = new QStandardItem(QString(membershipNumber));
            model->setItem(row,column++,item1);

            QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
            model->setItem(row,column++,item2);


            ui->tableView->update();


            row++;
            column = 0;
            total = 0;
        }

        ui->label_3->setText(QString::number(grandTotal));

        //queryModel->setQuery("SELECT  total, CustomerMembershipNumber, QuantityOfPurchase, Total FROM Purchases_tbl WHERE Day LIKE '%"+QString::number(day)+"%'");
        //queryModel->setQuery("SELECT  Name, MembershipNumber FROM Member_tbl");
        //queryModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
        //queryModel->setHeaderData(1, Qt::Horizontal, tr("Salary"));
        //ui->tableView->setModel(queryModel);
        //ui->tableView->show();




        dbHandler.close();
    }

}
