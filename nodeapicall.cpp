#include "nodeapicall.h"

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

NodeAPICall::NodeAPICall(QString aPIURL, QString aPICallType, QJsonObject inputToAPI, QObject *parent)
    : QObject(parent)
{
    connect(
                &aPIManager, SIGNAL (finished(QNetworkReply*)),
                this, SLOT (aPIOutputRecieved(QNetworkReply*))
                );

    QUrl uRL(aPIURL);
    QNetworkRequest request(uRL);

    if(aPICallType == "get")
    {
        aPIManager.get(request);
    }
    else if(aPICallType == "post")
    {
        request.setRawHeader("Content-Type", "application/json");
        QJsonDocument data(inputToAPI);
        QByteArray userDataDetails = data.toJson();
        aPIManager.post(request, userDataDetails);
    }
}

NodeAPICall::~NodeAPICall() { }

void NodeAPICall::aPIOutputRecieved(QNetworkReply* aPIReply){
    if ( aPIReply->error())
    {
        qDebug() << "Error :" << aPIReply->errorString();
    } else
    {
        QByteArray recievedData = aPIReply->readAll();
        aPIOutputData = QJsonDocument::fromJson(recievedData);

        aPIReply->deleteLater();
        emit aPIOutput();
    }
}

QJsonDocument NodeAPICall::outputFromAPI() const{
    return aPIOutputData;
}

