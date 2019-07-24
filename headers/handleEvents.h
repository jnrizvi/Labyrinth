#ifndef HANDLE_EVENTS
#define HANDLE_EVENTS

# include "resources.h"

int eventHandler(Agent *agent);
void move(Agent *agent, float moveDirection[4]);
int processEvents(Agent *agent, int *curX, int *curY);

#endif /* HANDLE_EVENTS */