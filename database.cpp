#include "database.h"
Database::Database()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("/home/yavuz/.config/DersTakip/db.sqlite");
    this->db.open();
    this->query = QSqlQuery(this->db);
}

Database::~Database(){
    QString connection = this->db.connectionName();
    this->db = QSqlDatabase();
    this->db.removeDatabase(connection);
    this->db.close();
}

void Database::GetDersler(){
    //this->query.exec("SELECT dersadi FROM Dersler");
    this->dersler->setQuery("SELECT dersadi id FROM Dersler");
}

void Database::GetNotlar(QString dersadi){
    this->query.exec(QString("SELECT * from Dersler WHERE dersadi='%1'").arg(dersadi));
    this->query.first();
    QString id = this->query.value(0).toString();
    this->notlar->setQuery(QString("SELECT * from Notlar WHERE ders_id=%1").arg(id));
}

void Database::AddNot(QString dersadi){
    this->query.exec(QString("SELECT * from Dersler WHERE dersadi='%1'").arg(dersadi));
    this->query.first();
    QString id = this->query.value(0).toString();
    this->notlar->setQuery(QString("INSERT INTO Notlar(baslik, ders_id) VALUES('Yeni Sayfa',%1)").arg(id));
}

void Database::DelNot(int id){
    this->query.exec(QString("DELETE FROM Notlar WHERE id=%1").arg(id));
    //this->notlar->setQuery(QString("SELECT * FROM Notlar WHERE id=%1").arg(id));
}

void Database::UpdateNot(int id,QString baslik,QString kod,QString cikti,QString aciklama){
    this->query.exec(QString("UPDATE Notlar SET baslik='%1',kod='%2',cikti='%3',aciklama='%4'  WHERE id=%5").arg(baslik,kod,cikti,aciklama,QString::number(id)));
}

void Database::AddDers(QString dersadi){
    this->query.exec(QString("INSERT INTO Dersler(dersadi) VALUES('%1')").arg(dersadi));
}

void Database::DelDers(QString dersadi){
    this->query.exec(QString("DELETE FROM Dersler WHERE dersadi='%1'").arg(dersadi));
}
