package view.swing.panel;

import domain.model.Person;
import ui.HomeUI;
import ui.PathUI;
import ui.SearchUI;
import ui.SortUI;
import view.HomeView;

import javax.inject.Inject;
import javax.swing.*;
import java.awt.*;
import java.util.List;

public class HomePanel extends PanelView implements HomeView {

    private final PathUI pathUI;
    private final SortUI sortUI;
    private final SearchUI searchUI;
    private final HomeUI homeUI;

    @Inject
    public HomePanel(JFrame frame, PathUI pathUI, SortUI sortUI, SearchUI searchUI, HomeUI homeUI) {
        super(frame);
        this.pathUI = pathUI;
        this.sortUI = sortUI;
        this.searchUI = searchUI;
        this.homeUI = homeUI;
    }

    @Override
    public void display(List<Person> personList) {
        JPanel panel = new JPanel(new BorderLayout());
        String[] columnNames = {"Prénom", "Nom", "Ville", "Code postal", "Téléphone", "Email", "Profession"};
        String[][] data = new String[personList.size()][columnNames.length];
        int i = 0;

        for (Person person : personList) {
            data[i][0] = person.getIdentity().getFirstName();
            data[i][1] = person.getIdentity().getLastName();
            data[i][2] = person.getLocation().getCity();
            data[i][3] = person.getLocation().getPostalCode();
            data[i][4] = person.getContact().getPhone();
            data[i][5] = person.getContact().getEmailAdress();
            data[i][6] = person.getJob();
            i++;
        }

        JTable table = new JTable(data, columnNames);
        JScrollPane scrollPane = new JScrollPane(table);

        panel.add(scrollPane);

        if (frame.getJMenuBar() == null) {
            frame.setJMenuBar(new OptionMenuBar(pathUI, sortUI, searchUI, homeUI));
        }

        frame.setContentPane(panel);
        panel.updateUI();
    }
}
