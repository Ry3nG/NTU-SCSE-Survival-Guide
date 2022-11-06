package lab4;

public class SalePerson implements Comparable<SalePerson> {
	String firstName;
	String lastName;
	int totalSales;

	public SalePerson(String firstName, String LastName, int totalSales) {
		this.firstName = firstName;
		this.lastName = LastName;
		this.totalSales = totalSales;
	}

	public String toString() {
		return this.firstName + " " + this.lastName + ":" + this.totalSales;

	}

	public boolean equals(SalePerson person) {
		if (person.firstName.equals(person.lastName))
			return true;
		else {
			return false;
		}

	}

	public String getFirstName() {
		return firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public int getTotalSales() {
		return totalSales;
	}

	@Override
	public int compareTo(SalePerson p) {
		if (p.totalSales > this.totalSales)
			return -1;
		else if (p.totalSales < this.totalSales)
			return 1;
		else {
			if ((this.lastName).compareTo(p.lastName) < 0)
				return 1;
			else
				
				return -1;

		}
	}

}
