/*
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003,2013,2014 Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 *
 * All rights reserved.
 *
 * This code may not be resdistributed without the permission of the copyright holders.
 * Any student solutions using any of this code base constitute derviced work and may
 * not be redistributed in any form.  This includes (but is not limited to) posting on
 * public forums or web sites, providing copies to (past, present, or future) students
 * enrolled in similar operating systems courses the University of Maryland's CMSC412 course.
 */

#include <conio.h>
#include <process.h>


int main(int argc __attribute__ ((unused)), char **argv
         __attribute__ ((unused))) {

    struct Process_Info ps[20];
    int Process_count = PS(ps, sizeof(ps));
    int i = 0;


    if (Process_count == 0) {
        Print("size of user memory too small\n");
    }
    else if (Process_count == -1) {
        Print("failure\n");
    }


    else {

        Print("PID PPID PRIO STAT AFF TIME COMMAND\n");


        for (int i = 0;i < Process_count;i++) {
            char core = ' ';
            char status = ' ';
            char affinity = ' ';

            if (ps[i].status == STATUS_RUNNABLE) {
                core = '0';
                status = 'R';
            }
            else if (ps[i].status == STATUS_BLOCKED) {
                status = 'B';
            }
            else if (ps[i].status == STATUS_ZOMBIE) {
                status = 'Z';
            }


            if (ps[i].affinity == -1) {
                affinity = 'A';
            }
            else{
		        affinity = ps[i].affinity + 0x30;
	        }

            Print("%3d %4d %4d %2c%2c %3c %4d %s\n", ps[i].pid, ps[i].parent_pid, ps[i].priority, core, status, affinity, ps[i].totalTime, ps[i].name);
        }        
    }
// format string for one process line should be "%3d %4d %4d %2c%2c %3c %4d %s\n"
    return 1;
}
