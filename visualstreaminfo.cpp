#include "visualstreaminfo.h"
#include "ui_visualstreaminfo.h"
#include <QDebug>
#include <QPixmap>
VisualStreamInfo::VisualStreamInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualStreamInfo)
{
    ui->setupUi(this);
    //updateTime = new QTimer(this);
    //connect(updateTime,SIGNAL(timeout()),this,SLOT(updateToTimeElapsed()));
          //  updateTime->start(200);

}

VisualStreamInfo::~VisualStreamInfo()
{
    delete ui;
}
void VisualStreamInfo::updateToTimeElapsed(){

}

void VisualStreamInfo::setModeDisplaying(QString stream_mode){
    ui->liveTime_2->setText(stream_mode);
}

void VisualStreamInfo::setDisplayCurrentStreamTime(QString stream_time){
    ui->liveTime->setText(stream_time);
}
void VisualStreamInfo::appendToDisplay(QString stream_data, bool verbose){
    stream_regex_match = stream_regex.match(stream_data);
    QString stripped_message = stream_regex_match.captured();
    QPixmap pixmap(":/res/icons/up_arrow.png");
    bool hasMatch = stream_regex_match.hasMatch();
    qDebug() << hasMatch;
    stripped_message.chop(1);
    if(hasMatch){
        if(stripped_message == "up"){

            ui->textBrowser->append(" <img src=\":/icons/up_arrow.png\" />");
        }

    if(stripped_message == "down"){

        ui->textBrowser->append(" <img src=\":/icons/down_arrow.png\" />");
    }
if(stripped_message == "left"){

    ui->textBrowser->append(" <img src=\":/icons/left_arrow.png\" />");
}

if(stripped_message == "right"){

    ui->textBrowser->append(" <img src=\":/icons/right_arrow.png\" />");
}
    }
}

void VisualStreamInfo::setBackgroundColor(QColor cPickerSelected)
{
    this->setStyleSheet("background-color: rgb(" + QString::number(cPickerSelected.red()) + "," + QString::number(cPickerSelected.green()) + "," + QString::number(cPickerSelected.blue()) + "," + ");");
}

void VisualStreamInfo::initRegex(QString stream_name){
    stream_regex.setPattern("(?<=PRIVMSG\\s#"+ stream_name +"\\s:).*");
    qDebug() << stream_regex.pattern();
}
