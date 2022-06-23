package domain.model;

public class Location {

    private final String city;
    private final String postalCode;


    public Location(String city, String postalCode) {
        this.city = city;
        this.postalCode = postalCode;
    }

    public String getCity() {
        return city;
    }

    public String getPostalCode() {
        return postalCode;
    }

    @Override
    public String toString() {
        return city + " at " + postalCode;
    }
}
