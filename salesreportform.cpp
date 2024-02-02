#include "salesreportform.h"
#include "ui_salesreportform.h"
#include "dbhandler.h"

#include <QStandardItemModel>


SalesReportForm::SalesReportForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesReportForm)
{
    ui->setupUi(this);

}

SalesReportForm::~SalesReportForm()
{
    delete ui;
}

void SalesReportForm::on_pushButton_clicked()
{

    int day = 1 + ui->comboBox->currentIndex();

    int typeFilter = ui->comboBox_2->currentIndex();


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);

    if(dbHandler.open())
    {

        //QSqlQueryModel *queryModel = new QSqlQueryModel();

        //queryModel->setQuery("SELECT  Date, CustomerMembershipNumber, QuantityOfPurchase, Total FROM Purchases_tbl WHERE Day LIKE '%"+QString::number(day)+"%'");
        //queryModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
        //queryModel->setHeaderData(1, Qt::Horizontal, tr("Salary"));
        //ui->tableView->setModel(queryModel);
        //ui->tableView->show();

        QSqlQuery query, itemQuery, memberQuery;
        query.exec("SELECT ItemId, Date, CustomerMembershipNumber, QuantityOfPurchase, Total FROM Purchases_tbl WHERE Day LIKE '%"+QString::number(day)+"%'");

        int row=0, column=0;
        QString id, date, membershipNumber, quantity, total, itemName, memberName, memberType;


        QStandardItemModel *model = new QStandardItemModel(row,7);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Member Type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Item"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantity"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Total"));

        ui->tableView->setModel(model);
        ui->tableView->show();

        while(query.next())
        {
            id = query.value(0).toString();
            date = query.value(1).toString();
            membershipNumber = query.value(2).toString();
            quantity = query.value(3).toString();
            total = query.value(4).toString();


            switch(typeFilter)
            {
            case 1:
                memberQuery.exec("SELECT Name, MembershipType FROM Member_tbl WHERE MembershipNumber LIKE '%"+membershipNumber+"%' AND MembershipType LIKE '%Regular%'");
                break;

            case 2:
                memberQuery.exec("SELECT Name, MembershipType FROM Member_tbl WHERE MembershipNumber LIKE '%"+membershipNumber+"%' AND MembershipType LIKE '%Executive%'");
                break;

            default:
                memberQuery.exec("SELECT Name, MembershipType FROM Member_tbl WHERE MembershipNumber LIKE '%"+membershipNumber+"%'");
            }

            //memberQuery.exec("SELECT Name, MembershipType FROM Member_tbl WHERE MembershipNumber LIKE '%"+membershipNumber+"%'");
            memberQuery.next();
            memberName = memberQuery.value(0).toString();
            memberType = memberQuery.value(1).toString();


            if(memberType!="") // correct type was found else it needs to iterate to find next member in the specific Day if regular or executive
            {
                itemQuery.exec("SELECT ItemName FROM Item_tbl WHERE Id LIKE '%"+id+"%'");
                itemQuery.next();
                itemName = itemQuery.value(0).toString();



                QStandardItem *item = new QStandardItem(QString(memberName));
                model->setItem(row,column++,item);

                QStandardItem *item2 = new QStandardItem(QString(membershipNumber));
                model->setItem(row,column++,item2);

                QStandardItem *item3 = new QStandardItem(QString(memberType));
                model->setItem(row,column++,item3);

                QStandardItem *item4 = new QStandardItem(QString(date));
                model->setItem(row,column++,item4);

                QStandardItem *item5 = new QStandardItem(QString(itemName));
                model->setItem(row,column++,item5);

                QStandardItem *item6 = new QStandardItem(QString(quantity));
                model->setItem(row,column++,item6);

                QStandardItem *item7 = new QStandardItem(QString(total));
                model->setItem(row,column++,item7);


                ui->tableView->update();


                row++;
                column=0;

            }

        }

        dbHandler.close();
    }


}

