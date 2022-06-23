package view.swing;

import javax.inject.Inject;
import javax.swing.*;

public class ManagerFrame extends JFrame {


    @Inject
    public ManagerFrame() {
        setTitle("Gestionnaire d'annuaire");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setLocationRelativeTo(null);
    }
}
