#ifndef NODEAPICALL_H
#define NODEAPICALL_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

class NodeAPICall : public QObject
{
    Q_OBJECT

public:
    explicit NodeAPICall( QString aPIURL, QString aPICallType, QJsonObject inputToAPI, QObject *parent = 0);
    virtual ~NodeAPICall();
    QJsonDocument outputFromAPI() const;

signals:
 void aPIOutput();

private slots:
 void aPIOutputRecieved(QNetworkReply* pReply);
 private:
 QNetworkAccessManager aPIManager;
 QJsonDocument aPIOutputData;

};

#endif // NODEAPICALL_H



