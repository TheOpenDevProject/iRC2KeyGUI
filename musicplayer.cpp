#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{
    music_Player = new QMediaPlayer;
    songList = new QMediaPlaylist; //Pass the music player in
    //DO NOT FORGET TO DELETE THESE OFF THE HEAP!
    music_Player->setPlaylist(songList);
    buildPlaylistFromDirectory();
    //Build our playlist from the QStringList
    for(int i = 0; i < song_in_dir.size(); i++){
    addSong(song_in_dir.at(i));
         }
}

MusicPlayer::~MusicPlayer(){
delete music_Player;
delete songList;
//End House-Keeping
}


void MusicPlayer::addSong(QString fileName){
       songList->addMedia(QUrl::fromLocalFile(songPath + fileName));
       qDebug() << songList;

}

void MusicPlayer::startPlaying(int volume,int startSong){
    songList->setCurrentIndex(startSong);
        music_Player->setVolume(volume);
    music_Player->play();
}

void MusicPlayer:: nextSong(){
    //Note: QMediaPlaylistNavigator will handle our playlist end of bounds and restart index at 0
startPlaying(100,songList->currentIndex() + 1);
}

void MusicPlayer::prevSong(){
    //Note: QMediaPlaylistNavigator will handle our playlist end of bounds and restart index at 0
startPlaying(100,songList->currentIndex() - 1);
}

void MusicPlayer::pause(){
    music_Player->pause();
}

void MusicPlayer::continuePlaying(){
    music_Player->play();
}

QStringList MusicPlayer::getMetaInfo(){
    if(music_Player->isMetaDataAvailable()){
        qDebug() << "Meta Data Is Available";
    }else{
        qDebug() << "No Meta Data Found!";
    }
    return music_Player->availableMetaData();
}

void MusicPlayer::setCustomMusicDirectory(QString wDirectory){
   songPath = wDirectory;

}
void MusicPlayer::buildPlaylistFromDirectory(){
   musicDirectory.setPath(songPath);
    song_in_dir = musicDirectory.entryList();
    song_in_dir.removeFirst(); //Remove the first two elements because some hidden bullshit in the folder
   song_in_dir.removeFirst();
}

double MusicPlayer::getTimeElapsed(){
    return music_Player->position() / 1000; //Return time in Seconds
}
