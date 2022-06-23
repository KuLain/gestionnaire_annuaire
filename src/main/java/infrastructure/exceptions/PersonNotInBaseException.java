package infrastructure.exceptions;

import domain.model.Person;

public class PersonNotInBaseException extends RuntimeException {

    public PersonNotInBaseException(Person person) {
        super(person + " not in base.");
    }

    public PersonNotInBaseException(String firstName, String lastName) {
        super(firstName + " " + lastName + " not in base.");
    }

}
