#ifndef MEMBERSPURCHASESFORM_H
#define MEMBERSPURCHASESFORM_H

#include <QMainWindow>

namespace Ui {
class memberspurchasesform;
}

class memberspurchasesform : public QMainWindow
{
    Q_OBJECT

public:
    explicit memberspurchasesform(QWidget *parent = nullptr);
    ~memberspurchasesform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::memberspurchasesform *ui;
};

#endif // MEMBERSPURCHASESFORM_H
