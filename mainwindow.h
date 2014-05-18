#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <ircprocessor.h>
#include <QKeyEvent>
#include <QStringList>
#include <QStringListModel>
#include <visualstreaminfo.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    iRCProcessor ircKey;
    QTimer *msgConsoleTimer;
        QString msgLog;
    QTimer *timeStreamLiveTimer;
    QTimer *current_time_timer = new QTimer(this); //Ewwwww
    QStringListModel *s_data;
    QStringList song_sList;
     VisualStreamInfo vWin;

protected:
    void keyPressEvent(QKeyEvent *);

    int timeStreamLiveNth = 0;
private:
    Ui::MainWindow *ui;
 int prevIttr;

private slots:
    void msgConsole();
    void timeStreamLive();
    void on_connect_bttn_clicked();
    void on_pushMsg_clicked();
    void on_disconnect_bttn_clicked();
    void on_actionRemove_Chat_Limit_triggered();
    void on_actionEnable_Chat_Limit_triggered();
    void on_actionBan_User_triggered();
    void on_actionUnban_User_triggered();
    void on_actionAbout_The_Team_triggered();
    void on_actionAdd_Moderator_triggered();
    void on_setTitleBttn_clicked();
    void on_actionClear_Chat_box_triggered();
    void on_actionRemove_Moderator_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_musicScanBttn_clicked();
    void  realtime_Music_Info();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
