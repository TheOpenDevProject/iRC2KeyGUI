#ifndef IRCPROCESSOR_H
#define IRCPROCESSOR_H
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QRegularExpression>
#include <QTextBrowser>
#include <QRegularExpressionMatch>
#include <string>
#include <windowskeyboardsim.h>
#include <musicplayer.h>
#include <QCheckBox>
#include <QTimer>
class iRCProcessor : public QObject
{
    Q_OBJECT
public:
    explicit iRCProcessor();
    ~iRCProcessor();
    void openToServer(); // Could be merged at a later stage with its other connect to channel function
    void setupIRC(QString server, int port, QString nickname, QString realNameX, QString channelNameX, QString userName, QString t_passwordX);
        void checkVals();
        void closeToServer();
        QString ircOutput;
        void pushMsg(QString msgToSend);
        std::vector <QString> msgStack;
        QString getUsername();
        void setSuspended();
        void setUnsuspended();
       QString setCurrentGameTitle(QString currentGame);
       QString getCurrentGameTitle();
       MusicPlayer streamMusic;
       bool waitForDelay(QCheckBox *delay_Checked,int timeInSec); //Pass a checkbox from the form and set the delayer
signals:

public slots:
    void connected();
    void disconnected();
       void readyRead();
       void messageDelayer();
private:
       //This is the timer and counter for the lastMessage delay functions
       int timeSinceLastMsg = 0;
       QTimer *countDelay;
       //End
    QString ircServer;
    QString username;
    QString realName;
    QString nickName;
    QString channelName;
    QString t_password;
    int server_port = 6667; //Default NON-SSL IRC port
    QTcpSocket *ircSocket;
    QString messageLine;

    QString STL_Message_Parser(QString ircMessage);
    QRegularExpression QRegEx;
    QRegularExpressionMatch QRegExMatch;
    //PING-PONG
    QRegularExpression pingPong;
    QRegularExpressionMatchIterator QRegExIttr;
    WindowsKeyboardSim keySim;
    QString keepAlive(QString ircMessage);
    QString current_game = "No Game Title Set";
    bool isSuspended = false; //Why would we start the bot to a suspended state?
};
/*
class vdsInfo{
    vdsInfo();
public:
    int addTime(int timeToAdd){runTime+= timeToAdd;}
    int getTime(){return runTime;}
       static int runTime;
private:

};

*/
#endif // IRCPROCESSOR_H
