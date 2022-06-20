package domain.application.options.sort;

import domain.model.Person;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class SortWithCriteriaService {

    private final PersonRepository personRepository;

    @Inject
    public SortWithCriteriaService(PersonRepository personRepository) {
        this.personRepository = personRepository;
    }

    public List<Person> sortWithCriteria(SortingCriteria criteria, Order order) {
        List<Person> personList = null;

        switch (criteria) {
            case CITY -> {
                personList = sortByCity();
            }
            case POSTAL_CODE -> {
                personList = sortByPostalCode();
            }
            case PHONE_NUMBER -> {
                personList = sortByPhoneNumber();
            }
            case EMAIL -> {
                personList = sortByEmail();
            }
            case JOB -> {
                personList = sortByJob();
            }
        }
        if (personList != null && order == Order.DESC) {
            reverseList(personList);
        }

        return personList;
    }

    private List<Person> sortByCity() {
        return personRepository.getListPerson()
                .stream()
                .sorted(Comparator.comparing(p -> p.getLocation().getCity()))
                .collect(Collectors.toList());
    }

    private List<Person> sortByPostalCode() {
        return personRepository.getListPerson()
                .stream()
                .sorted(Comparator.comparing(p -> p.getLocation().getPostalCode()))
                .collect(Collectors.toList());
    }

    private List<Person> sortByPhoneNumber() {
        return personRepository.getListPerson()
                .stream()
                .sorted(Comparator.comparing(p -> p.getContact().getPhone()))
                .collect(Collectors.toList());
    }

    private List<Person> sortByEmail() {
        return personRepository.getListPerson()
                .stream()
                .sorted(Comparator.comparing(p -> p.getContact().getEmailAdress()))
                .collect(Collectors.toList());
    }

    private List<Person> sortByJob() {
        return personRepository.getListPerson()
                .stream()
                .sorted(Comparator.comparing(Person::getJob))
                .collect(Collectors.toList());
    }

    private void reverseList(List<Person> listToReverse) {
        for (int i = 0; i < listToReverse.size()/2; i++) {
            int endIndex = listToReverse.size()-1-i;
            Person tmp = listToReverse.get(endIndex);
            listToReverse.set(endIndex, listToReverse.get(i));
            listToReverse.set(i, tmp);
        }
    }
}
