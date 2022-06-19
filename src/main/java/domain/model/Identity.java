package domain.model;

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
}
