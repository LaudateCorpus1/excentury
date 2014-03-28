/** TIMER.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: April 8, 2010
% Last Modified: December 13, 2013
*/

#ifndef XC_TIMER_H
#define XC_TIMER_H

namespace excentury {

class timer {
private:
    struct timeval startT;
    struct timeval stopT;
    struct timeval elapsedT;
    bool running;
    FILE* fp;
public:
    timer(): running(false), fp(stdout) {}
    timer(FILE* fp_): running(false), fp(fp_) {}
    void set_file(FILE* fp_) {
        fp = fp_;
    }
    void print() {
        long int hrs, min, sec, usec;
        usec = elapsedT.tv_usec;
        sec = elapsedT.tv_sec;
        hrs = sec/3600; sec = sec%3600;
        min = sec/60; sec = sec%60;
        if (hrs != 0 && min != 0) {
            fprintf(fp, "%ldhrs:%ldmin:%ldsec:%ldusec",
                        hrs, min, sec, usec);
        } else if (min != 0) {
            fprintf(fp, "%ldmin:%ldsec:%ldusec",
                        min, sec, usec);
        } else {
            fprintf(fp, "%ldsec:%ldusec",
                        sec, usec);
        }
    }
    void tic() {
        if (running) {
            fprintf(fp, "Already tic-ing...\n");
        } else {
            running = true;
            gettimeofday(&startT, NULL);
        }
    }
    void toc(bool display_=false) {
        int nsec;
        if (running) {
            running = false;
            gettimeofday(&stopT, NULL);
            if (stopT.tv_usec < startT.tv_usec) {
                nsec = (int)(startT.tv_usec - stopT.tv_usec)/1000000 + 1;
                startT.tv_usec -= 1000000*nsec;
                startT.tv_sec += nsec;
            }
            if (stopT.tv_usec-startT.tv_usec > 1000000) {
                nsec = (int)(stopT.tv_usec - startT.tv_usec)/1000000;
                startT.tv_usec += 1000000*nsec;
                startT.tv_sec -= nsec;
            }
            elapsedT.tv_sec = stopT.tv_sec - startT.tv_sec;
            elapsedT.tv_usec = stopT.tv_usec - startT.tv_usec;
            if (display_) {
                fprintf(fp, "Time elapsed = ");
                print();
                fprintf(fp, "\n");
            }
        } else {
            fprintf(fp, "You have not called tic()...\n");
        }
    }
    void to_str(char* str_) {
        long int hrs, min, sec, usec;
        usec = elapsedT.tv_usec;
        sec = elapsedT.tv_sec;
        hrs = sec/3600; sec = sec%3600;
        min = sec/60; sec = sec%60;
        if (hrs != 0 && min != 0){
            sprintf(str_, "%ldhrs:%ldmin:%ldsec:%ldusec", hrs, min, sec, usec);
        } else if (min != 0) {
            sprintf(str_, "%ldmin:%ldsec:%ldusec", min, sec, usec);
        } else {
            sprintf(str_, "%ldsec:%ldusec", sec, usec);
        }
    }
    long int get_seconds() const {
        return elapsedT.tv_usec;
    }
    long int get_microseconds() const {
        return elapsedT.tv_sec;
    }
    void print_date(const char* format) const {
        // http://www.cplusplus.com/reference/ctime/strftime/
        char buffer[100];
        struct timeval tv;
        time_t curtime;
        gettimeofday(&tv, NULL);
        curtime = tv.tv_sec;
        strftime(buffer,(size_t)100,format,localtime(&curtime));
        fprintf(fp, "%s",buffer);
    }
};

}

#endif
