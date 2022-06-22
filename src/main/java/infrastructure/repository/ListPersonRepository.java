package infrastructure.repository;

import com.google.inject.Singleton;
import domain.model.Person;

import java.util.ArrayList;
import java.util.List;

@Singleton
public class ListPersonRepository implements PersonRepository {

    private final List<Person> listPerson = new ArrayList<>();

    @Override
    public void add(Person person) {
        listPerson.add(person);
    }

    @Override
    public void remove(Person person) {
        listPerson.remove(person);
    }

    @Override
    public Person searchWithMail(String firstName, String lastName, String mail) {
        return listPerson.stream()
                .filter(person -> person.getIdentity().getFirstName().equals(firstName))
                .filter(person -> person.getIdentity().getLastName().equals(lastName))
                .filter(person -> person.getContact().getEmailAdress().equals(mail))
                .findFirst()
                .orElse(null);
    }

    @Override
    public Person searchWithPhone(String firstName, String lastName, String phoneNumber) {
        return listPerson.stream()
                .filter(person -> person.getIdentity().getFirstName().equals(firstName))
                .filter(person -> person.getIdentity().getLastName().equals(lastName))
                .filter(person -> person.getContact().getPhone().equals(phoneNumber))
                .findFirst()
                .orElse(null);
    }

    @Override
    public void clear() {
        listPerson.clear();
    }

    @Override
    public List<Person> getListPerson() {
        return listPerson;
    }
}
