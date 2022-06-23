package view.swing.panel;

import domain.application.PersonBuilder;
import domain.application.options.sort.Order;
import domain.application.options.sort.SortingCriteria;
import domain.model.Person;
import infrastructure.exceptions.PersonNotInBaseException;
import ui.*;
import ui.swing.components.SearchType;

import javax.swing.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class OptionMenuBar extends JMenuBar {

    private final JFrame frame;
    private final PathUI pathUI;
    private final SortUI sortUI;
    private final SearchUI searchUI;
    private final HomeUI homeUI;
    private final ModifyUI modifyUI;

    public OptionMenuBar(JFrame frame, PathUI pathUI, SortUI sortUI, SearchUI searchUI, HomeUI homeUI, ModifyUI modifyUI) {
        this.frame = frame;
        this.pathUI = pathUI;
        this.sortUI = sortUI;
        this.searchUI = searchUI;
        this.homeUI = homeUI;
        this.modifyUI = modifyUI;

        buildMenuBar();
    }

    private void buildMenuBar() {
        add(buildFileMenu());
        add(buildSortMenu());
        add(buildSearchMenu());
        add(buildModifyMenu());
        add(buildResetMenu());
    }

    private JMenu buildFileMenu() {
        JMenu fileMenu = new JMenu("Fichier");
        JMenuItem changeFile = new JMenuItem("Changer fichier");
        JMenuItem quitAndSave = new JMenuItem("Quitter et sauvegarder");
        // TODO: add function to quit and save
        JMenuItem quit = new JMenuItem("Quitter sans sauvegarder");

        fileMenu.add(changeFile);
        changeFile.addActionListener(e -> {
            String newPath = inputNewFilePath();
            pathUI.changePath(newPath);
        });
        fileMenu.add(quitAndSave);
        fileMenu.add(quit);
        quit.addActionListener(e -> System.exit(0));

        return fileMenu;
    }

    private JMenu buildSortMenu() {
        JMenu sortMenu = new JMenu("Trier");
        JCheckBoxMenuItem reverseCheckbox = new JCheckBoxMenuItem("Ordre décroissant");
        JMenuItem sortByFirstName = new JMenuItem("Par prénom");
        JMenuItem sortByName = new JMenuItem("Par nom");
        JMenuItem sortByCity = new JMenuItem("Par ville");
        JMenuItem sortByZipCode = new JMenuItem("Par code postal");
        JMenuItem sortByPhone = new JMenuItem("Par téléphone");
        JMenuItem sortByEmail = new JMenuItem("Par email");
        JMenuItem sortByJob = new JMenuItem("Par poste");

        int i = 0;

        SortingCriteria[] sortingCriteria = SortingCriteria.values();

        sortMenu.add(reverseCheckbox);
        sortMenu.add(new JSeparator());
        for (JMenuItem item : new JMenuItem[]{sortByFirstName, sortByName, sortByCity,
                sortByZipCode, sortByPhone, sortByEmail, sortByJob}) {
            sortMenu.add(item);
            addEventToSortMenu(item, reverseCheckbox, sortingCriteria[i++]);
        }

        return sortMenu;
    }

    private void addEventToSortMenu(JMenuItem item, JCheckBoxMenuItem checkBox, SortingCriteria criteria) {
        item.addActionListener(e -> {
            if (checkBox.getState()) {
                sortUI.interact(criteria, Order.DESC);
            } else {
                sortUI.interact(criteria, Order.ASC);
            }
        });
    }

    private JMenu buildSearchMenu() {
        JMenu searchMenu = new JMenu("Rechercher");
        JMenuItem searchByEmail = new JMenuItem("Par email");
        JMenuItem searchByPhone = new JMenuItem("Par téléphone");

        searchMenu.add(searchByEmail);
        searchByEmail.addActionListener(e -> {
            String[] inputs = callFieldsInput(SortingCriteria.FIRST_NAME, SortingCriteria.LAST_NAME,
                    SortingCriteria.EMAIL);
            searchUI.interact(inputs[0], inputs[1], inputs[2], SearchType.EMAIL);
        });
        searchMenu.add(searchByPhone);
        searchByPhone.addActionListener(e -> {
            String[] inputs = callFieldsInput(SortingCriteria.FIRST_NAME, SortingCriteria.LAST_NAME,
                    SortingCriteria.PHONE_NUMBER);
            searchUI.interact(inputs[0], inputs[1], inputs[2], SearchType.PHONE);
        });

        return searchMenu;
    }

    private JMenu buildModifyMenu() {
        JMenu modifyMenu = new JMenu("Modifier");
        JMenuItem add = new JMenuItem("Ajouter une personne");
        JMenuItem suppress = new JMenuItem("Supprimer par email");
        JMenuItem suppressByPhone = new JMenuItem("Supprimer par téléphone");

        modifyMenu.add(add);
        modifyMenu.add(new JSeparator());
        modifyMenu.add(suppress);
        modifyMenu.add(suppressByPhone);

        add.addActionListener(e -> {
            String[] inputs = callFieldsInput(SortingCriteria.FIRST_NAME, SortingCriteria.LAST_NAME, SortingCriteria.CITY,
                    SortingCriteria.POSTAL_CODE, SortingCriteria.PHONE_NUMBER, SortingCriteria.EMAIL, SortingCriteria.JOB);
            Person person = PersonBuilder.generatePerson()
                    .withIdentity(inputs[0], inputs[1])
                    .withLocation(inputs[2], inputs[3])
                    .withContact(inputs[4], inputs[5])
                    .withJob(inputs[6])
                    .build();

            modifyUI.interact(inputs, null);
        });

        suppress.addActionListener(e -> {
            String[] inputs = callFieldsInput(SortingCriteria.FIRST_NAME, SortingCriteria.LAST_NAME, SortingCriteria.EMAIL);
            try {
                modifyUI.interact(inputs, SearchType.EMAIL);
            } catch (PersonNotInBaseException exception) {
                JOptionPane.showMessageDialog(frame, "Cette personne n'existe pas dans la base",
                        "Personne introuvable",
                        JOptionPane.ERROR_MESSAGE);
            }
        });

        suppressByPhone.addActionListener(e -> {
            String[] inputs = callFieldsInput(SortingCriteria.FIRST_NAME, SortingCriteria.LAST_NAME, SortingCriteria.PHONE_NUMBER);
            try {
                modifyUI.interact(inputs, SearchType.PHONE);
            } catch (PersonNotInBaseException exception) {
                JOptionPane.showMessageDialog(frame, "Cette personne n'existe pas dans la base",
                        "Personne introuvable",
                        JOptionPane.ERROR_MESSAGE);
            }
        });

        return modifyMenu;
    }

    private JMenu buildResetMenu() {
        JMenu resetMenu = new JMenu("Réinitialiser");
        JMenuItem reset = new JMenuItem("Réinitialiser affichage");

        resetMenu.add(reset);
        reset.addActionListener(e -> homeUI.interact());

        return resetMenu;
    }

    private String inputNewFilePath() {
        JFileChooser fileChooser = new JFileChooser("src/main/resources");

        int result = fileChooser.showOpenDialog(this);

        if (result == JFileChooser.APPROVE_OPTION) {
            return fileChooser.getSelectedFile().getAbsolutePath();
        } else {
            return null;
        }
    }

    private String[] callFieldsInput(SortingCriteria... criterias) {
        List<String> inputFields = new ArrayList<>();
        Map<SortingCriteria, String> dictionnaire = new HashMap<>();
        dictionnaire.put(SortingCriteria.FIRST_NAME, "prénom");
        dictionnaire.put(SortingCriteria.LAST_NAME, "nom");
        dictionnaire.put(SortingCriteria.CITY, "ville");
        dictionnaire.put(SortingCriteria.POSTAL_CODE, "code postal");
        dictionnaire.put(SortingCriteria.PHONE_NUMBER, "numéro de téléphone");
        dictionnaire.put(SortingCriteria.EMAIL, "adresse email");
        dictionnaire.put(SortingCriteria.JOB, "profession");

        for (SortingCriteria criteria : criterias) {
            String currentInput = JOptionPane.showInputDialog(this,
                    "Entrez l'information suivante : " + dictionnaire.get(criteria),
                    "Entrez une informations",
                    JOptionPane.QUESTION_MESSAGE);
            inputFields.add(currentInput);
        }

        return inputFields.toArray(new String[0]);
    }

}
