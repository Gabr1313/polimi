package gabr.pattern.mvc;

import java.util.List;

// Application model: contains a list of songs and the id of the current song
// We assume that the list of songs is not empty for simplicity
public class MusicLibraryModel {
    private final List<Song> songs;
    private int nextSong;

    public MusicLibraryModel(List<Song> songs) {
        this.songs = songs;
        this.nextSong = 0;
    }

    public Song getNextSong() {
        Song result = songs.get(nextSong);
        nextSong = (nextSong + 1) % songs.size();
        return result;
    }
}
