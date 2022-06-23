package ui.swing;

import infrastructure.loader.FilePath;
import infrastructure.loader.PersonLoader;
import infrastructure.repository.PersonRepository;
import ui.HomeUI;
import ui.PathUI;

import javax.inject.Inject;

public class SwingPathUI implements PathUI {

    private final FilePath filePath;
    private final PersonRepository personRepository;
    private final PersonLoader personLoader;
    private final HomeUI homeUI;

    @Inject
    public SwingPathUI(FilePath filePath, PersonRepository personRepository, PersonLoader personLoader, HomeUI homeUI) {
        this.filePath = filePath;
        this.personRepository = personRepository;
        this.personLoader = personLoader;
        this.homeUI = homeUI;
    }

    @Override
    public void changePath(String newPath) {
        filePath.changePath(newPath);
        personRepository.clear();
        personLoader.load();
        homeUI.interact();
    }
}
