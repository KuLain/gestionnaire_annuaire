package domain.model;

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
        return  emailAdress + " " + phone;
    }
}
