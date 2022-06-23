package infrastructure.loader;

import infrastructure.repository.ListPersonRepository;
import infrastructure.repository.PersonRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class CSVPersonLoaderTest {

    PersonRepository personRepository;
    PersonLoader loader;

    @BeforeEach
    void setUp() {
        personRepository = new ListPersonRepository();
    }

    @Test
    void load_shouldLoadFullDataFromFile_whenDataInFileIsFull() {
        loader = new CSVPersonLoader(new FilePath("src/test/resources/1-Jeu de validation.csv"),
                personRepository);

        loader.load();

        assertEquals(9, personRepository.getListPerson().size());
    }

    @Test
    void load_shouldLoadDataFromFileWithoutDuplicate_whenFileContainsEmptyDataAndDuplicates() {
        loader = new CSVPersonLoader(new FilePath("src/test/resources/2-Jeu de validation.csv"),
                personRepository);

        loader.load();

        assertEquals(10, personRepository.getListPerson().size());
    }
}