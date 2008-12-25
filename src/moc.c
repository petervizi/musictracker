#include "musictracker.h"
#include "utils.h"

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFF_SIZE 256

gboolean get_moc_info(struct TrackInfo* ti) {
    char* pch;
    char temp[BUFF_SIZE];
    FILE* pipe = popen("mocp -Q '%song;%artist;%album;%state;%ts;%cs'", "r");
    fgets(temp, BUFF_SIZE, pipe);
    pclose(pipe);
    pch = strtok(temp, ";");
    strcpy(ti->track, pch);
    pch = strtok(NULL, ";");
    strcpy(ti->artist, pch);
    pch = strtok(NULL, ";");
    strcpy(ti->album, pch);
    pch = strtok(NULL, ";");
    if (strcmp(pch, "STOP") == 0) {
	ti->status = STATUS_OFF;
    } else if (strcmp(pch, "PLAY") == 0) {
	ti->status = STATUS_NORMAL;
    } else if (strcmp(pch, "PAUSED") == 0) {
	ti->status = STATUS_PAUSED;
    }
    pch = strtok(NULL, ";");
    ti->totalSecs = atoi(pch);
    pch = strtok(NULL, ";");
    ti->currentSecs = atoi(pch);
    return TRUE;
}
