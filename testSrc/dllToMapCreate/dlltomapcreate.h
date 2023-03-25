#ifndef DLLTOMAPCREATE_H
#define DLLTOMAPCREATE_H

#include "dllToMapCreate_global.h"

extern "C"
DECL_EXPORT bool killNpc(char* roomName, char* backBegin, char* backEnd);

extern "C"
DECL_EXPORT bool boatIn(char* roomName, char* backStr);

extern "C"
DECL_EXPORT bool cheIn(char* roomName, char* cmd, char* backStr);

#endif // DLLTOMAPCREATE_H
