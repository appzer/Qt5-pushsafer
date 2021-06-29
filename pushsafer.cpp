#include <QApplication>

#include "pushsafer.h"

PushSafer::PushSafer() {}

void PushSafer::Push(QString PrivateKey, QString Title, QString Message, QString Device, QString Priority, QString Sound, QString Vibration, QString Icon, QString IconColor, QString Time2Live, QString Retry, QString Expire, QString Confirm, QString Answer, QString AnswerOptions, QString URL, QString URLTitle, QString Giphy, QString Image1, QString Image2, QString Image3, QString ImageSize)
{
    QNetworkAccessManager *PushServiceManager = new QNetworkAccessManager(this);
    connect(PushServiceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(PushRequestFinished(QNetworkReply*)));

    QUrl PushServiceUrl = QUrl("https://www.pushsafer.com/api");

    QUrlQuery PushData;                                         // Parameter https://www.pushsafer.com/en/pushapi_ext

    PushData.addQueryItem("k",  PrivateKey);                    // Private or Alias Key

    PushData.addQueryItem("d",  Device);                        // Device or Device Group (a=alle)
    PushData.addQueryItem("pr", Priority);                      // Priority (-2 - 2), (2 = Critical Alert)
    PushData.addQueryItem("s",  Sound);                         // Sound (0-62)
    PushData.addQueryItem("v",  Vibration);                     // Vibration (1-3)
    PushData.addQueryItem("i",  Icon);                          // Icon
    PushData.addQueryItem("c",  IconColor);                     // Icon-Color	

    PushData.addQueryItem("l",  Time2Live);                     // Time to Live Integer number 0-43200: Time in minutes, after a message automatically gets purged
    PushData.addQueryItem("re", Retry);                         // Retry / resend Integer 60-10800 (60s steps): Time in seconds, after a message should resend
    PushData.addQueryItem("ex", Expire);                        // Expire Integer 60-10800: Time in seconds, after the retry/resend should stop
    PushData.addQueryItem("cr", Confirm);                       // Confirm / resend Integer 10-10800 (10s steps) Time in seconds after which a message should be sent again before it is confirmed

    PushData.addQueryItem("t",  Title);                         // Titel (max 255 Zeichen)
    PushData.addQueryItem("m",  Message);                       // Text (max 5000 Zeichen)

    PushData.addQueryItem("a",  Answer);                        // Auf diese Nachricht kann geantwortet werden (0=no, 1=yes)
    PushData.addQueryItem("ao", AnswerOptions);		            // Answer-Options

    PushData.addQueryItem("u",  URL); 						    // URL
    PushData.addQueryItem("ut", URLTitle);                      // Title of URL

    PushData.addQueryItem("g",  Giphy);			                // GIPHY GIF Code

    PushData.addQueryItem("p",  Image1);                        // Image 1 Data URL with Base64-encoded string
    PushData.addQueryItem("p2", Image2);                        // Image 2 Data URL with Base64-encoded string
    PushData.addQueryItem("p3", Image3);                        // Image 3 Data URL with Base64-encoded string
    PushData.addQueryItem("is", ImageSize);                     // Image size (0-3)

    QNetworkRequest PushRequest(PushServiceUrl);
    PushRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    PushServiceManager->post(PushRequest, PushData.toString(QUrl::FullyEncoded).toUtf8());

    qDebug() << "Push-Notification sent";
}

void PushSafer::PushRequestFinished (QNetworkReply *reply)
{
    if(reply->error())
        qDebug() << "Error sending Push-Notification: " << reply->errorString();
    else
    {
        QString JSONReply = reply->readAll();
        QJsonDocument JSONResponse = QJsonDocument::fromJson(JSONReply.toUtf8());
        QJsonObject JSONObject = JSONResponse.object();

        qDebug() << "Pushsafer-API response:";
        qDebug() << "Status:" << JSONObject["status"].toInt();
        qDebug() << "Success:" << JSONObject["success"].toString();
        qDebug() << "Available:" << JSONObject["available"].toInt();
        qDebug() << "Message IDs:" << JSONObject["message_ids"].toString();
    }

    QApplication::exit();
}
