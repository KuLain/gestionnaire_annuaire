package infrastructure.loader;

import infrastructure.repository.DefaultLocationRepository;
import infrastructure.repository.DefaultPersonRepository;
import infrastructure.repository.LocationRepository;
import infrastructure.repository.PersonRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;

import static org.junit.jupiter.api.Assertions.*;

class CSVPersonLoaderTest {

    PersonRepository personRepository;
    LocationRepository locationRepository;
    PersonLoader loader;

    @BeforeEach
    void setUp() {
        personRepository = new DefaultPersonRepository();
        locationRepository = new DefaultLocationRepository();
    }

    @Test
    void load_shouldLoadFullDataFromFile_whenDataInFileIsFull() {
        loader = new CSVPersonLoader(new FilePath("src/test/resources/1-Jeu de validation.csv"),
                personRepository, locationRepository);

        loader.load();

        assertEquals(9, personRepository.getListPerson().size());
        assertEquals(5, locationRepository.getListLocations().size());
    }

    @Test
    void load_shouldLoadDataFromFileWithoutDuplicate_whenFileContainsEmptyDataAndDuplicates() {
        loader = new CSVPersonLoader(new FilePath("src/test/resources/2-Jeu de validation.csv"),
                personRepository, locationRepository);

        loader.load();

        assertEquals(9, personRepository.getListPerson().size());
        assertEquals(6, locationRepository.getListLocations().size());
    }
}