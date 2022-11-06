package lab3;
/**
 * a class Plane that comprises 12 seats.
*/
public class Plane {
    // Write a class Plane that comprises 12 seats. The class should create an array
    // of 12 objects from the class PlaneSeat.

    PlaneSeat[] seat = new PlaneSeat[12];
    int numEmptySeats = 12;

    public Plane() {
        for (int i = 0; i < 12; i++) {
            seat[i] = new PlaneSeat(i);
        }
    }

    /**
     * a method to sort the seats according to ascending order of customerID.
     * A copy of the original seat array is used for sorting instead of the original
     * 
     * @param customerId
     * @return the numEmptySeats
     */
    public PlaneSeat[] sortSeats() {
        PlaneSeat[] sortedSeats = new PlaneSeat[12];
        for (int i = 0; i < 12; i++) {
            sortedSeats[i] = seat[i];
        }
        // bubble sort
        for (int i = 0; i < 12; i++) {
            for (int j = i + 1; j < 12; j++) {
                if (sortedSeats[i].getCustomerId() > sortedSeats[j].getCustomerId()) {
                    PlaneSeat temp = sortedSeats[i];
                    sortedSeats[i] = sortedSeats[j];
                    sortedSeats[j] = temp;
                }
            }
        }
        return sortedSeats;
    }

    /**
     * a method to display the number of empty seats.
     */
    public void showNumEmptySeats() {
        System.out.println("There are " + numEmptySeats+" empty seats.");
    }

    /**
     * a method to display the list of empty seats.
     */
    public void showEmptySeats() {
        System.out.println("The following seats are empty:");
        for (int i = 0; i < 12; i++) {
            if (!seat[i].isOccupied()) {
                System.out.println("SeatId "+seat[i].getSeatId());
            }
        }
        System.out.println();
    }

    /**
     * a method to display the assigned seats with seat ID and customer ID.
     * If bySeatId is true, the order will be by seatID, else order is by
     * customerID.
     * 
     * @param bySeatId
     */
    public void showAssignedSeats(boolean bySeatId) {
        if (bySeatId) {
            System.out.println("The seat assignments are as follows:");
            for (int i = 0; i < 12; i++) {
                if (seat[i].isOccupied()) {
                    System.out.println("Seat ID: " + seat[i].getSeatId() + " assigned to Customer ID: " + seat[i].getCustomerId());
                }
            }
        } else {
            System.out.println("The seat assignments are as follows:");
            PlaneSeat[] sortedSeats = sortSeats();
            for (int i = 0; i < 12; i++) {
                if (sortedSeats[i].isOccupied()) {
                    System.out.println("Seat ID: " + sortedSeats[i].getSeatId() + " assigned to Customer ID: "
                            + sortedSeats[i].getCustomerId());
                }
            }
        }
    }

    /**
     * a method that assigns a customer ID to an empty seat .
     */
    void assignSeat(int seatId, int customerID) {
        if (seat[seatId-1].isOccupied()) {
            System.out.println("Seat already assigned to a customer.");
        } else {
            seat[seatId-1].assign(customerID);
            numEmptySeats--;
            System.out.println("Seat " + seatId + " is assigned to customer " + customerID);
        }
    }

    /**
     * a method that unassigns a seat.
     */
    void unassignSeat(int seatId) {
        if (seat[seatId-1].isOccupied()) {
            seat[seatId-1].unassign();
            numEmptySeats++;
            System.out.println("Seat " + seatId + " is unassigned.");
        } else {
            System.out.println("Seat " + seatId + " is not occupied.");
        }
    }
}
