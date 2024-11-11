#include "Device/Driver/OGNBridge.hpp"
#include "Device/Driver.hpp"

class OGNBridgeDevice : public AbstractDevice {
};

static Device *
OGNBridgeCreateOnPort([[maybe_unused]] const DeviceConfig &config, [[maybe_unused]] Port &com_port)
{
  return new OGNBridgeDevice();
}

const struct DeviceRegister ognbridge_driver = {
  _T("OGNBridge"),
  _T("OGNBridge"),
  0,
  OGNBridgeCreateOnPort,
};
