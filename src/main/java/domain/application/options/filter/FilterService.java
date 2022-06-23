package domain.application.options.filter;

import domain.application.options.sort.SortingCriteria;
import domain.model.Person;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.util.ArrayList;
import java.util.List;

public class FilterService {

    private final PersonRepository personRepository;

    @Inject
    public FilterService(PersonRepository personRepository) {
        this.personRepository = personRepository;
    }

    public List<Person> filter(String pattern, SortingCriteria sortingCriteria) {
        List<Person> matchingPersons = new ArrayList<>();

        for (Person person : personRepository.getListPerson()) {
            switch (sortingCriteria) {
                case FIRST_NAME:
                    if (person.getIdentity().getFirstName().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case LAST_NAME:
                    if (person.getIdentity().getLastName().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case CITY:
                    if (person.getLocation().getCity().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case POSTAL_CODE:
                    if (person.getLocation().getPostalCode().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case PHONE_NUMBER:
                    if (person.getContact().getPhone().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case EMAIL:
                    if (person.getContact().getEmailAdress().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
                case JOB:
                    if (person.getJob().contains(pattern)) {
                        matchingPersons.add(person);
                    }
                    break;
            }
        }

        return matchingPersons;
    }

}
