#include "musictracker.h"

int main() {
    struct TrackInfo ti;
    gboolean ret;
    ret = get_moc_info(&ti);
    printf("Track: %s\n", ti.track);
    printf("Artist: %s\n", ti.artist);
    printf("Album: %s\n", ti.album);
    printf("Player: %s\n", ti.player);
    printf("Status: %d\n", ti.status);
    printf("Total: %i\n", ti.totalSecs);
    printf("Current: %i\n", ti.currentSecs);
    return 0;
}

