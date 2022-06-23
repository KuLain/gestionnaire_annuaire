package view.swing;

import domain.model.Person;
import view.HomeView;
import view.SearchView;

import javax.inject.Inject;
import javax.swing.*;
import java.util.List;

public class SwingSearchView implements SearchView {
    private final JFrame frame;
    private final HomeView homeView;

    @Inject
    public SwingSearchView(JFrame frame, HomeView homeView) {
        this.frame = frame;
        this.homeView = homeView;
    }

    @Override
    public void display(Person person) {
        if (person == null) {
            JOptionPane.showMessageDialog(frame,
                    "Cette personne n'existe pas",
                    "Personne introuvable",
                    JOptionPane.ERROR_MESSAGE);
        } else {
            homeView.display(List.of(person));
        }
    }
}
