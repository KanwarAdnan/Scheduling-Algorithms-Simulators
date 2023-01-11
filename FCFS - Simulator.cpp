/**

    # Code By Kanwar Adnan

*/

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;
#include <algorithm>

/*

    The Process class represents a single process that can be scheduled using a scheduling algorithm.

    It has the following member variables:

      name (int) : an identifier for the process
      arrival_time (int): the time at which the process arrives
      burst_time (int): the amount of time required for the process to execute
      response_time (int): the time taken from arrival time to first response of process
      finish_time (int): the time at which the process finishes executing
      turn_around_time (int): the time taken for the process to complete execution
      waiting_time (int): the time process spent waiting in the ready queue
      burst_time_mask (int) and cache (int) are not used in the class.

    The class has the following member functions:

      Process(name: int, arrival_time: int, burst_time: int) : constructor which initializes the member variables with the provided values.
      operator<<(ostream&, const Process&) : overload operator '<<' to output process object in the required format.
get_report() : returns a map containing the process details, with keys as variable name and value as the variable's value
      Getter and setter functions for all the private variables.

*/

class Process {
    private:
        int name;
        int arrival_time;
        int burst_time;
        int response_time;
        int finish_time;
        int turn_around_time;
        int waiting_time;
        int burst_time_mask;
        int cache;

    public:
        /**
         * Constructor for the Process class.
         * @param name The name of the process.
         * @param arrival_time The arrival time of the process.
         * @param burst_time The burst time of the process.
         */
        Process(int name, int arrival_time, int burst_time) : name(name), arrival_time(arrival_time), burst_time(burst_time)         {
            response_time = -1;
            finish_time = -1;
            turn_around_time = -1;
            waiting_time = -1;
            burst_time_mask = -1;
            cache = -1;
        }

        /**
         * Overloading operator to make it easy to print the process details.
         */
        friend ostream& operator<< (ostream &out, const Process &process) {
            out << process.name << "\t" << process.arrival_time << "\t" << process.burst_time << "\t" << process.response_time << "\t"
            << process.finish_time << "\t" << process.turn_around_time << "\t" << process.waiting_time;
            return out;
        }

        /**
         * Get report of the process with the name of the process, arrival time, burst time, response time, 
         * finish time, turn around time, waiting time
         * @return A map containing the report of the process.
         */
        map<string, int> get_report() {
            map<string, int> report = {
                {"Process", name},
                {"A.T", arrival_time},
                {"B.T", burst_time},
                {"R.T", response_time},
                {"F.T", finish_time},
                {"T.A.T", turn_around_time},
                {"W.T", waiting_time}
            };
            return report;
        }

        //getters
        int get_name() { return name; }
        int get_arrival_time() { return arrival_time; }
        int get_burst_time() { return burst_time; }
        int get_response_time() { return response_time; }
        int get_finish_time() { return finish_time; }
        int get_turn_around_time() { return turn_around_time; }
        int get_waiting_time() { return waiting_time; }
        int get_burst_time_mask() { return burst_time_mask; }
        int get_cache() { return cache; }
        //setters
        void set_response_time(int value) { response_time = value; }
        void set_finish_time(int value) { finish_time = value; }
        void set_turn_around_time(int value) { turn_around_time = value; }
        void set_waiting_time(int value) { waiting_time = value; }
        void set_burst_time(int value) { burst_time = value; }
        void set_arrival_time(int value) { arrival_time = value; }
        void set_name(int value) { name = value; }
};

class FCFS {
    public:
        /**
         * execute_processes is a static method that takes a vector of Process objects as an input and returns a 
         * vector of maps that contains the report of each process.
         *
         * The method first sorts the processes based on their arrival time using the STL sort function.
         * It then initializes the current time to the arrival time of the first process.
         * Then, it iterates through the processes, setting the response time, finish time, turn around time, 
         * and waiting time of each process. It also updates the current time as the finish time of the current process.
         * Finally, it pushes the report of each process into the reports vector and returns it.
         *
         * @param processes  a vector of Process objects to be executed
         * @return           a vector of maps that contains the report of each process
         */

        static vector<map<string, int>> execute_processes(vector<Process> processes) {
            vector<map<string, int>> reports;
	    sort(processes.begin(), processes.end(), [](Process a, Process b) {
                return a.get_arrival_time() < b.get_arrival_time();
            });

            int current_time = processes[0].get_arrival_time();
            for (auto process : processes) {
                process.set_response_time(current_time);
                process.set_finish_time(current_time + process.get_burst_time());
                current_time = process.get_finish_time();
                process.set_turn_around_time(process.get_finish_time() - process.get_arrival_time());
                process.set_waiting_time(process.get_turn_around_time() - process.get_burst_time());
                reports.push_back(process.get_report());
            }
            return reports;
        }
};

void print_report(vector<map<string, int>> reports) {
    /**
    It takes in one argument: a vector of maps, where each map represents a process report with keys of string type and values of int type. The function first prints the headers of the report table, with the width of each column set to 10 characters using setw(). Then, for each process report in the input vector, it prints the values of each key in the corresponding column and goes to the next line.
    */

    cout << setw(10) << "Process" << setw(10) << "A.T" << setw(10) << "B.T"
    << setw(10) << "F.T" << setw(10) << "R.T" << setw(10) << "T.A.T"
    << setw(10) << "W.T" << endl;
    for (auto report : reports) {
        cout << setw(10) << report["Process"] << setw(10) << report["A.T"] << setw(10)
        << report["B.T"] << setw(10) << report["F.T"] << setw(10) << report["R.T"]
        << setw(10) << report["T.A.T"] << setw(10) << report["W.T"] << endl;
    }
}

vector<Process> q1 = {Process(1, 0, 9), Process(2, 1, 4), Process(3, 2, 9), Process(4, 4, 3)};
vector<Process> q2 = {Process(1, 0, 20), Process(2, 15, 25), Process(3, 30, 10), Process(4, 45, 15)};
vector<Process> q3 = {Process(1, 0, 8), Process(2, 1, 4), Process(3, 2, 9), Process(4, 3, 5)};
vector<vector<Process>> questions = {q1, q2, q3};

void execute_all_processes(vector<vector<Process>> processes) {
    for (auto process : processes){
        vector<map<string, int>> report = FCFS::execute_processes(process);
        print_report(report);
        cout << "\n";
    }
}

int main() {
    cout << "FCFS Simulator By Kanwar Adnan\n\n";
    execute_all_processes(questions);
    return 0;
}
