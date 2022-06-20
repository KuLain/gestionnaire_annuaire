package infrastructure.repository;

import domain.application.PersonBuilder;
import domain.model.Person;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.exceptions.NotInRepositoryException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.*;

class DefaultPersonRepositoryTest {

    PersonRepository personRepository;
    Person person1;
    Person person2;

    @BeforeEach
    void setUp() {
        personRepository = new DefaultPersonRepository();
        person1 = PersonBuilder.generatePerson()
                .withIdentity("Joel", "Miller")
                .withContact("0123456789", "joelmiller@gmail.com")
                .withLocation("Paris", "75000")
                .withJob("Supplier")
                .build();
        person2 = PersonBuilder.generatePerson()
                .withIdentity("Ellie", "Smith")
                .withContact("0123456798", "ellie@gmail.com")
                .withLocation("Marseille", "13000")
                .withJob("Fighter")
                .build();
    }

    @Test
    void add_shouldAddPersonToRepository_whenPersonNotInRepository() {
        personRepository.add(person1);
        personRepository.add(person2);
        assertEquals(2, personRepository.getListPerson().size());
        assertThat(personRepository.getListPerson()).containsExactlyInAnyOrder(person1, person2);
    }

    @Test
    void add_shouldThrowException_whenPersonAlreadyInRepository() {
        personRepository.add(person1);
        assertThrows(AlreadyExistInRepositoryException.class, () -> personRepository.add(person1));
    }

    @Test
    void remove_shouldRemovePersonFromRepository_whenPersonInRepository() {
        personRepository.add(person1);
        personRepository.add(person2);
        personRepository.remove(person1);
        assertEquals(1, personRepository.getListPerson().size());
        assertThat(personRepository.getListPerson()).containsOnly(person2);
    }

    @Test
    void remove_shouldThrowException_whenPersonNotInRepository() {
        assertThrows(NotInRepositoryException.class, () -> personRepository.remove(person1));
    }

    @Test
    void searchWithMail_shouldReturnPerson_whenPersonInRepository() {
        personRepository.add(person1);
        personRepository.add(person2);
        assertEquals(person1, personRepository.searchWithMail("Joel", "Miller", "joelmiller@gmail.com"));
    }

    @Test
    void searchWithMail_shouldReturnNull_whenPersonNotInRepository() {
        assertNull(personRepository.searchWithMail("Joel", "Miller", "joelmiller@gmail.com"));
    }

    @Test
    void searchWithPhone_shouldReturnPerson_whenPersonInRepository() {
        personRepository.add(person1);
        personRepository.add(person2);
        assertEquals(person1, personRepository.searchWithPhone("Joel", "Miller", "0123456789"));
    }

    @Test
    void searchWithPhone_shouldReturnNull_whenPersonNotInRepository() {
        assertNull(personRepository.searchWithPhone("Joel", "Miller", "0123456789"));
    }
}