package domain.application;

import domain.model.Contact;
import domain.model.Identity;
import domain.model.Location;
import domain.model.Person;

public class PersonBuilder {

    private final Person person;

    private PersonBuilder() {
        person = new Person();
    }

    public Person build() {
        return person;
    }

    public static PersonBuilder generatePerson() {
        return new PersonBuilder();
    }

    public PersonBuilder withIdentity(String firstName, String lastName) {
        person.setIdentity(new Identity(firstName, lastName));
        return this;
    }

    public PersonBuilder withLocation(String city, String postalCode) {
        person.setLocation(new Location(city, postalCode));
        return this;
    }

    public PersonBuilder withContact(String phone, String mail) {
        person.setContact(new Contact(phone, mail));
        return this;
    }

    public PersonBuilder withJob(String job) {
        person.setJob(job);
        return this;
    }



}
