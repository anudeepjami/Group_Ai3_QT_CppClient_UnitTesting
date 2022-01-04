#include <QtTest>
#include <QCoreApplication>
#include "nodeapicall.h"

// add necessary includes here

class loginpage : public QObject
{
    Q_OBJECT

public:
    loginpage();
    ~loginpage();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void loginsuccess();

private:
    NodeAPICall *postValidateUser;

};

loginpage::loginpage()
{

}

loginpage::~loginpage()
{

}

void loginpage::initTestCase()
{

}

void loginpage::cleanupTestCase()
{

}

void loginpage::loginsuccess()
{
    // check username and password present in DB by calling validateuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/validateuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["username"] = "rvrajavijay"; // enter username
    aPIInputData["password"] = "test1234"; // enter password
    aPIInputData["logintype"] = "login"; // enter login type

    postValidateUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postValidateUser, SIGNAL (aPIOutput()));

    QVERIFY(spy.wait(1000));
    qDebug()<<postValidateUser->outputFromAPI();;
    //postValidateUser->outputFromAPI();

}


QTEST_MAIN(loginpage)

#include "tst_loginpage.moc"
