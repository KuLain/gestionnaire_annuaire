package view.swing.panel;

import infrastructure.repository.PersonRepository;
import view.HomeView;

import javax.inject.Inject;
import javax.swing.*;

public class HomePanel extends PanelView implements HomeView {

    private final PersonRepository personRepository;

    @Inject
    public HomePanel(JFrame frame, PersonRepository personRepository) {
        super(frame);
        this.personRepository = personRepository;
    }

    @Override
    public void display() {
        JPanel panel = new JPanel();

        // TODO: implement JTable

        frame.setContentPane(panel);
    }
}
