package ui.swing;

import domain.application.options.filter.FilterService;
import domain.application.options.sort.SortingCriteria;
import infrastructure.repository.PersonRepository;
import ui.FilterUI;
import view.HomeView;

import javax.inject.Inject;

public class SwingFilterUI implements FilterUI {

    private final HomeView homeView;
    private final FilterService service;

    @Inject
    public SwingFilterUI(HomeView homeView, PersonRepository personRepository) {
        this.homeView = homeView;
        service = new FilterService(personRepository);
    }

    @Override
    public void interact(String pattern, SortingCriteria sortingCriteria) {
        homeView.display(service.filter(pattern, sortingCriteria));
    }
}
