package domain.model;

import java.util.Objects;

public class Identity {

    private final String firstName;
    private final String lastName;

    public Identity(String firstName, String lastname) {
        this.firstName = firstName;
        this.lastName = lastname;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    @Override
    public String toString() {
        return firstName + " " + lastName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Identity identity = (Identity) o;
        return Objects.equals(firstName, identity.firstName) && Objects.equals(lastName, identity.lastName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName);
    }
}
