package it.polimi.softeng.pattern_solutions.mvc2;

import java.util.ArrayList;
import java.util.List;

// Application model: contains a list of songs and the id of the current song
// We assume that the list of songs is not empty for simplicity
public class MusicLibraryModel {
    private final List<Song> songs;
    private final List<MusicLibraryModelObserver> observers;
    private int nextSong;

    public MusicLibraryModel(List<Song> songs, MusicAppView view) {
        this.songs = songs;
        this.observers = new ArrayList<>();
        this.nextSong = 0;
        observers.add(view);
    }

    public void nextSong() {
        final Song song = songs.get(nextSong);
        nextSong = (nextSong+1) % songs.size();
        observers.forEach(observer -> observer.modelChanged(song));
    }
}