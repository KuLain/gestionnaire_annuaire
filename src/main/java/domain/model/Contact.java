package domain.model;

import java.util.Objects;

public class Contact {

    private final String phone;
    private final String emailAdress;


    public Contact(String phone, String emailAdress) {
        this.phone = phone;
        this.emailAdress = emailAdress;
    }

    public String getPhone() {
        return phone;
    }

    public String getEmailAdress() {
        return emailAdress;
    }

    @Override
    public String toString() {
        return  emailAdress + " & " + phone;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Contact contact = (Contact) o;
        return Objects.equals(phone, contact.phone) && Objects.equals(emailAdress, contact.emailAdress);
    }

    @Override
    public int hashCode() {
        return Objects.hash(phone, emailAdress);
    }
}
