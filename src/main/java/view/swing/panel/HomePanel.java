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

        // TODO: implement JTable
        panel.add(scrollPane);
        frame.setContentPane(panel);
    }
}
