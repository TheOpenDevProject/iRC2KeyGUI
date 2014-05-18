#include "ircprocessor.h"
#include <QTextStream>
#include <windows.h>
#include <QString>
#include <QTime>
/*
 To put something into the Output console put it in the msgStack que (Failure of a name) FIFO does not apply on the vector, probably was done drunk...
  ircSocet is the TCP Socket object
 pushMsg sends an IRC compliant PRIVMSG to the channel
 */
iRCProcessor::iRCProcessor()
{
    countDelay = new QTimer(this);
    connect(countDelay,SIGNAL(timeout()),this,SLOT(messageDelayer()));

}
iRCProcessor::~iRCProcessor(){
    delete countDelay;
}

void iRCProcessor::openToServer(){
    ircSocket = new QTcpSocket(this);
   connect(ircSocket,SIGNAL(connected()),this,SLOT(connected()));
           connect(ircSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
             connect(ircSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
                  //Connect to IRC Server and wait for response (max - 30Sec)
                    msgStack.push_back("Connecting to IRC server...");
            ircSocket->connectToHost(ircServer,server_port);
            if(!ircSocket->waitForConnected()){
                msgStack.push_back("Something went wrong:");msgStack.push_back(ircSocket->errorString());
            }

}
void iRCProcessor::pushMsg(QString msgToSend){
    QByteArray msgArray;
    msgArray.append("PRIVMSG #"); //RFC Message Command to array;
    msgArray.append(channelName); //Append channel
    msgArray.append(" :"); //Append more RFC IRC special char
    msgArray.append(msgToSend);
    msgArray.append("\r\n"); //End Line Delmiters for IRC

    ircSocket->write(msgArray); //Send through TCP socket 6667
    ircSocket->flush(); // Flush any extra bytes that may be stray
    msgStack.push_back("iRC2Key Announce:" + msgToSend);

}

void iRCProcessor::connected(){
    msgStack.push_back( "Connection to IRC server Open, Listening on port 6667");
    msgStack.push_back("Sending IDENT as");
    msgStack.push_back(nickName);
    msgStack.push_back(":");
    msgStack.push_back(username) ;
//PASS
    if(t_password != NULL){
    QByteArray passIDENT;
   passIDENT.append("PASS ");
    passIDENT.append(t_password);
    passIDENT.append("\r\n");

           ircSocket->write(passIDENT);
             ircSocket->flush();
    }
    //Craft NSIdent And write to stream


    QByteArray nsIDENT;
    nsIDENT.append("NICK ");
    nsIDENT.append(nickName);
    nsIDENT.append("\r\n");

           ircSocket->write(nsIDENT);
             ircSocket->flush();
        //End of First ASYNC Flush

        //Craft USER Param required by most servers
        QByteArray userIDENT;
        userIDENT.append("USER ");
        userIDENT.append(nickName);
        userIDENT.append(" 8 *: ");
        userIDENT.append(realName);

         userIDENT.append("\r\n"); //RFC Valid Ident for USER and valid line end on the TCP stack

                ircSocket->write(userIDENT);
                ircSocket->flush();
    //Finally craft the channel join command (A.K.A where our viewers will send all their inputs)
    QByteArray channel_to_join;
    channel_to_join.append("JOIN #");
    channel_to_join.append(channelName);
            channel_to_join.append("\r\n");
    ircSocket->write(channel_to_join);
    ircSocket->flush();
}

void iRCProcessor::disconnected(){

}


void iRCProcessor::readyRead(){
        QByteArray array;
        while( !(array=ircSocket->readLine()).isNull()){
           msgStack.push_back(array);
           STL_Message_Parser(array);
           keepAlive(array);

        }
    }

void iRCProcessor::setupIRC(QString server, int port, QString nickname, QString realNameX, QString channelNameX, QString userName, QString t_passwordX){
    ircServer =  server;
   username = userName;
 realName = realNameX;
  nickName = nickname;
    channelName = channelNameX;
    t_password = t_passwordX;
    server_port = port;
}
//Could be removed in production version
void iRCProcessor::checkVals(){
    qDebug() << "Server:" << ircServer;
    qDebug() << "Nick:" << nickName;
    qDebug() << "Real Name:" << realName;
    qDebug() << "Username:" << username;
    qDebug() << "port:" << server_port;
    qDebug() << "--------------------------------------------------------------------------------------------------";

}
void iRCProcessor::closeToServer(){
    ircSocket->write("QUIT :Game Over Man, Game Over!\r\n");
    ircSocket->flush();
    ircSocket->disconnectFromHost();
}

QString iRCProcessor::keepAlive(QString ircMessage){

    if(ircMessage =="PING :tmi.twitch.tv"){
        pushMsg("PONG tmi.twitch.tv");
        qDebug() << ircMessage;
        qDebug() << "Sent PONG to Server As Response";
    }
    return 0;
}

QString iRCProcessor::STL_Message_Parser(QString ircMessage){
    QRegEx.setPattern("(?<=PRIVMSG\\s#"+ channelName +"\\s:).*");
    QRegExMatch = QRegEx.match(ircMessage);
    bool hasMatch = QRegExMatch.hasMatch();
    if(hasMatch){
        QString inboundUsrMsg = QRegExMatch.captured();
        //This is where we will test for different user inputs
        inboundUsrMsg.chop(1); // Remove the end of line character before we compare it
        //Update RC 0.2
        //Important: The delayer is only needed on the functions that return a message to the live stream as they could be abused and get the owner banned from twitch

        //Some bot functions

        if(inboundUsrMsg == "!time" && isSuspended == false){
            pushMsg(QTime::currentTime().toString());

        }

        if(inboundUsrMsg == "!game" && isSuspended == false){
            pushMsg(current_game);

        }

        if(inboundUsrMsg == "!fightclub" && isSuspended == false){
            pushMsg("Please do not talk about fight club...");

        }

        if(inboundUsrMsg == "!toxichawk" && isSuspended == false){
            pushMsg("Its said that those who wait will see the ends of time itself, sitting in the depths of the command center always watching.");

        }

        if(inboundUsrMsg == "!thecreator" && isSuspended == false){
            pushMsg("My name is Jesse, Jesse the creator!.");
             countDelay->start(1000);
        }
        if(inboundUsrMsg == "!weather" && isSuspended == false){
            pushMsg("Why?, It's not like you're ever going to go outside any way!.");

        }

        if(inboundUsrMsg == "!next" && isSuspended == false){
            streamMusic.nextSong();
            pushMsg("Next Song Started!");

        }

        if(inboundUsrMsg == "!prev" && isSuspended == false){
            streamMusic.prevSong();
            pushMsg("Previous Song Started!");

        }

        if(inboundUsrMsg == "!playmusic" && isSuspended == false){
            streamMusic.startPlaying(100,0);
            pushMsg("Music Player Started / Restarted!");

        }
        //Music Player Bot
    //Keyboard functions may have a ?Slow? function in the future
//Keyboard Functions
        if(inboundUsrMsg =="left" && isSuspended == false){
    keySim.SendKey(Key_G);
        }
        if(inboundUsrMsg =="right" && isSuspended == false){
keySim.SendKey(Key_J);
        }
        if(inboundUsrMsg =="up" && isSuspended == false){
keySim.SendKey(Key_Y);
        }
        if(inboundUsrMsg =="down" && isSuspended == false){
keySim.SendKey(Key_H);
        }
        if(inboundUsrMsg =="start" && isSuspended == false){
keySim.SendKey(Key_RETURN);
        }
        if(inboundUsrMsg =="space" && isSuspended == false){
keySim.SendKey(Key_SPACE);
        }
        if(inboundUsrMsg =="a" && isSuspended == false){
keySim.SendKey(Key_A);
        }
        if(inboundUsrMsg =="b" && isSuspended == false){
keySim.SendKey(Key_B);
        }


    }
    return 0;
}
//What are we Playing?
QString iRCProcessor::setCurrentGameTitle(QString currentGame){
    current_game = currentGame;
    return 0;
}

QString iRCProcessor::getCurrentGameTitle(){
    return current_game;
    return 0;
}

QString iRCProcessor::getUsername()
{
    return username;
}

void iRCProcessor::setSuspended(){
    isSuspended = true;
}
void iRCProcessor::setUnsuspended(){
}

bool iRCProcessor::waitForDelay(QCheckBox *delay_Checked, int timeInSec){
    if(delay_Checked->isCheckable() && timeSinceLastMsg < timeInSec){
        return true;
    }else{
        return false;
    }
}

void iRCProcessor::messageDelayer(){
timeSinceLastMsg++;
}
