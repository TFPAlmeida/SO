//
// Created by tiago on 24/04/2022.
//

#include "pipes_2_.h"

int main_pipes_2_(int argc, char* argv[]){

    time_t     now, now1, now2;
    struct tm  ts;
    char       buf[80];

    // Get current time
    time(&now);
    ts = *localtime((const time_t *) 1646353043);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("Local Time %s\n", buf);

    //UTC time
    now2 = now - 19800;  //from local time to UTC time
    ts = *localtime(&now2);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("UTC time %s\n", buf);

    //TAI time valid upto next Leap second added
    now1 = now + 37;    //from local time to TAI time
    ts = *localtime(&now1);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("TAI time %s\n", buf);
    return 0;
}