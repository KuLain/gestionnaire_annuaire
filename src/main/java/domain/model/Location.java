package domain.model;

import java.util.Objects;

public class Location implements Comparable<Location>{

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
        return city + ", " + postalCode;
    }


    @Override
    public int compareTo(Location o) {
        return city.compareTo(o.city);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Location location = (Location) o;
        return Objects.equals(city, location.city) && Objects.equals(postalCode, location.postalCode);
    }

    @Override
    public int hashCode() {
        return Objects.hash(city, postalCode);
    }
}
