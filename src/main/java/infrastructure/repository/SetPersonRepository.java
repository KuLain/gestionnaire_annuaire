package infrastructure.repository;

import com.google.inject.Singleton;
import domain.model.Person;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.exceptions.NotInRepositoryException;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;

@Singleton
public class SetPersonRepository implements PersonRepository {

    private final Set<Person> personSet = new TreeSet<>();

    @Override
    public void add(Person person) {
        if (!personSet.add(person)) throw new AlreadyExistInRepositoryException(person);
    }

    @Override
    public void remove(Person person) {
        if (!personSet.remove(person)) throw new NotInRepositoryException(person);
    }

    @Override
    public Person searchWithMail(String firstName, String lastName, String mail) {
        return personSet.stream()
                .filter(person -> person.getIdentity().getFirstName().equals(firstName))
                .filter(person -> person.getIdentity().getLastName().equals(lastName))
                .filter(person -> person.getContact().getEmailAdress().equals(mail))
                .findFirst()
                .orElse(null);
    }

    @Override
    public Person searchWithPhone(String firstName, String lastName, String phoneNumber) {
        return personSet.stream()
                .filter(person -> person.getIdentity().getFirstName().equals(firstName))
                .filter(person -> person.getIdentity().getLastName().equals(lastName))
                .filter(person -> person.getContact().getPhone().equals(phoneNumber))
                .findFirst()
                .orElse(null);
    }

    @Override
    public void clear() {
        personSet.clear();
    }

    @Override
    public List<Person> getListPerson() {
        return personSet.stream().toList();
    }
}
