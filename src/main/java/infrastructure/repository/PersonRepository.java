package infrastructure.repository;

import domain.model.Person;

import java.util.List;

public interface PersonRepository {

    void add(Person person);
    void remove(Person person);
    Person searchWithMail(String firstName, String lastName, String mail);
    Person searchWithPhone(String firstName, String lastName, String phoneNumber);
    void clear();
    List<Person> getListPerson();

}
