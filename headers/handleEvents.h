#ifndef HANDLE_EVENTS
#define HANDLE_EVENTS

# include "resources.h"

void move(Agent *agent, int distance, int dir);
int processEvents(Agent *agent, int *curX, int *curY, int *bCurY, int *fCurY);

#endif /* HANDLE_EVENTS */