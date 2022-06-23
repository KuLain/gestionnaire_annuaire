package ui.swing.events;

import domain.application.options.sort.Order;
import domain.application.options.sort.SortingCriteria;
import ui.SortUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SortCallEvent implements ActionListener {

    private final SortingCriteria sortingCriteria;
    private final Order order;
    private final SortUI sortUI;

    public SortCallEvent(SortUI sortUI, SortingCriteria sortingCriteria, Order order) {
        this.sortUI = sortUI;
        this.order = order;
        this.sortingCriteria = sortingCriteria;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        sortUI.interact(sortingCriteria, order);
    }
}
