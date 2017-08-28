#ifndef HTMLYAZ_H
#define HTMLYAZ_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QAbstractItemModel>
#include <QMessageBox>

class htmlYaz : public QObject
{
    Q_OBJECT
public:
    explicit htmlYaz(QObject *parent = 0);
    void dosyaAc(QString dosyaAdi, QAbstractItemModel *veri);
    void veriYaz(QString veri, int tur);

private:
    QString baslik = "<b><h1 style=\"color:red;\">%1</h1></b>";
    QString kod = "<font size=4><pre style=\"color:grey;\">%1</pre></font>";
    QString cikti = "<font size=4><pre style=\"color:#009933;\">%1</pre></font>";
    QString aciklama = "<font size=4><pre style=\"color:black;\">%1</pre></font>";
    QTextStream *out = new QTextStream();
signals:

public slots:
};

#endif // HTMLYAZ_H
