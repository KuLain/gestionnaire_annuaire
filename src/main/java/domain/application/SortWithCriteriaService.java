package domain.application;

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
        switch (criteria) {
            case CITY -> {
                return sortByCity(order);
            }
            case POSTAL_CODE -> {
                return sortByPostalCode(order);
            }
            case PHONE_NUMBER -> {
                return sortByPhoneNumber(order);
            }
            case EMAIL -> {
                return sortByEmail(order);
            }
            case JOB -> {
                return sortByJob(order);
            }
        }
        return null;
    }

    private List<Person> sortByCity(Order order) {
        if (order == Order.ASC) {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> p.getLocation().getCity()))
                    .collect(Collectors.toList());
        } else {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> ((Person) p).getLocation().getCity()).reversed())
                    .collect(Collectors.toList());
        }
    }

    private List<Person> sortByPostalCode(Order order) {
        if (order == Order.ASC) {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> p.getLocation().getPostalCode()))
                    .collect(Collectors.toList());
        } else {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> ((Person) p).getLocation().getPostalCode()).reversed())
                    .sorted(Comparator.reverseOrder())
                    .collect(Collectors.toList());
        }
    }

    private List<Person> sortByPhoneNumber(Order order) {
        if (order == Order.ASC) {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> p.getContact().getPhone()))
                    .collect(Collectors.toList());
        } else {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> ((Person) p).getContact().getPhone()).reversed())
                    .sorted(Comparator.reverseOrder())
                    .collect(Collectors.toList());
        }
    }

    private List<Person> sortByEmail(Order order) {
        if (order == Order.ASC) {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> p.getContact().getEmailAdress()))
                    .collect(Collectors.toList());
        } else {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(p -> ((Person) p).getContact().getEmailAdress()).reversed())
                    .sorted(Comparator.reverseOrder())
                    .collect(Collectors.toList());
        }
    }

    private List<Person> sortByJob(Order order) {
        if (order == Order.ASC) {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(Person::getJob))
                    .collect(Collectors.toList());
        } else {
            return personRepository.getListPerson()
                    .stream()
                    .sorted(Comparator.comparing(Person::getJob))
                    .sorted(Comparator.reverseOrder())
                    .collect(Collectors.toList());
        }
    }
}
