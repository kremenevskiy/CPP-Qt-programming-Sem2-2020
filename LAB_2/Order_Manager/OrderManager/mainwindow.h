#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include <iterator>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QRegExpValidator>

#include "courier.h"
#include "orders.h"




QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; } QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialization();
    void showAllOrders();
    void showAllCouriers();
    void start_init();
    void activate_buttons_order(bool bln);
    void activate_buttons_courier(bool bln);




public slots:
    void addCourier();
    void addOrder();
    void update_button_clicked();
    void init_button_clicked();
    void delete_order();
    void delete_courier();

    void choose_file();


    void reorder();







private slots:
    void on_comboBox_orders_currentIndexChanged(int index);

    void on_comboBox_courier_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    std::vector<Orders> VectorOrders;

    std::vector<Courier> VectorCourier;

    int OrderCounter;
    int CourierCounter;

    QString fileName_Save_Order;
    QString fileName_Save_Courier;

    QString fileName_Open_Order;
    QString fileName_Open_Courier;

};
#endif // MAINWINDOW_H
