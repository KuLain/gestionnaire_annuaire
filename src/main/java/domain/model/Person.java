package domain.model;

import java.util.Objects;

public class Person implements Comparable<Person>{

    private Identity identity = null;
    private Location location = null;
    private Contact contact = null;
    private String job = null;

    public void setIdentity(Identity identity) {
        this.identity = identity;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public void setContact(Contact contact) {
        this.contact = contact;
    }

    public void setJob(String job) {
        this.job = job;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(identity).append("\n");
        for (Object object : new Object[]{location, contact, job}) {
            if (object != null) {
                sb.append("\t").append(object).append("\n");
            }
        }
        sb.setLength(sb.length()-1);
        return sb.toString();
    }

    @Override
    public int compareTo(Person o) {
        if (o.identity.getLastName().equals(identity.getLastName())) {
            return identity.getFirstName().compareTo(o.identity.getFirstName());
        } else {
            return identity.getLastName().compareTo(o.identity.getLastName());
        }
    }


    public Identity getIdentity() {
        return identity;
    }

    public Location getLocation() {
        return location;
    }

    public Contact getContact() {
        return contact;
    }

    public String getJob() {
        return job;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return Objects.equals(identity, person.identity) && Objects.equals(location, person.location) && Objects.equals(contact, person.contact) && Objects.equals(job, person.job);
    }

    @Override
    public int hashCode() {
        return Objects.hash(identity, location, contact, job);
    }
}
