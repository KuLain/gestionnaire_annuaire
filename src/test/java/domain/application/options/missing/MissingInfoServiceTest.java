package domain.application.options.missing;

import domain.application.PersonBuilder;
import domain.model.Person;
import infrastructure.repository.PersonRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
class MissingInfoServiceTest {

    MissingInfoService service;

    @Mock
    PersonRepository personRepository;

    Person person1;
    Person person2;
    Person person3;

    @BeforeEach
    void setUp() {
        service = new MissingInfoService(personRepository);
        person1 = PersonBuilder.generatePerson()
                .withIdentity("Mark", "Evans")
                .withContact("0987654321", "mark@evans.com")
                .withLocation("Tokyo", "0190")
                .withJob("Goal à Raimon")
                .build();

        person2 = PersonBuilder.generatePerson()
                .withIdentity("Nelly", "Evans")
                .build();

        person3 = PersonBuilder.generatePerson()
                .withIdentity("Celia", "")
                .build();
    }

    @Test
    void findPersonsWithMissingInfo_shouldReturnListOfPersonWithMissingInfo_whenInfoAreNull() {
        when(personRepository.getListPerson()).thenReturn(Arrays.asList(person1, person2));

        assertEquals(Collections.singletonList(person2), service.findPersonsWithMissingInfos());
    }

    @Test
    void findPersonsWithMissingInfo_shouldReturnListOfPersonWithMissingInfo_whenInfoAreEmpty() {
        when(personRepository.getListPerson()).thenReturn(Arrays.asList(person3,person1));

        assertEquals(Collections.singletonList(person3), service.findPersonsWithMissingInfos());
    }

    @Test
    void findPersonsWithMissingInfo_shouldReturnEmptyList_whenAllInfosAreFilled() {
        when(personRepository.getListPerson()).thenReturn(Collections.singletonList(person1));

        List<Person> testResult = service.findPersonsWithMissingInfos();

        assertEquals(0, testResult.size());
        assertThat(testResult).doesNotContain(person1);
    }
}