#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>

void MainWindow::update(){
    this->db->GetDersler();
    findChild<QComboBox*>("derslerCombo")->setModel(db->dersler);
    QString dersadi = findChild<QComboBox*>("derslerCombo")->currentText();
    db->GetNotlar(dersadi);
    findChild<QTableView*>("tableView")->setModel(db->notlar);
}

void MainWindow::hidetablecolumn(){
    findChild<QTableView*>("tableView")->hideColumn(0);
    findChild<QTableView*>("tableView")->hideColumn(2);
    findChild<QTableView*>("tableView")->hideColumn(3);
    findChild<QTableView*>("tableView")->hideColumn(4);
    findChild<QTableView*>("tableView")->hideColumn(5);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update();
    hidetablecolumn();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

void MainWindow::on_kaydetButton_clicked()
{
    int row = findChild<QTableView*>("tableView")->currentIndex().row();
    int id = findChild<QTableView*>("tableView")->selectionModel()->model()->index(row,0).data().toInt();
    QString baslik = findChild<QLineEdit*>("baslik")->text();
    QString kod = findChild<QPlainTextEdit*>("kod")->toPlainText();
    QString cikti = findChild<QPlainTextEdit*>("cikti")->toPlainText();
    QString aciklama = findChild<QPlainTextEdit*>("aciklama")->toPlainText();
    db->UpdateNot(id,baslik,kod,cikti,aciklama);
    QString dersadi = findChild<QComboBox*>("derslerCombo")->currentText();
    this->db->GetDersler();
    findChild<QComboBox*>("derslerCombo")->setModel(db->dersler);
    findChild<QComboBox*>("derslerCombo")->setCurrentText(dersadi);
}

void MainWindow::on_actionDers_Ekle_triggered()
{
    bool ok;
    QString dersAdi = QInputDialog::getText(this,"Ders Ekle", "Ders Adı", QLineEdit::Normal, "", &ok);

    if(ok && !dersAdi.isEmpty()){
        db->AddDers(dersAdi);
        db->dersler->setQuery("SELECT * FROM Dersler");
        update();
        findChild<QComboBox*>("derslerCombo")->setCurrentText(dersAdi);
    }
}

void MainWindow::on_actionDersi_Sil_triggered()
{
    QString dersAdi = findChild<QComboBox*>("derslerCombo")->currentText();
    int ret = QMessageBox::warning(this, tr("Silmek İstediğine Emin Misin?"),
                         dersAdi,
                         QMessageBox::Save | QMessageBox::Cancel);

    if(ret==2048){
        db->DelDers(dersAdi);
        update();
    }
}

void MainWindow::on_actionPDF_ye_D_n_t_r_triggered()
{
    htmlYaz *html = new htmlYaz();
    QString dosyaadi = findChild<QComboBox*>("derslerCombo")->currentText();
    QAbstractItemModel *veri = findChild<QTableView*>("tableView")->model();
    html->dosyaAc(dosyaadi,veri);
}

void MainWindow::on_derslerCombo_currentIndexChanged(const QString &arg1)
{
    db->GetNotlar(arg1);
    findChild<QTableView*>("tableView")->setModel(db->notlar);
    hidetablecolumn();
}

void MainWindow::on_silButton_clicked()
{
    int row = findChild<QTableView*>("tableView")->currentIndex().row();
    int id = findChild<QTableView*>("tableView")->selectionModel()->model()->index(row,0).data().toInt();
    db->DelNot(id);
    QString dersadi = findChild<QComboBox*>("derslerCombo")->currentText();
    on_derslerCombo_currentIndexChanged(dersadi);
}

void MainWindow::on_pushButton_clicked()
{
    QString dersadi = findChild<QComboBox*>("derslerCombo")->currentText();
    db->AddNot(dersadi);
    on_derslerCombo_currentIndexChanged(dersadi);
}



void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString baslik = index.model()->data(index.model()->index(index.row(),1)).toString();
    QString kod = index.model()->data(index.model()->index(index.row(),2)).toString();
    QString cikti = index.model()->data(index.model()->index(index.row(),3)).toString();
    QString aciklama = index.model()->data(index.model()->index(index.row(),4)).toString();
    findChild<QLineEdit*>("baslik")->setText(baslik);
    findChild<QPlainTextEdit*>("kod")->document()->setPlainText(kod);
    findChild<QPlainTextEdit*>("cikti")->document()->setPlainText(cikti);
    findChild<QPlainTextEdit*>("aciklama")->document()->setPlainText(aciklama);
}
