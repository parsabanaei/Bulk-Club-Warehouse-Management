#include "membersexpirationform.h"
#include "ui_membersexpirationform.h"
#include "dbhandler.h"

#include <QStandardItemModel>

membersexpirationform::membersexpirationform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::membersexpirationform)
{
    ui->setupUi(this);
}

membersexpirationform::~membersexpirationform()
{
    delete ui;
}

void membersexpirationform::on_pushButton_clicked()
{
    QString month = ui->textEdit->toPlainText();

    if(month!="" || (!month.isNull()))
    {
        DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);
        if(dbHandler.open())
        {
            QSqlQuery query;
            QString name, membershipNumber, membershipType, expirationDate;
            int row=0, column=0;
            double cost = 0;

            QStandardItemModel *model = new QStandardItemModel(row,5);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Member Name"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Membership Number"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Membership Type"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Expiration Date"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("renewal Cost"));


            ui->tableView->setModel(model);
            ui->tableView->show();


            query.exec("SELECT Name, MembershipNumber, MembershipType, ExpirationDate FROM Member_tbl WHERE ExpirationDate LIKE '%"+month+"%'");
            while(query.next())
            {
                name = query.value(0).toString();
                membershipNumber = query.value(1).toString();
                membershipType = query.value(2).toString();
                expirationDate = query.value(3).toString();


                QStandardItem *item0 = new QStandardItem(QString(name));
                model->setItem(row,column++,item0);

                QStandardItem *item1 = new QStandardItem(QString(membershipNumber));
                model->setItem(row,column++,item1);

                QStandardItem *item2 = new QStandardItem(QString(membershipType));
                model->setItem(row,column++,item2);

                QStandardItem *item3 = new QStandardItem(QString(expirationDate));
                model->setItem(row,column++,item3);




                if(membershipType == "Executive\n")
                {
                    cost = EXECUTIVE_MEMBERS_ANNUAL_PAYMENT;
                }

                else if(membershipType == "Regular\n")
                {
                    cost = REGULAR_MEMBERS_ANNUAL_PAYMENT;
                }

                QStandardItem *item4 = new QStandardItem(QString::number(cost));
                model->setItem(row,column++,item4);

                ui->tableView->update();


                row++;
                column = 0;
                cost = 0;
            }


            dbHandler.close();
        }


    }

}

