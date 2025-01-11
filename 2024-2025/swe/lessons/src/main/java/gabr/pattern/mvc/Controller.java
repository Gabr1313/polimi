package gabr.pattern.mvc;

public class Controller implements ClickObserver {
    private final MusicLibraryModel model;
    private final MusicAppView view;

    public Controller(MusicLibraryModel model, MusicAppView view) {
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
