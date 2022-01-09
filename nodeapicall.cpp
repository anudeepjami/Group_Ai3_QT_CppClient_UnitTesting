#include "nodeapicall.h"

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

/**
 * @brief NodeAPICall::NodeAPICall
 *          This function is used to make node api calls for all test cases
 * @param aPIURL
 * @param aPICallType
 * @param inputToAPI
 * @param parent
 */
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

/**
 * @brief NodeAPICall::~NodeAPICall
 */
NodeAPICall::~NodeAPICall() { }

/**
 * @brief NodeAPICall::aPIOutputRecieved
 *          This function receives the output of the api call in json format and emits aPIOutput signal
 * @param aPIReply
 */
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

/**
 * @brief NodeAPICall::outputFromAPI
 *          This function return the api data received to the parent functions
 * @return
 */
QJsonDocument NodeAPICall::outputFromAPI() const{
    return aPIOutputData;
}

