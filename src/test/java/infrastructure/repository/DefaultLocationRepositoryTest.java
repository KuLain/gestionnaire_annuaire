package infrastructure.repository;

import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.exceptions.NotInRepositoryException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.*;

class DefaultLocationRepositoryTest {

    LocationRepository locationRepository;
    Location location1;
    Location location2;

    @BeforeEach
    void setUp() {
        locationRepository = new DefaultLocationRepository();
        location1 = new Location("Lyon", "69000");
        location2 = new Location("Marseille", "13000");
    }

    @Test
    void add_shouldAddLocationToRepository_whenLocationNotInRepository() {
        locationRepository.add(location1);
        assertEquals(1, locationRepository.getListLocations().size());
        assertThat(locationRepository.getListLocations()).contains(location1);
    }

    @Test
    void add_shouldNotAddLocationToRepository_whenLocationAlreadyInRepository() {
        locationRepository.add(location1);
        assertThrows(AlreadyExistInRepositoryException.class, () -> locationRepository.add(location1));
    }

    @Test
    void remove_shouldRemoveLocationFromRepository_whenLocationInRepository() {
        locationRepository.add(location1);
        locationRepository.remove(location1);
        assertEquals(0, locationRepository.getListLocations().size());
        assertThat(locationRepository.getListLocations()).isEmpty();
        assertThat(locationRepository.getListLocations()).doesNotContain(location1);
    }

    @Test
    void remove_shouldNotRemoveLocationFromRepository_whenLocationNotInRepository() {
        assertThrows(NotInRepositoryException.class, () -> locationRepository.remove(location1));
    }

    @Test
    void searchWithName_shouldReturnLocation_whenLocationInRepository() {
        locationRepository.add(location1);
        assertEquals(location1, locationRepository.searchWithName("Lyon"));
    }

    @Test
    void searchWithName_shouldReturnNull_whenLocationNotInRepository() {
        assertNull(locationRepository.searchWithName("Lyon"));
    }

    @Test
    void searchWithPostalCode_shouldReturnLocation_whenLocationInRepository() {
        locationRepository.add(location1);
        assertEquals(location1, locationRepository.searchWithPostalCode("69000"));
    }

    @Test
    void searchWithPostalCode_shouldReturnNull_whenLocationNotInRepository() {
        assertNull(locationRepository.searchWithPostalCode("69000"));
    }
}