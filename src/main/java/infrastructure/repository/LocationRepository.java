package infrastructure.repository;

import domain.model.Location;

import java.util.List;

public interface LocationRepository {

    void add(Location location);
    void remove(Location location);
    Location searchWithName(String name);
    Location searchWithPostalCode(String postalCode);
    List<Location> getListLocations();

}
