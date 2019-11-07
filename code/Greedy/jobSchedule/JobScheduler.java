package src.dp;
import java.util.*;

public class JobScheduler {
		private Job[] jobs;			// Input set of jobs to schedule
		private int nbrJobs;		// Number of input jobs
		private int endTime;		// Latest end time of job (=maximum resource)
		private int[] path;			// List of nodes that are the optimal solution
		private int jobsDone;		// Output: total number of jobs
		private int totalProfit;	// Output  (can also compute total time used)
		
		private int nodes;			// Nodes generated in DP graph
		private int[] nodeProfit;	// Profit of jobs prior to this node at this stage
		private int[] nodeTime;		// Time spent on jobs prior to this node at this stage
		private int[] pred;			// Predecessor node with best profit from this node
		private int stageNodes;		// Difference in node numbers from one stage to next
		
		public JobScheduler(Job[] j, int e) {
			jobs = j;
			endTime = e;
			nbrJobs= jobs.length;
			path= new int[nbrJobs+1];
			nodes= (nbrJobs-1)*(endTime+1)+2;	// Stages*states + source, sink
			nodeProfit= new int[nodes];
			nodeTime= new int[nodes];
			pred= new int[nodes];
			for (int i= 0; i < nodes; i++)
				pred[i]= -1;
			stageNodes= endTime+1;
		}

		public void jsd() {
			buildSource();
			buildCenter();
			buildSink();
			backPath();
		}
		
		private void buildSource() {
			// Source node ('=0' statements included for clarity)
			nodeProfit[0]= 0;
			nodeTime[0]= 0;
			
			// Treat stage 0 as special case because it has only 1 node
			// Generate 1 or 2 virtual arcs, depending on whether job feasible or not
			// If job not in solution set (0 time and profit). This option always feasible
			nodeProfit[1]= 0;
			nodeTime[1]= 0;
			pred[1]= 0;

			// If job feasible
			if (jobs[0].time <= jobs[0].deadline) {
				int toNode= 1+ jobs[0].time;
				nodeProfit[toNode]= jobs[0].profit;
				nodeTime[toNode]= jobs[0].time;
				pred[toNode]= 0;
			}
		}
		
		private void buildCenter() {
			for (int stage= 1; stage < nbrJobs-1; stage++) {
				// Generate virtual arcs
				for (int node= (stage-1)*stageNodes+1; 
						node <= stage*stageNodes; node++) 
					if (pred[node] >= 0) {
						// Generate 1 or 2 virtual arcs from previous node
						// If job not in solution set build arc, if it is on optimal sequence
						if (nodeProfit[node] >= nodeProfit[node+stageNodes]) {
							nodeProfit[node+stageNodes]= nodeProfit[node];
							nodeTime[node+stageNodes]= nodeTime[node];
							pred[node+stageNodes]= node;
						}
						// If job feasible build virtual arc (Stage = job) if it is on optimal sequence
						if (nodeTime[node]+jobs[stage].time <= jobs[stage].deadline) {
							int nextNode= node + stageNodes + jobs[stage].time;
							if (nodeProfit[node] + jobs[stage].profit >= nodeProfit[nextNode]) {
								nodeProfit[nextNode]= nodeProfit[node]+ jobs[stage].profit;
								nodeTime[nextNode]= nodeTime[node]+ jobs[stage].time;
								pred[nextNode]= node;
						}
					}
				}
			}
		}
		
		private void buildSink() {
			int stage= nbrJobs - 1;
			int sinkNode= (nbrJobs-1)*stageNodes + 1;
			for (int node= (stage-1)*stageNodes+1; node <= stage*stageNodes; node++)
				if (pred[node] >= 0) {
					// Generate only single best virtual arc from previous node
					// Job feasible
					if (nodeTime[node] + jobs[stage].time <= jobs[stage].deadline) {
						// Job in solution
						if (nodeProfit[node]+ jobs[stage].profit >= nodeProfit[sinkNode]) {
							nodeProfit[sinkNode]= nodeProfit[node]+ jobs[stage].profit;
							nodeTime[sinkNode]= nodeTime[node]+ jobs[stage].time;
							pred[sinkNode]= node;
						}
					}
						// Job not in solution
					if (nodeProfit[node] >= nodeProfit[sinkNode]) {
						nodeProfit[sinkNode]= nodeProfit[node];
						nodeTime[sinkNode]= nodeTime[node];
						pred[sinkNode]= node;
					}
				}
		}
		
		private void backPath() {
			// Trace back predecessor nodes from sink to source
			path[nbrJobs]= (nbrJobs-1)*stageNodes + 1;	// Sink node
			for (int stage= nbrJobs-1; stage >= 1; stage--)
				path[stage]= pred[path[stage+1]];
		}
		
		public void outputJobs() {
			System.out.println("Jobs to be scheduled");
			for (Job j: jobs)
				System.out.println(j);
			System.out.println();
			
			System.out.println("Jobs done:");
			for (int stage= 0; stage < nbrJobs; stage++) {
				if (nodeProfit[path[stage]] != nodeProfit[path[stage+1]]) {	// Job in solution
					System.out.println(jobs[stage]);
					jobsDone++;
					totalProfit += jobs[stage].profit;
				}
			}
			System.out.println("\nJobs done: " + jobsDone + " total profit: "+ totalProfit);
		}

		public static void main(String[] args) {
			Job[] jobs= new Job[7];
			jobs[0]= new Job(0, 1, 39, 1);	
			jobs[1]= new Job(1, 2, 90, 1);
			jobs[2]= new Job(2, 2, 88, 2);
			jobs[3]= new Job(3, 2, 20, 1);
			jobs[4]= new Job(4, 3, 37, 3);
			jobs[5]= new Job(5, 3, 25, 2);
			jobs[6]= new Job(6, 4, 70, 1);
			int endTime= 4;
			Arrays.sort(jobs);
			JobScheduler j= new JobScheduler(jobs, endTime);
			j.jsd();
			j.outputJobs();
		}	
	}
