#ifndef ITEMSALESREPORTFORM_H
#define ITEMSALESREPORTFORM_H

#include <QMainWindow>

namespace Ui {
class itemsalesreportform;
}

class itemsalesreportform : public QMainWindow
{
    Q_OBJECT

public:
    explicit itemsalesreportform(QWidget *parent = nullptr);
    ~itemsalesreportform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::itemsalesreportform *ui;
};

#endif // ITEMSALESREPORTFORM_H
