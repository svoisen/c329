#ifndef CAMERAC329_H_
#define CAMERAC329_H_

#include "WProgram.h"
#include "WConstants.h"
#include <inttypes.h>

// The byte size of UART commands
#define CMD_SIZE 8

// Number of sync attempts to try before giving up
#define MAX_SYNC_ATTEMPTS 60

class CameraC329R
{
  public:
    CameraC329R();
    bool sync();

  private:
    byte outputCommand[CMD_SIZE];
    byte inputCommand[CMD_SIZE];
    void setOutputCommand(const byte, byte, byte, byte, byte);
}

#endif // CAMERAC329_H_
