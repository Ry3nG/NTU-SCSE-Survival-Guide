package lab3;

public class PlaneSeat {
    int seatId;
    boolean assigned;
    int customerId;

    public PlaneSeat(int seatId) {
        this.seatId = seatId;
        this.assigned = false;
        this.customerId = -1;
    }

    public int getSeatId() {
        return seatId+1;
    }

    public int getCustomerId() {
        return customerId;
    }

    public boolean isOccupied() {
        return assigned;
    }

    public void assign(int customerId){
        this.customerId = customerId;
        this.assigned = true;
    }

    public void unassign(){
        this.customerId = -1;
        this.assigned = false;
    }
}
