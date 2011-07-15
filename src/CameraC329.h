#ifndef CAMERAC329_H_
#define CAMERAC329_H_

#include "WProgram.h"
#include "WConstants.h"
#include <inttypes.h>

// The byte size of UART commands
#define CMD_SIZE 8

// Number of sync attempts to try before giving up
#define MAX_SYNC_ATTEMPTS 60

// How long to wait for serial communication responses
#define RESPONSE_DELAY 100

class CameraC329
{
  public:
    CameraC329();
    bool sync();

  private:
    byte outputCommand[CMD_SIZE];
    byte inputCommand[CMD_SIZE];
    void sendCommand();
    bool waitForACK(uint32_t, uint8_t);
    bool waitForResponse(uint32_t);
    bool waitForResponse(uint32_t, byte[], uint16_t);
    void setOutputCommand(const byte, byte, byte, byte, byte);
};

#endif // CAMERAC329_H_
