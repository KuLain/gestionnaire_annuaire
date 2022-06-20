package domain.application.options.missing;

import domain.model.Person;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.util.ArrayList;
import java.util.List;

public class MissingInfoService {

    private final PersonRepository personRepository;

    @Inject
    public MissingInfoService(PersonRepository personRepository) {
        this.personRepository = personRepository;
    }

    public List<Person> findPersonsWithMissingInfos() {
        List<Person> personList = new ArrayList<>();

        for (Person person : personRepository.getListPerson()) {
            if (hasMissingInfo(person)) personList.add(person);
        }

        return personList;
    }

    private boolean hasMissingInfo(Person person) {
        Object[] attributes = new Object[]{person.getIdentity(), person.getLocation(),
                person.getContact(), person.getJob()};
        for (Object o : attributes) {
            if (o == null) return true;
        }

        return person.getJob() == null || person.getJob().equals("")
                || person.getContact().getPhone() == null || person.getContact().getPhone().equals("")
                || person.getContact().getEmailAdress() == null || person.getContact().getEmailAdress().equals("")
                || person.getLocation().getPostalCode() == null || person.getLocation().getPostalCode().equals("")
                || person.getLocation().getCity() == null || person.getLocation().getCity().equals("")
                || person.getIdentity().getLastName() == null || person.getIdentity().getLastName().equals("")
                || person.getIdentity().getFirstName() == null || person.getIdentity().getFirstName().equals("")
                ;
    }
}
