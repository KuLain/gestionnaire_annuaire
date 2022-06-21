package view.swing.panel;

import ui.HomeView;

import javax.inject.Inject;
import javax.swing.*;

public class HomePanel implements HomeView {

    private final JFrame frame;

    @Inject
    public HomePanel(JFrame frame) {
        this.frame = frame;
    }

    @Override
    public void display() {
        JPanel panel = new JPanel();

        JButton button = new JButton("Click me");

        panel.add(button);

        frame.setContentPane(panel);
    }
}
