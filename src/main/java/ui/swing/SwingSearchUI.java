package ui.swing;

import domain.model.Person;
import infrastructure.repository.PersonRepository;
import ui.SearchUI;
import ui.swing.components.SearchType;
import view.HomeView;
import view.SearchView;

import javax.inject.Inject;
import javax.swing.*;
import java.util.List;

public class SwingSearchUI implements SearchUI {

    private final SearchView searchView;
    private final PersonRepository personRepository;

    @Inject
    public SwingSearchUI(SearchView searchView, PersonRepository personRepository) {
        this.searchView = searchView;
        this.personRepository = personRepository;
    }

    @Override
    public void interact(String firstName, String lastName, String criteria, SearchType type) {
        Person person = null;
        if (type == SearchType.EMAIL) {
            person = personRepository.searchWithMail(firstName, lastName, criteria);
        } else if (type == SearchType.PHONE) {
            person = personRepository.searchWithPhone(firstName, lastName, criteria);
        }
        searchView.display(person);
    }
}
