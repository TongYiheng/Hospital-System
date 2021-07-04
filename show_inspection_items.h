#ifndef SHOW_INSPECTION_ITEMS_H
#define SHOW_INSPECTION_ITEMS_H

#include <QMainWindow>

namespace Ui {
class show_inspection_items;
}

class show_inspection_items : public QMainWindow
{
    Q_OBJECT

public:
    show_inspection_items(QString &id,QWidget *parent = nullptr);
    ~show_inspection_items();

private slots:
    void on_pushButton_clicked();

private:
    Ui::show_inspection_items *ui;
};

#endif // SHOW_INSPECTION_ITEMS_H
