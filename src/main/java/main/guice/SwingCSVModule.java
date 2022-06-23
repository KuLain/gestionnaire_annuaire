package main.guice;

import com.google.inject.AbstractModule;
import com.google.inject.Singleton;
import infrastructure.loader.*;
import infrastructure.repository.*;
import ui.*;
import ui.swing.*;
import view.HomeView;
import view.SearchView;
import view.swing.*;
import view.swing.panel.*;

import javax.swing.*;

public class SwingCSVModule extends AbstractModule {

    private final FilePath path;
    public SwingCSVModule(String path) {
        this.path = new FilePath(path);
    }


    @Override
    protected void configure() {
        bind(FilePath.class).toInstance(path);
        bind(JFrame.class).to(ManagerFrame.class).in(Singleton.class);

        bind(PersonRepository.class).to(ListPersonRepository.class).in(Singleton.class);
        bind(LocationRepository.class).to(DefaultLocationRepository.class).in(Singleton.class);

        bind(PersonLoader.class).to(CSVPersonLoader.class);

        bind(HomeUI.class).to(SwingHomeUI.class);
        bind(SortUI.class).to(SwingSortUI.class);
        bind(SearchUI.class).to(SwingSearchUI.class);
        bind(PathUI.class).to(SwingPathUI.class);

        bind(HomeView.class).to(HomePanel.class);
        bind(SearchView.class).to(SwingSearchView.class);

    }

}
