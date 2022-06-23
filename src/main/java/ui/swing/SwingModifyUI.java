package ui.swing;

import domain.application.PersonBuilder;
import domain.model.Person;
import infrastructure.exceptions.PersonNotInBaseException;
import infrastructure.repository.PersonRepository;
import ui.HomeUI;
import ui.ModifyUI;
import ui.swing.components.SearchType;

import javax.inject.Inject;

public class SwingModifyUI implements ModifyUI {

    private final PersonRepository personRepository;
    private final HomeUI homeUI;

    @Inject
    public SwingModifyUI(PersonRepository personRepository, HomeUI homeUI) {
        this.personRepository = personRepository;
        this.homeUI = homeUI;
    }

    @Override
    public void interact(String[] fields, SearchType searchType) {
        if (searchType == null) {
            Person person = PersonBuilder.generatePerson()
                    .withIdentity(fields[0], fields[1])
                    .withLocation(fields[2], fields[3])
                    .withContact(fields[4], fields[5])
                    .withJob(fields[6])
                    .build();
            personRepository.add(person);
        } else {
            Person person = null;
            if (searchType == SearchType.EMAIL) {
                person = personRepository.searchWithMail(fields[0], fields[1], fields[2]);
            } else {
                person = personRepository.searchWithPhone(fields[0], fields[1], fields[2]);
            }
            if (person == null) throw new PersonNotInBaseException(fields[0], fields[1]);
        }
        homeUI.interact();
    }
}
