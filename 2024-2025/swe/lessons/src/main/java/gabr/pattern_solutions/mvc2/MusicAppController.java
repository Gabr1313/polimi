package it.polimi.softeng.pattern_solutions.mvc2;

public class MusicAppController implements ClickObserver {
    private final MusicLibraryModel model;

    public MusicAppController(MusicLibraryModel model, MusicAppView view) {
        this.model = model;
        view.addClickObserver(this);
    }

    @Override
    public void onClick() {
        model.nextSong();
    }
}
