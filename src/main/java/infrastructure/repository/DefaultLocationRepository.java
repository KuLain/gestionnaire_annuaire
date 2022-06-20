package infrastructure.repository;

import domain.model.Location;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.exceptions.NotInRepositoryException;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class DefaultLocationRepository implements LocationRepository {

    private final Set<Location> treeSet = new TreeSet<>();

    @Override
    public void add(Location location) {
        if (!treeSet.add(location)) throw new AlreadyExistInRepositoryException(location);
    }

    @Override
    public void remove(Location location) {
        if (!treeSet.remove(location)) throw new NotInRepositoryException(location);
    }

    @Override
    public Location searchWithName(String name) {
        Location location = null;
        List<Location> list = treeSet.stream().toList();
        int beginIndex = 0;
        int endIndex = treeSet.size() - 1;

        while (beginIndex <= endIndex) {
            int middleIndex = (beginIndex + endIndex) / 2;
            location = list.get(middleIndex);
            if (location.getCity().compareTo(name) == 0) {
                return location;
            } else if (location.getCity().compareTo(name) > 0) {
                endIndex = middleIndex - 1;
            } else {
                beginIndex = middleIndex + 1;
            }
        }

        return location;
    }

    @Override
    public Location searchWithPostalCode(String postalCode) {
        return treeSet.stream()
                .filter(location -> location.getPostalCode().equals(postalCode))
                .findFirst()
                .orElse(null);
    }

    @Override
    public List<Location> getListLocations() {
        return treeSet.stream().toList();
    }
}
