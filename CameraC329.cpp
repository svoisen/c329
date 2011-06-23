#include "CameraC329R.h"

//-----------------------------------------------------------------------------
//
// Constants
//
//-----------------------------------------------------------------------------

static const byte CMD_INITIAL = 0x01;
static const byte CMD_GETPICTURE = 0x04;
static const byte CMD_SNAPSHOT = 0x05;
static const byte CMD_RESET = 0x08;
static const byte CMD_POWEROFF = 0x09;
static const byte CMD_DATA = 0x0A;
static const byte CMD_SYNC = 0x0D;
static const byte CMD_ACK = 0x0E;
static const byte CMD_NAK = 0x0F;
static const byte CMD_QUALITY = 0x10;

/**
 * Constructor
 */
CameraC329::CameraC329()
{
}

/**
 * Synchronize with the camera. Synchronization will be attempted up to
 * MAX_SYNC_ATTEMPTS. You must synchronize with the camera before you can
 * call other methods.
 *
 * @return True if successful, false otherwise.
 */
bool CameraC329::sync()
{
  uint8_t syncAttempts = 0;
  bool success = false;

  createCommand(CMD_SYNC, 0, 0, 0, 0);
}

void CameraC329::createCommand(const byte command, byte param1, byte param2, byte param3, byte param4)
{
}
