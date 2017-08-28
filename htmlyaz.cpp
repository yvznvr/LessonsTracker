#include "htmlyaz.h"

htmlYaz::htmlYaz(QObject *parent) : QObject(parent)
{

}

void htmlYaz::dosyaAc(QString dosyaAdi, QAbstractItemModel *veri){
    QString path = QDir::homePath().append("/");
    path.append(dosyaAdi);
    QFile file(path.append(".html"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    this->out->setDevice(&file);

    int satir = veri->rowCount();
    for(int i=0;i<satir;i++){
        for(int j=1;j<5;j++){
            veriYaz(veri->index(i,j).data().toString(),j);
        }
    }
    QMessageBox msgBox;
    msgBox.setText(QString("Dosya '%1' yolunda oluşturuldu.").arg(path));
    msgBox.exec();
}

void htmlYaz::veriYaz(QString veri, int tur){
    if(tur==1){
        QString baslik = this->baslik.arg(veri);
        *(this->out) << baslik;
        *(this->out) << "\n";
    }
    else if(tur==2){
        QString kod = this->kod.arg(veri);
        *(this->out) << kod;
        *(this->out) << "\n";
    }
    else if(tur==3){
        QString cikti = this->cikti.arg(veri);
        *(this->out) << cikti;
        *(this->out) << "\n";
    }
    else{
        QString aciklama = this->aciklama.arg(veri);
        *(this->out) << aciklama;
        *(this->out) << "<br><hr>";
        *(this->out) << "\n";

    }

}
