#ifndef SALESREPORTFORM_H
#define SALESREPORTFORM_H

#include <QMainWindow>

namespace Ui {
class SalesReportForm;
}

class SalesReportForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SalesReportForm(QWidget *parent = nullptr);
    ~SalesReportForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SalesReportForm *ui;
};

#endif // SALESREPORTFORM_H
