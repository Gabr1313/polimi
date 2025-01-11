package gabr.pattern.mvc;

import java.util.List;
import java.util.ArrayList;

// User interface of the app
public class MusicAppView {
    private final List<ClickObserver> clickObserverList = new ArrayList<>();

    public void addClickObserver(ClickObserver clickObserver) {
        this.clickObserverList.add(clickObserver);
    }

    // The user clicked on the "next" button
    // This should update the music library (move to the next song) and the user
    // interface (update current song)
    public void clickNext() {
        clickObserverList.forEach(ClickObserver::onClick);
    }

    // Display the current song (as a simple example, it prints the title)
    public void updateCurrentSong(Song s) {
        System.out.println(s.getTitle());
    }
}
