#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhandler.h"
#include "memberhandler.h"
#include "managerwindow.h"
#include "adminwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);


    QMessageBox msgBox;
    if(dbHandler.open())
    {
        try {
            QSqlQuery query;

            query.exec("SELECT count(*) FROM Purchases_tbl");
            query.next();
            QString result = query.value(0).toString();
            //msgBox.setText(result);
            //msgBox.exec();
            if(result=="0")
            {

                QFile file;
                QByteArray line;
                int index;
                QString arr[5];
                QString arrFiles[7]={DAY1_FILE, DAY2_FILE, DAY3_FILE, DAY4_FILE, DAY5_FILE, DAY6_FILE, DAY7_FILE};
                //MemberHandler memberHandler;  //**************===****************

                for(int i=0;i<7;i++)
                {

                    file.setFileName(arrFiles[i]);

                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {

                        msgBox.setText(FAILED_MESSAGE_FILE_OPENING);
                        msgBox.exec();
                    }
                    else
                    {
                        file.seek(0);


                        line.clear();

                        index = 0;


                        while(!file.atEnd())
                        {
                            QByteArray line = file.readLine();

                            arr[index++] = line;




                            if(index == 5)
                            {
                                // check if we do not have the item, we will insert the item to the Item Table
                                query.exec("SELECT Id FROM Item_tbl WHERE ItemName='"+arr[2]+"'");

                                query.next();
                                QString result = query.value(0).toString();

                                if(result == "")
                                {
                                    query.prepare("INSERT INTO Item_tbl (ItemName, ItemCost) "
                                                  "VALUES (:ItemName, :ItemCost)");
                                    query.bindValue(":ItemName", arr[2]);
                                    query.bindValue(":ItemCost", arr[3]);
                                    query.exec();


                                    query.exec("SELECT Id FROM Item_tbl WHERE ItemName='"+arr[2]+"'");

                                    query.next();
                                    result = query.value(0).toString();
                                }




                                query.prepare("INSERT INTO Purchases_tbl (ItemId, Date, Day, CustomerMembershipNumber, QuantityOfPurchase, TaxRate, UnitPrice, Subtotal, Total) "
                                              "VALUES (:ItemId, :Date, :Day, :CustomerMembershipNumber, :QuantityOfPurchase, :TaxRate, :UnitPrice, :Subtotal, :Total)");

                                query.bindValue(":ItemId", result);
                                query.bindValue(":Date", arr[0]);
                                query.bindValue(":Day", i+1);
                                query.bindValue(":CustomerMembershipNumber", arr[1]);
                                query.bindValue(":QuantityOfPurchase", arr[4]);
                                query.bindValue(":TaxRate", TAX_RATE);
                                query.bindValue(":UnitPrice", arr[3]);

                                double subtotal = (arr[3].toDouble() * arr[4].toDouble());
                                query.bindValue(":Subtotal", subtotal); // pre-tax cost

                                double total= subtotal + ((subtotal * TAX_RATE) / 100);
                                double round  = (int)(total * 100 + .5);
                                round = (double)round / 100;
                                query.bindValue(":Total", round);

                                query.exec();


                                //memberHandler.addData(arr[1].toInt(), arr[3].toDouble() * arr[4].toInt());

                                index = 0;
                            }


                        }

                        file.close();

                    }
                }




                file.setFileName(WAREHOUSE_SHOPPERS_FILE);

                if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                {

                    msgBox.setText(FAILED_MESSAGE_FILE_OPENING);
                    msgBox.exec();
                }
                else
                {
                    file.seek(0);

                    line.clear();

                    index = 0;

                   // double totalAmount;
                   //double rebateAmount;



                    while(!file.atEnd())
                    {
                        QByteArray line = file.readLine();

                        arr[index++] = line;

                        if(index == 4)
                        {
                            query.prepare("INSERT INTO Member_tbl (Name, MembershipNumber, MembershipType, ExpirationDate) "
                                          "VALUES (:Name, :MembershipNumber, :MembershipType, :ExpirationDate)");

                            query.bindValue(":Name", arr[0]);
                            query.bindValue(":MembershipNumber", arr[1]);
                            query.bindValue(":MembershipType", arr[2]);
                            query.bindValue(":ExpirationDate", arr[3]);


                            //memberHandler.getData(arr[1].toInt(), totalAmount, rebateAmount);
                            //query.bindValue(":TotalAmountSpent", totalAmount);
                            //query.bindValue(":RebateAmount", rebateAmount);

                            query.exec();




                            index = 0;
                        }



                    }

                    file.close();

                }
            }


        }

        catch (...)
        {
            msgBox.setText("Error while fetching data from files and saving into the database!");
            msgBox.exec();
        }

        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;

    DbHandler dbHandler(DATABASE_PATH,DATABASE_CONNECTION_NAME);

    if(dbHandler.open())
    {
        QSqlQuery query;

        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();
        QString result;

        if(query.exec("SELECT * FROM Account_tbl WHERE Username='"+username+"' AND Password='"+password+"'"))
        {
            query.next();
            result = query.value(0).toString();
            if(result=="")
            {
                msgBox.setText("incorrect!");
                msgBox.exec();
            }
            else
            {
                if(result=="2")
                {
                    ManagerWindow *managerForm;
                    hide();
                    managerForm = new ManagerWindow(this);
                    managerForm->show();
                }
                else if(result=="1")
                {
                    adminwindow *managerForm;
                    hide();
                    managerForm = new adminwindow(this);
                    managerForm->show();
                }

            }
        }



        dbHandler.close();
    }
    else
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
        msgBox.exec();
    }





}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->checkBox->checkState() ? ui->passwordLineEdit->setEchoMode(QLineEdit::Normal) :ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

