package infrastructure.loader;

import domain.application.PersonBuilder;
import domain.model.Location;
import domain.model.Person;
import infrastructure.exceptions.AlreadyExistInRepositoryException;
import infrastructure.exceptions.InvalidLineFormatException;
import infrastructure.repository.LocationRepository;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class CSVPersonLoader implements PersonLoader {

    private final String path;
    private final PersonRepository personRepository;
    private final LocationRepository locationRepository;

    @Inject
    public CSVPersonLoader(FilePath filePath, PersonRepository personRepository, LocationRepository locationRepository) {
        this.path = filePath.path;
        this.personRepository = personRepository;
        this.locationRepository = locationRepository;
    }

    private void loadPersons() {
        try {
            InputStream inputStream = new FileInputStream(path);
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8);

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] infos = line.split(",");

                if (infos.length < 7) {
                    if (infos.length == 6) {
                        infos = new String[7];
                        String[] tmp = line.split(",");
                        System.arraycopy(tmp, 0, infos, 0, tmp.length);
                        infos[6] = "";
                    } else {
                        throw new InvalidLineFormatException(line);
                    }
                }

                Person currentPerson = PersonBuilder.generatePerson()
                        .withIdentity(infos[0], infos[1])
                        .withLocation(locationRepository.searchWithName(infos[2]))
                        .withContact(infos[4], infos[5])
                        .withJob(infos[6])
                        .build();

                try {
                    personRepository.add(currentPerson);
                } catch (AlreadyExistInRepositoryException e) {
                    System.err.println(currentPerson.getIdentity() + " has duplicate");
                }
            }

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private void loadLocations() {
        try {
            InputStream inputStream = new FileInputStream(path);
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8);

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] infos = line.split(",");

                if (infos.length < 7) {
                    if (infos.length == 6) {
                        infos = new String[7];
                        String[] tmp = line.split(",");
                        System.arraycopy(tmp, 0, infos, 0, tmp.length);
                        infos[6] = "";
                    } else {
                        throw new InvalidLineFormatException(line);
                    }
                }

                Location location = locationRepository.searchWithName(infos[2]);

                if (location == null
                        || location.getCity().equals("") && !infos[2].equals("")
                        || location.getPostalCode().equals("") && !infos[3].equals("")) {
                    locationRepository.add(new Location(infos[2], infos[3]));
                }

            }

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void load() {
        loadLocations();
        loadPersons();
    }
}
