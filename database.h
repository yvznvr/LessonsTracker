#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>

class Database
{
public:
    Database();
    ~Database();
    void GetDersler();
    void GetNotlar(QString dersadi);
    void AddNot(QString dersadi);
    void DelNot(int id);
    void UpdateNot(int id,QString baslik,QString kod,QString cikti,QString aciklama);
    void AddDers(QString dersadi);
    void DelDers(QString dersadi);
    QSqlQueryModel *dersler = new QSqlQueryModel();
    QSqlQueryModel *notlar = new QSqlQueryModel();
private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DATABASE_H
