#include "itemsalesreportform.h"
#include "ui_itemsalesreportform.h"
#include "dbhandler.h"
#include <QList>
#include <QStandardItemModel>

bool exist(QList<QString> &list, QString key);
void showItemReport(Ui::itemsalesreportform* ui);

itemsalesreportform::itemsalesreportform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::itemsalesreportform)
{
    ui->setupUi(this);

    showItemReport(ui);

    /*
    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QSqlQuery queryItem, queryPurchases, query;

        //query.exec("SELECT ItemId FROM Purchases_tbl");

        QString id,name;
        double total = 0;
        int quantity = 0;
        int row=0, column=0;
        QList<QString> idList; // to prevent of duplicating Ids in Purchases table
        QMessageBox msgBox;

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantity"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Revenue"));


        ui->tableView->setModel(model);
        ui->tableView->show();

        queryPurchases.exec("SELECT ItemId FROM Purchases_tbl");
        while(queryPurchases.next())
        {

            id = queryPurchases.value(0).toString();
            if(!exist(idList,id))
            {

                idList.push_back(id);

                queryItem.exec("SELECT ItemName FROM Item_tbl WHERE Id LIKE '%"+id+"%'");
                queryItem.next();
                name = queryItem.value(0).toString();


                query.exec("SELECT QuantityOfPurchase, Subtotal FROM Purchases_tbl WHERE ItemId LIKE '%"+id+"%'");
                while (query.next())
                {
                    quantity += query.value(0).toInt();
                    total += query.value(1).toDouble();
                }

                QStandardItem *item0 = new QStandardItem(QString(name));
                model->setItem(row,column++,item0);

                QStandardItem *item1 = new QStandardItem(QString(QString::number(quantity)));
                model->setItem(row,column++,item1);

                QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
                model->setItem(row,column++,item2);


                ui->tableView->update();


                row++;
                column = 0;
                total = 0;
                quantity = 0;

            }


        }



        dbHandler.close();
    }

*/

}

itemsalesreportform::~itemsalesreportform()
{
    delete ui;
}



bool exist(QList<QString> &list, QString key)
{
    bool exist = false;

    if(!list.isEmpty())
    {

        for(int i=0;i<list.size();i++)
        {
            if(list.at(i)==key)
            {
                exist = true; // it means that the Id allredy is already calculated
                break;
            }
        }
    }


    return exist;
}

void itemsalesreportform::on_pushButton_clicked()
{
    // search button
    QString id,itemName;
    itemName = ui->textEdit->toPlainText();

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open() && (itemName!="" || itemName!=" " ))  // itemName != "" does not work
    {
        QSqlQuery queryItem, queryPurchases;
        double total = 0;
        int quantity = 0;
        int row=0, column=0;

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantity"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Revenue"));


        ui->tableView->setModel(model);
        ui->tableView->show();


        queryItem.exec("SELECT Id FROM Item_tbl WHERE ItemName LIKE '"+itemName+"'");
        queryItem.next();
        id = queryItem.value(0).toString();

        if(id!="" || id!=" ")
        {

            queryPurchases.exec("SELECT QuantityOfPurchase, Subtotal FROM Purchases_tbl WHERE ItemId LIKE '%"+id+"%'");
            while(queryPurchases.next())
            {

                quantity += queryPurchases.value(0).toInt();
                total += queryPurchases.value(1).toDouble();
            }

            QStandardItem *item0 = new QStandardItem(QString(itemName));
            model->setItem(row,column++,item0);

            QStandardItem *item1 = new QStandardItem(QString(QString::number(quantity)));
            model->setItem(row,column++,item1);

            QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
            model->setItem(row,column++,item2);


            ui->tableView->update();

        }

        dbHandler.close();
    }


}


void itemsalesreportform::on_pushButton_2_clicked()
{
    // reset button
    showItemReport(ui);
    ui->textEdit->setText("");

}



void showItemReport(Ui::itemsalesreportform* ui)
{
    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
    if(dbHandler.open())
    {

        QSqlQuery queryItem, queryPurchases, query;

        //query.exec("SELECT ItemId FROM Purchases_tbl");

        QString id,name;
        double total = 0;
        int quantity = 0;
        int row=0, column=0;
        QList<QString> idList; // to prevent of duplicating Ids in Purchases table

        QStandardItemModel *model = new QStandardItemModel(row,3);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Item Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantity"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Revenue"));


        ui->tableView->setModel(model);
        ui->tableView->show();

        queryPurchases.exec("SELECT ItemId FROM Purchases_tbl");
        while(queryPurchases.next())
        {

            id = queryPurchases.value(0).toString();
            if(!exist(idList,id))
            {

                idList.push_back(id);

                queryItem.exec("SELECT ItemName FROM Item_tbl WHERE Id LIKE '%"+id+"%'");
                queryItem.next();
                name = queryItem.value(0).toString();


                query.exec("SELECT QuantityOfPurchase, Subtotal FROM Purchases_tbl WHERE ItemId LIKE '%"+id+"%'");
                while (query.next())
                {
                    quantity += query.value(0).toInt();
                    total += query.value(1).toDouble();
                }

                QStandardItem *item0 = new QStandardItem(QString(name));
                model->setItem(row,column++,item0);

                QStandardItem *item1 = new QStandardItem(QString(QString::number(quantity)));
                model->setItem(row,column++,item1);

                QStandardItem *item2 = new QStandardItem(QString(QString::number(total)));
                model->setItem(row,column++,item2);


                ui->tableView->update();


                row++;
                column = 0;
                total = 0;
                quantity = 0;

            }


        }



        dbHandler.close();
    }

}
