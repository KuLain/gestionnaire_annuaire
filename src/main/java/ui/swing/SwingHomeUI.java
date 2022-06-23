package ui.swing;

import infrastructure.repository.PersonRepository;
import ui.HomeUI;
import view.HomeView;

import javax.inject.Inject;

public class SwingHomeUI implements HomeUI {

    private final PersonRepository personRepository;
    private final HomeView homeView;

    @Inject
    public SwingHomeUI(PersonRepository personRepository, HomeView homeView) {
        this.personRepository = personRepository;
        this.homeView = homeView;
    }

    @Override
    public void interact() {
        homeView.display(personRepository.getListPerson());
    }
}
