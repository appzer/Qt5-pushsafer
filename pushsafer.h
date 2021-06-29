#ifndef PUSHSAFER_H
#define PUSHSAFER_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class PushSafer : public QObject
{
    Q_OBJECT

public:
    PushSafer();
    void Push(QString Title, QString Message);

public slots:
    void PushRequestFinished(QNetworkReply *reply);
};

#endif // PUSHSAFER_H
