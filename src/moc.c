#include "musictracker.h"
#include "utils.h"

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFF_SIZE 256

gboolean get_moc_info(struct TrackInfo* ti) {
    char* pch;
    char temp[BUFF_SIZE];
    FILE* pipe = popen("mocp -Q '%song ;%artist ;%album ;%state;%ts ;%cs ;%file ; '", "r");
    if (!pipe) {
	trace("No mocp");
	return FALSE;
    }
    fgets(temp, BUFF_SIZE, pipe);
    pclose(pipe);
    pch = strtok(temp, ";");
    if (pch != NULL) {
	strcpy(ti->track, pch);
    } else {
	strcpy(ti->track, "");
    }
    pch = strtok(NULL, ";");
    if (pch != NULL) {
	strcpy(ti->artist, pch);
    } else {
	strcpy(ti->artist, "");
    }
    pch = strtok(NULL, ";");
    if (pch != NULL) {
	strcpy(ti->album, pch);
    } else {
	strcpy(ti->album, "");
    }
    pch = strtok(NULL, ";");
    if (pch != NULL) {
	if (strcmp(pch, "STOP") == 0) {
	    ti->status = STATUS_OFF;
	} else if (strcmp(pch, "PLAY") == 0) {
	    ti->status = STATUS_NORMAL;
	} else if (strcmp(pch, "PAUSED") == 0) {
	    ti->status = STATUS_PAUSED;
	} else {
	    ti->status = STATUS_OFF;
	}
    } else {
	ti->status = STATUS_OFF;
    }
    pch = strtok(NULL, ";");
    if (pch != NULL) {
	ti->totalSecs = atoi(pch);
    } else {
	ti->totalSecs = 0;
    }
    pch = strtok(NULL, ";");
    if (pch != NULL) {
	ti->currentSecs = atoi(pch);
    } else {
	ti->currentSecs = 0;
    }
    // Check for internet radio
    pch = strtok(NULL, ";");
    if (strcmp(ti->album, " ") == 0 && strcmp(ti->artist, " ") == 0) {
	if (strstr(pch, "http://") != NULL) {
	    strcpy(ti->artist, pch);
	    strcpy(ti->album, "Online Radio");
	}
    }
    return TRUE;
}
