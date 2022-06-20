package domain.application;

import domain.model.Person;
import infrastructure.repository.PersonRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
class SortWithCriteriaServiceTest {

    SortWithCriteriaService service;
    @Mock
    PersonRepository personRepository;
    Person person1;
    Person person2;
    Person person3;

    @BeforeEach
    void setUp() {
        service = new SortWithCriteriaService(personRepository);
        person1 = PersonBuilder.generatePerson()
                .withIdentity("John", "Doe")
                .withLocation("New York", "10010")
                .withContact("0123456789", "john@gmail.com")
                .withJob("Software Engineer")
                .build();
        person2 = PersonBuilder.generatePerson()
                .withIdentity("Jane", "Doe")
                .withLocation("Paris", "75001")
                .withContact("09876543210", "jane@gmail.com")
                .withJob("Doctor")
                .build();
        person3 = PersonBuilder.generatePerson()
                .withIdentity("UwU", "OwO")
                .withLocation("Tokyo", "13000")
                .withContact("091827364", "uwu@gmail.com")
                .withJob("Student")
                .build();
        when(personRepository.getListPerson()).thenReturn(List.of(person2, person1, person3));
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByCityASC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.CITY, Order.ASC);
        assertThat(sortedList).containsExactly(person1, person2, person3);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByCityDESC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.CITY, Order.DESC);
        assertThat(sortedList).containsExactly(person3, person2, person1);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByPostalCodeASC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.POSTAL_CODE, Order.ASC);
        assertThat(sortedList).containsExactly(person1, person3, person2);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByPostalCodeDESC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.POSTAL_CODE, Order.DESC);
        assertThat(sortedList).containsExactly(person2, person3, person1);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByPhoneNumberASC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.PHONE_NUMBER, Order.ASC);
        assertThat(sortedList).containsExactly(person1, person3, person2);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByPhoneNumberDESC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.PHONE_NUMBER, Order.DESC);
        assertThat(sortedList).containsExactly(person2, person3, person1);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByEmailASC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.EMAIL, Order.ASC);
        assertThat(sortedList).containsExactly(person2, person1, person3);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByEmailDESC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.EMAIL, Order.DESC);
        assertThat(sortedList).containsExactly(person3, person1, person2);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByJobASC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.JOB, Order.ASC);
        assertThat(sortedList).containsExactly(person2, person1, person3);
    }

    @Test
    void sortWithCriteria_shouldReturnSortedList_whenSortingByJobDESC() {
        List<Person> sortedList = service.sortWithCriteria(SortingCriteria.JOB, Order.DESC);
        assertThat(sortedList).containsExactly(person3, person1, person2);
    }
}