package ui.swing;

import domain.application.options.sort.Order;
import domain.application.options.sort.SortWithCriteriaService;
import domain.application.options.sort.SortingCriteria;
import domain.model.Person;
import infrastructure.repository.PersonRepository;
import ui.SortUI;
import view.HomeView;

import javax.inject.Inject;
import java.util.List;

public class SwingSortUI implements SortUI {

    private final HomeView homeView;
    private final SortWithCriteriaService service;
    @Inject
    public SwingSortUI(HomeView homeView, PersonRepository personRepository) {
        this.homeView = homeView;
        service = new SortWithCriteriaService(personRepository);
    }


    @Override
    public void interact(SortingCriteria criteria, Order order) {
        List<Person> sortedList = service.sortWithCriteria(criteria, order);
        homeView.display(sortedList);
    }
}
