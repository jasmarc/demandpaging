# Demand Paging Simulator
This project was done as an assignment for [CSC4320 Operating Systems](http://www.cs.gsu.edu/~skarmakar/csc4320_teaching.html) at [Georgia State University](http://www.cs.gsu.edu/). See [here](http://www.cs.gsu.edu/~skarmakar/cs4320/assignment4.htm) and [here](http://www.cs.gsu.edu/~skarmakar/cs4320/asg4T1Details.htm) for original assignment.

## Compilation and Usage
Please run "make clean && make" to compile.
You may then use a4 as described below

    usage:          ./a4 [OPTIONS]
    example:        ./a4 -m1 -p2 -s3 -j4 -n5 -r fifo -i input.txt
    options:
     -h             Print this message.
     -i <file>      Read comma-separated file with arrive,burst
     -m             The machine size (in words)
     -p             The page size (in words)
     -s             The size of a processes
     -j             The 'job mix'
     -n             The number of simulated references for each process
     -r <pager(s)>  Specify pager(s) to use.
                    Valid pagers are: fifo, clock, lru

---
