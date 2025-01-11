package it.polimi.softeng.pattern_solutions.mvc;

public class MusicAppController implements ClickObserver {
    private final MusicLibraryModel model;
    private final MusicAppView view;

    public MusicAppController(MusicLibraryModel model, MusicAppView view) {
        this.model = model;
        this.view = view;
        view.addClickObserver(this);
    }

    @Override
    public void onClick() {
        Song newSong = model.getNextSong();
        view.updateCurrentSong(newSong);
    }
}
