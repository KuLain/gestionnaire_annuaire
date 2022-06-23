package infrastructure.writer;

import domain.model.Person;
import infrastructure.loader.FilePath;
import infrastructure.repository.PersonRepository;

import javax.inject.Inject;
import java.io.FileWriter;
import java.io.IOException;

public class CSVPersonWriter implements PersonWriter {

    private final PersonRepository personRepository;
    private final FilePath filePath;

    @Inject
    public CSVPersonWriter(PersonRepository personRepository, FilePath filePath) {
        this.personRepository = personRepository;
        this.filePath = filePath;
    }

    @Override
    public void write() {
        try {
            FileWriter fileWriter = new FileWriter(filePath.path);
            for (Person person : personRepository.getListPerson()) {
                fileWriter.write(formatLine(person));
            }
            fileWriter.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private String formatLine(Person person) {
        return person.getIdentity().getFirstName() + "," +
                person.getIdentity().getLastName() + "," +
                person.getLocation().getCity() + "," +
                person.getLocation().getPostalCode() + "," +
                person.getContact().getPhone() + "," +
                person.getContact().getEmailAdress() + "," +
                person.getJob() + "\n";
    }
}
