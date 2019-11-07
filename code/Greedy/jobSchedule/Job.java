package src.dp;

public class Job implements Comparable<Object> {
	int jobNbr;		// Package access
	int deadline;	// Package access
	int profit;		// Package access
	int time;		// Package access
	
	public Job(int j, int d, int p, int t) {
		jobNbr= j;
		deadline= d;
		profit= p;
		time= t;
	}
    public int compareTo(Object other) {
    	Job o= (Job) other;
        if (deadline < o.deadline)
            return -1;
        else if (deadline > o.deadline)
            return 1;
        else
            return 0;
    }
        public String toString() {
    	return ("Job: "+ jobNbr+" Deadline: "+deadline+" Profit: "+profit+" Time: "+time);
    }
}