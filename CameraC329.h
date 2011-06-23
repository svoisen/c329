#ifndef CAMERAC329_H_
#define CAMERAC329_H_

#include "WProgram.h"
#include "WConstants.h"
#include <inttypes.h>

// The byte size of UART commands
#define CMD_SIZE 8

class CameraC329R
{
  public:
    CameraC329R();
    bool sync();

  private:
    byte outCommand[CMD_SIZE];
    byte inCommand[CMD_SIZE];
    void createCommand(const byte, byte, byte, byte, byte);
}

#endif // CAMERAC329_H_
