#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "htmlyaz.h"
#include <QAbstractItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Database *db = new Database();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_kaydetButton_clicked();

    void on_actionDers_Ekle_triggered();

    void on_actionDersi_Sil_triggered();

    void on_actionPDF_ye_D_n_t_r_triggered();

    void on_silButton_clicked();

    void on_pushButton_clicked();

    void update();

    void hidetablecolumn();

    void on_tableView_activated(const QModelIndex &index);

    void on_derslerCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
