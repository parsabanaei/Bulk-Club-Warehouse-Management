#ifndef MEMBERSEXPIRATIONFORM_H
#define MEMBERSEXPIRATIONFORM_H

#include <QMainWindow>

namespace Ui {
class membersexpirationform;
}

class membersexpirationform : public QMainWindow
{
    Q_OBJECT

public:
    explicit membersexpirationform(QWidget *parent = nullptr);
    ~membersexpirationform();

private slots:
    void on_pushButton_clicked();

private:
    Ui::membersexpirationform *ui;
};

#endif // MEMBERSEXPIRATIONFORM_H
