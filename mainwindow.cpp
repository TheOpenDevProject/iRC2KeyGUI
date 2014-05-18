#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKit/QWebSettings>
#include <QInputDialog>
#include <QMessageBox>
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    msgConsoleTimer = new QTimer(this);
    timeStreamLiveTimer = new QTimer(this);
    connect(msgConsoleTimer,SIGNAL(timeout()),this,SLOT(msgConsole()));
    connect(timeStreamLiveTimer,SIGNAL(timeout()),this,SLOT(timeStreamLive()));
    connect(current_time_timer,SIGNAL(timeout()),this,SLOT(realtime_Music_Info()));
    QWidget::setFixedWidth(879);
    QWidget::setFixedHeight(753);

    vWin.show();
    vWin.setModeDisplaying("Mode: Chaos");
     ui->setupUi(this);



 s_data = new QStringListModel(song_sList);
 ui->songList->setModel(s_data);
 s_data->setStringList(ircKey.streamMusic.song_in_dir);
 current_time_timer->start(100); //Update at 100ms intervals, this is fast enough because we are only looking for secconds anway

}

MainWindow::~MainWindow()
{
  delete s_data;
    delete current_time_timer;
    delete ui;

}

void MainWindow::msgConsole(){
   for(int i=0;i<ircKey.msgStack.size();i++){
       if(i> prevIttr){
  ui->outputConsole->append(ircKey.msgStack.at(i));
  vWin.appendToDisplay(ircKey.msgStack.at(i),false);
  prevIttr++;
     }

 }


}


void MainWindow::on_connect_bttn_clicked()
{
   // ircKey.setupIRC("irc.twitch.tv",6667,"irc2key","Slim Shayde","irc2key","TwitchPlaysN64|BOT");
   //To connect to a twitch tv stream we use the following params in the following order
    //Server,port,Twitch username,Name,Twitch Channel,username,username,oath token(Generated on twitch.tv)
    ircKey.setupIRC("irc.twitch.tv",6667,ui->twitchUsrEdit->text(),"iRC2KeyDev",ui->twitchUsrEdit->text(),ui->twitchUsrEdit->text(),ui->oAuthTokenEdit->text());
    vWin.initRegex(ui->twitchUsrEdit->text());
    ircKey.openToServer();
  prevIttr = -1;
    ui->connect_bttn->setEnabled(false);
    ui->disconnect_bttn->setEnabled(true);
   msgConsoleTimer->start(100);
    timeStreamLiveTimer->start(1000); //Since we measure in sec
    ui->statusLbl->setText("Status: Listening!");


}

void MainWindow::on_pushMsg_clicked()
{
    ircKey.pushMsg(ui->Announce_msg->text());
}

void MainWindow::on_disconnect_bttn_clicked()
{
    ircKey.closeToServer();
    ui->connect_bttn->setEnabled(true);
    ui->disconnect_bttn->setEnabled(false);
    timeStreamLiveTimer->stop();
    ui->statusLbl->setText("Status: Not Listening!");

}
void MainWindow::timeStreamLive(){
    timeStreamLiveNth++;
   ui->elapsedTime->display(timeStreamLiveNth);
   vWin.setDisplayCurrentStreamTime("Live Time:" + QString::number(timeStreamLiveNth));
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_F6){
        ircKey.setSuspended();
        ui->statusLbl->setText("Status: Suspended!");
    }
    if(event->key() == Qt::Key_F7){
        ircKey.setUnsuspended();
        ui->statusLbl->setText("Status: Listening!");
    }
}

void MainWindow::on_actionRemove_Chat_Limit_triggered()
{
    ircKey.pushMsg("/slowoff");
}

void MainWindow::on_actionEnable_Chat_Limit_triggered()
{
    ircKey.pushMsg("/slow 6");
}

void MainWindow::on_actionBan_User_triggered()
{
    bool ok = false;
    QString userToBan = QInputDialog::getText(this,tr("Enter Twitch User To Ban"),tr("Username"),QLineEdit::Normal,0,&ok);
        qDebug() << ok;
    if(ok){
    ircKey.pushMsg("/ban " + userToBan);
    ircKey.msgStack.push_back("User:" + userToBan + " BANNED!");
        }
    }

void MainWindow::on_actionUnban_User_triggered()
{
    bool ok = false;
    QString userToUnBan = QInputDialog::getText(this,tr("Enter Twitch User To Un-Ban"),tr("Username"),QLineEdit::Normal,0,&ok);
        qDebug() << ok;
    if(ok){
    ircKey.pushMsg("/unban " + userToUnBan);
    ircKey.msgStack.push_back("User:" + userToUnBan + " Unbanned");
        }
}

void MainWindow::on_actionAbout_The_Team_triggered()
{
      QMessageBox aboutTeam;

    aboutTeam.setText("Project was inspired by TwitchPlaysPokemon 2014");
    aboutTeam.exec();
    aboutTeam.setText("Special Thanks To: @Riot ToxicHawk (Inspired me to finish this project), @Taco Cookie (Many nights keeping me entertained), @freenode - #qt (These guys spent many nights making me a better developer), And most importantly everyone who has spent time helping me test it! you guys make these things possible");
    aboutTeam.exec();
}

void MainWindow::on_actionAdd_Moderator_triggered()
{
    bool ok = false;
    QString userToMod = QInputDialog::getText(this,tr("Enter Twitch User Make Moderator"),tr("Username"),QLineEdit::Normal,0,&ok);
        qDebug() << ok;
    if(ok){
    ircKey.pushMsg("/mod " + userToMod);
    ircKey.msgStack.push_back("User:" + userToMod + " Is Now A Moderator!");
        }
}

void MainWindow::on_setTitleBttn_clicked()
{
    ircKey.setCurrentGameTitle(ui->gameTitleEdit->text());
    ircKey.msgStack.push_back("Game Title Changed:" + ircKey.getCurrentGameTitle());
}

void MainWindow::on_actionClear_Chat_box_triggered()
{
    ircKey.pushMsg("/clear");
}

void MainWindow::on_actionRemove_Moderator_triggered()
{
    bool ok = false;
    QString userToUnMod = QInputDialog::getText(this,tr("Enter Twitch User To Demote"),tr("Username"),QLineEdit::Normal,0,&ok);
    qDebug() << ok;
    if(ok){
    ircKey.pushMsg("/unmod " + userToUnMod);
    ircKey.msgStack.push_back("User:" + userToUnMod + " Is No Longer A Moderator!");
        }
}

void MainWindow::on_pushButton_clicked()
{
//Temporary Function Calls Should Not be distributed
      ircKey.streamMusic.startPlaying(100,0);
      for(int i = 0; i < ircKey.streamMusic.getMetaInfo().size();i++){
          ui->metaData_lbl->setText(ui->metaData_lbl->text() + ircKey.streamMusic.getMetaInfo().at(i));
      }

}

void MainWindow::on_pushButton_2_clicked()
{
  ircKey.streamMusic.nextSong();
}

void MainWindow::on_pushButton_3_clicked()
{
    ircKey.streamMusic.prevSong();
}

void MainWindow::on_musicScanBttn_clicked()
{
    ircKey.streamMusic.rebuildPlaylist();
     s_data->setStringList(ircKey.streamMusic.song_in_dir);
}

void MainWindow::realtime_Music_Info(){
    ui->c_time_music->setText(QString::number(ircKey.streamMusic.getTimeElapsed()));
}

void MainWindow::on_pushButton_4_clicked()
{
    QColorDialog *colourPicker = new QColorDialog;

    QColor cPickerSelected = colourPicker->getRgba();
    if(!colourPicker->isActiveWindow()){
        this->setStyleSheet("background-color: rgb(" + QString::number(cPickerSelected.red()) + "," + QString::number(cPickerSelected.green()) + "," + QString::number(cPickerSelected.blue()) + "," + ");");
        delete colourPicker;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QColorDialog *colourPicker = new QColorDialog;

    QColor cPickerSelected = colourPicker->getRgba();
    if(!colourPicker->isActiveWindow()){
        vWin.setBackgroundColor(cPickerSelected);
        delete colourPicker;
    }
}
