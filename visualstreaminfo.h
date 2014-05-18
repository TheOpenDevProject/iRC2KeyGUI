#ifndef VISUALSTREAMINFO_H
#define VISUALSTREAMINFO_H

#include <QWidget>
#include <QTimer>
#include <QRegularExpressionMatch>

namespace Ui {
class VisualStreamInfo;
}

class VisualStreamInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit VisualStreamInfo(QWidget *parent = 0);
    void setModeDisplaying(QString stream_mode);
    void setDisplayCurrentStreamTime(QString stream_time);
    void appendToDisplay(QString stream_data,bool verbose);
    void setBackgroundColor(QColor cPickerSelected);
    //QTimer *updateTime;
    QString channel_name;
 void initRegex(QString stream_name);
    ~VisualStreamInfo();

    
private slots:
    void updateToTimeElapsed();
private:
    Ui::VisualStreamInfo *ui;
        QRegularExpression stream_regex;
        QRegularExpressionMatch stream_regex_match;

};


#endif // VISUALSTREAMINFO_H
