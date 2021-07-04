#ifndef SHOW_LIST_H
#define SHOW_LIST_H

#include <QMainWindow>

namespace Ui {
class show_list;
}

class show_list : public QMainWindow
{
    Q_OBJECT

public:
    show_list(QString &id,QWidget *parent = nullptr);
    ~show_list();

private slots:
    void on_pushButton_clicked();

private:
    Ui::show_list *ui;
};

#endif // SHOW_LIST_H
