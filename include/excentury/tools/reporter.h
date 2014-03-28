/** REPORTER.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: December 10, 2010
% Last Modified: December 13, 2013
% Notes: http://stackoverflow.com/a/20587065/788553
%        Explains why the values the reporter should report are not
%        displayed correctly when using optimization flags.
*/

#ifndef XC_REPORTER_H
#define XC_REPORTER_H

#include "timer.h"
#include <pthread.h>

namespace excentury {

void* run_reporter(void*);

class Reporter {
public:
    pthread_t thread;
    bool stdstream;
    FILE* fp;
    bool end_called;

    struct timespec sleepTime;
    struct timespec remainingSleepTime;

    const char* filename;
    const int sleepT;
    timer tm;

    Reporter(int st, FILE* fp_):
        fp(fp_), filename(NULL), stdstream(true), sleepT(st), tm(fp_)
    {
        begin_report();
    }
    Reporter(int st, const char* fn):
        fp(NULL), filename(fn), stdstream(false), sleepT(st)
    {
        begin_report();
    }
    ~Reporter() {
        if (!end_called) end_report();
    }
    void begin_report() {
        end_called = false;
        tm.tic();
        if (!stdstream) fp = fopen(filename, "w");
        fprintf(fp, "reporting every %d seconds ...\n", sleepT);
        if (!stdstream) fclose(fp);
        pthread_create(&thread, NULL, run_reporter, this);
    }
    void sleep() {
        sleepTime.tv_sec=sleepT;
        sleepTime.tv_nsec=0;
        nanosleep(&sleepTime,&remainingSleepTime);
    }
    virtual void report() = 0;
    void end_report() {
        end_called = true;
        pthread_cancel(thread);
        pthread_join(thread, NULL);
        tm.toc();
        if (!stdstream) fp = fopen(filename, "a");
        fprintf(fp, "reported for ");
        tm.set_file(fp);
        tm.print();
        fprintf(fp, "\n");
        if (!stdstream) fclose(fp);
    }
};

void* run_reporter(void* rep_) {
    Reporter* rep = (Reporter*)rep_;
    while (1) {
        if (!rep->stdstream) rep->fp = fopen(rep->filename, "a");
        rep->report();
        if (!rep->stdstream) fclose(rep->fp);
        rep->sleep();
    }
}

}

#endif
