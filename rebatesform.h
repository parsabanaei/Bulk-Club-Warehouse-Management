#ifndef REBATESFORM_H
#define REBATESFORM_H

#include <QMainWindow>

namespace Ui {
class rebatesform;
}

class rebatesform : public QMainWindow
{
    Q_OBJECT

public:
    explicit rebatesform(QWidget *parent = nullptr);
    ~rebatesform();

private:
    Ui::rebatesform *ui;
};

#endif // REBATESFORM_H
