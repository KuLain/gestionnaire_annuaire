package view.swing;

import javax.swing.*;

public class ManagerFrame extends JFrame {

    public ManagerFrame() {
        setTitle("Gestionnaire d'annuaire");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setJMenuBar(buildMenu());
        setLocationRelativeTo(null);
    }

    private JMenuBar buildMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("Fichier");
        JMenuItem changeFile = new JMenuItem("Changer fichier");
        // TODO: add function to change file
        JMenuItem quit = new JMenuItem("Quitter");
        quit.addActionListener(e -> System.exit(0));

        JMenu sortMenu = new JMenu("Trier");
        JMenuItem sortByName = new JMenuItem("Par nom");
        // TODO: add action listener to sort by name
        JMenuItem sortByFirstName = new JMenuItem("Par prénom");
        // TODO: add action listener to sort by first name
        JMenuItem sortByEmail = new JMenuItem("Par email");
        // TODO: add action listener to sort by email
        JMenuItem sortByPhone = new JMenuItem("Par téléphone");
        // TODO: add action listener to sort by phone
        JMenuItem sortByCity = new JMenuItem("Par ville");
        // TODO: add action listener to sort by city
        JMenuItem sortByZipCode = new JMenuItem("Par code postal");
        // TODO: add action listener to sort by zip code
        JMenuItem sortByJob = new JMenuItem("Par poste");
        // TODO: add action listener to sort by job

        JMenu searchMenu = new JMenu("Rechercher");
        JMenuItem searchByEmail = new JMenuItem("Par email");
        // TODO: add action listener to search by email
        JMenuItem searchByPhone = new JMenuItem("Par téléphone");
        // TODO: add action listener to search by phone

        JMenu resetMenu = new JMenu("Réinitialiser");
        JMenuItem reset = new JMenuItem("Réinitialiser affichage");
        // TODO: add action listener to reset display

        fileMenu.add(changeFile);
        fileMenu.add(quit);

        for (JMenuItem item : new JMenuItem[] { sortByName, sortByFirstName, sortByEmail, sortByPhone, sortByCity, sortByZipCode, sortByJob }) {
            sortMenu.add(item);
        }

        for (JMenuItem item : new JMenuItem[] { searchByEmail, searchByPhone }) {
            searchMenu.add(item);
        }

        resetMenu.add(reset);

        menuBar.add(fileMenu);
        menuBar.add(sortMenu);
        menuBar.add(searchMenu);
        menuBar.add(resetMenu);
        return menuBar;
    }

}
