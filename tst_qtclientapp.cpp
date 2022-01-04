#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "nodeapicall.h"

class qtclientapp : public QObject
{
    Q_OBJECT

public:
    qtclientapp();
    ~qtclientapp();

private slots:
    void loginSuccess();
    void loginUserDoesnotExist();
    void loginUserAlreadyLoggedIn();
    void loginClearSessionOfActiveUser();
    void logoutUser();
    void loadContacts();
    void loadChatrooms();

private:
    NodeAPICall *postValidateUser;
    NodeAPICall *postLogoutUser;
    NodeAPICall *getContacts;
    NodeAPICall *getChatrooms;

};

qtclientapp::qtclientapp()
{

}

qtclientapp::~qtclientapp()
{

}

void qtclientapp::loginSuccess()
{
    // check username and password present in DB by calling validateuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/validateuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["username"] = "rvrajavijay"; // enter username
    aPIInputData["password"] = "test1234"; // enter password
    aPIInputData["logintype"] = "login"; // enter login type

    postValidateUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postValidateUser, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QVariantMap userData = postValidateUser->outputFromAPI().object().toVariantMap();
    QCOMPARE(userData["message"].toString(),"Success");
    QCOMPARE(userData["username"].toString(),"rvrajavijay");
}

void qtclientapp::loginUserDoesnotExist()
{
    // check username and password present in DB by calling validateuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/validateuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["username"] = "randomuser"; // enter username
    aPIInputData["password"] = "admin123"; // enter password
    aPIInputData["logintype"] = "login"; // enter login type

    postValidateUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postValidateUser, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QVariantMap userData = postValidateUser->outputFromAPI().object().toVariantMap();
    QCOMPARE(userData["message"].toString(),"User doesn't exist");
}

void qtclientapp::loginUserAlreadyLoggedIn()
{
    // check username and password present in DB by calling validateuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/validateuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["username"] = "rvrajavijay"; // enter username
    aPIInputData["password"] = "test1234"; // enter password
    aPIInputData["logintype"] = "login"; // enter login type

    postValidateUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postValidateUser, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QVariantMap userData = postValidateUser->outputFromAPI().object().toVariantMap();
    QCOMPARE(userData["message"].toString(),"User is already logged in, please logout from existing session");
}

void qtclientapp::loginClearSessionOfActiveUser()
{
    // check username and password present in DB by calling validateuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/validateuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["username"] = "rvrajavijay"; // enter username
    aPIInputData["password"] = "test1234"; // enter password
    aPIInputData["logintype"] = "logout"; // enter login type

    postValidateUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postValidateUser, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QVariantMap userData = postValidateUser->outputFromAPI().object().toVariantMap();
    QCOMPARE(userData["message"].toString(),"User logged out successfully, please login again");
}

void qtclientapp::logoutUser()
{
    // logout user by calling logoutuser post method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/logoutuser";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    aPIInputData["userid"] = "6"; // enter userid

    postLogoutUser = new NodeAPICall(aPIURL, "post", aPIInputData, this);

    QSignalSpy spy(postLogoutUser, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QVariantMap userData = postLogoutUser->outputFromAPI().object().toVariantMap();
    QCOMPARE(userData["affectedRows"].toString(),"1");
}

void qtclientapp::loadContacts()
{
    // Load contacts to contacts list widget by calling contacts get method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/users/contacts";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    getContacts = new NodeAPICall(aPIURL, "get", aPIInputData, this);

    QSignalSpy spy(getContacts, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QJsonArray userData = getContacts->outputFromAPI().array();
    QStringList userNames;

    for( int i=0; i < userData.size(); i++)
    {
        QJsonObject object = userData.at(i).toObject();
        QVariantMap userDataMap = object.toVariantMap();
        userNames.push_back(userDataMap["username"].toString());
    }
    QCOMPARE(userNames[0],"aj");
    QCOMPARE(userNames[1],"varun");
    QCOMPARE(userNames[2],"bharat");
    QCOMPARE(userNames[3],"pedro");
    QCOMPARE(userNames[4],"shubham");
    QCOMPARE(userNames[5],"rvrajavijay");
}

void qtclientapp::loadChatrooms()
{
    // Load chatrooms to chatroom list widget by calling getchatrooms get method from NODE API
    QString aPIURL = "https://ai3chatapi.azurewebsites.net/api/chatrooms/getchatrooms";
    QJsonObject aPIInputData; //empty for get request, has data for post request
    getChatrooms = new NodeAPICall(aPIURL, "get", aPIInputData, this);

    QSignalSpy spy(getChatrooms, SIGNAL (aPIOutput()));
    //wait for signal output
    QVERIFY(spy.wait());
    //Turn signal output to qvariant map
    QJsonArray chatroomsData = getChatrooms->outputFromAPI().array();
    QStringList chatroomNames;

    for( int i=0; i < chatroomsData.size(); i++)
    {
        QJsonObject object = chatroomsData.at(i).toObject();
        QVariantMap chatroomsDataMap = object.toVariantMap();
        chatroomNames.push_back(chatroomsDataMap["chatroomname"].toString());
    }
    QCOMPARE(chatroomNames[0],"Ai3-Project ");
    QCOMPARE(chatroomNames[1],"Ai3-ProjectQueries");
    QCOMPARE(chatroomNames[2],"Friends");
}

QTEST_MAIN(qtclientapp)

#include "tst_qtclientapp.moc"
