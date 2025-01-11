package it.polimi.softeng.pattern_solutions.mvc2;

import java.util.ArrayList;
import java.util.List;

// User interface of the app
public class MusicAppView implements MusicLibraryModelObserver {
    private final List<ClickObserver> observerList = new ArrayList<>();

    public void addClickObserver(ClickObserver clickObserver) {
        observerList.add(clickObserver);
    }

    // The user clicked on the "next" button
    // This should update the music library (move to the next song) and the user interface (update current song)
    public void clickNext() {
        observerList.forEach(ClickObserver::onClick);
    }

    // Display the current song (as a simple example, it prints the title)
    private void updateCurrentSong(Song s) {
        System.out.println(s.getTitle());
    }

    @Override
    public void modelChanged(Song song) {
        updateCurrentSong(song);
    }
}
