package infrastructure.repository;

import domain.model.Location;

public interface CityRepository {

    void add(Location location);
    void remove(Location location);
    Location searchWithName(String name);
    Location searchWithPostalCode(String postalCode);

}
