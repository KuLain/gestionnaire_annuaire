package view.swing.panel;

import javax.inject.Inject;
import javax.swing.*;

public abstract class PanelView {

    protected final JFrame frame;

    @Inject
    public PanelView(JFrame frame) {
        this.frame = frame;
    }
}
