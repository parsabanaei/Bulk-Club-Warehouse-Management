#include "rebatesform.h"
#include "ui_rebatesform.h"
#include "dbhandler.h"

#include <QStandardItemModel>

rebatesform::rebatesform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rebatesform)
{
    ui->setupUi(this);


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QSqlQuery query,queryPurchase;
        QString name, membershipNumber;
        double subTotal = 0, rebates= 0;
        int row=0, column=0;

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Rebates Amount"));


        ui->tableView->setModel(model);
        ui->tableView->show();


        query.exec("SELECT Name, MembershipNumber FROM Member_tbl WHERE MembershipType LIKE '%Executive%'");
        while(query.next())
        {
            name = query.value(0).toString();
            membershipNumber = query.value(1).toString();

            queryPurchase.exec("SELECT Subtotal FROM Purchases_tbl WHERE CustomerMembershipNumber LIKE '%"+membershipNumber+"%'");
            while(queryPurchase.next())
            {
                subTotal += queryPurchase.value(0).toDouble();
            }


            QStandardItem *item0 = new QStandardItem(QString(name));
            model->setItem(row,column++,item0);

            QStandardItem *item1 = new QStandardItem(QString(membershipNumber));
            model->setItem(row,column++,item1);


            rebates = (subTotal * REBATE_AMOUNT) / 100;

            double value = (int)(rebates * 100 + .5);
            rebates = (double)value / 100;

            QStandardItem *item2 = new QStandardItem(QString(QString::number(rebates)));
            model->setItem(row,column++,item2);


            ui->tableView->update();


            row++;
            column = 0;
            subTotal = 0;
            rebates = 0;
        }



        dbHandler.close();
    }

}

rebatesform::~rebatesform()
{
    delete ui;
}
