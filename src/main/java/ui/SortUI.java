package ui;

import domain.application.options.sort.Order;
import domain.application.options.sort.SortingCriteria;


public interface SortUI {

    void interact(SortingCriteria criteria, Order order);

}
