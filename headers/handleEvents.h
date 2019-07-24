#ifndef HANDLE_EVENTS
#define HANDLE_EVENTS

# include "resources.h"

int eventHandler(Agent *agent, Coll allRects, int numRects);
void move(Agent *agent, int distance, int dir);
int processEvents(Agent *agent, int *curX, int *curY);

#endif /* HANDLE_EVENTS */