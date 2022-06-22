package view.swing.panel;

import domain.model.Person;
import infrastructure.repository.PersonRepository;
import view.HomeView;

import javax.inject.Inject;
import javax.swing.*;
import java.util.List;

public class HomePanel extends PanelView implements HomeView {

    @Inject
    public HomePanel(JFrame frame) {
        super(frame);
    }

    @Override
    public void display(List<Person> personList) {
        JPanel panel = new JPanel();

        // TODO: implement JTable

        frame.setContentPane(panel);
    }
}
