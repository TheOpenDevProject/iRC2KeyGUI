#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QtMultimedia/QtMultimedia>
#include <QStringList>
#include <QDir>

class MusicPlayer
{
public:
    MusicPlayer();
   ~MusicPlayer();
    void addSong(QString fileName);
    void startPlaying(int volume,int startSong);
    void nextSong();
    void prevSong();
    void pause();
    void continuePlaying();

    void setCustomMusicDirectory(QString wDirectory);
    void  rebuildPlaylist(){
       buildPlaylistFromDirectory();
    }
    QStringList getMetaInfo();

   QStringList song_in_dir;

    double getTimeElapsed();
private:
    QMediaPlayer *music_Player;
    QMediaPlaylist *songList;
    QString songPath = "music/"; //Set default to music directory
    void buildPlaylistFromDirectory();
    protected:
    QDir musicDirectory;

};

#endif // MUSICPLAYER_H
