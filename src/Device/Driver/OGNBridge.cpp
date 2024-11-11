#include "Device/Driver/OGNBridge.hpp"
#include "Device/Driver.hpp"
#include "NMEA/Checksum.hpp"
#include "NMEA/Info.hpp"
#include "NMEA/InputLine.hpp"
#include "LogFile.hpp"

class OGNBridgeDevice : public AbstractDevice {
public:
  bool ParseNMEA(const char *line, struct NMEAInfo &info) override;
};

bool
OGNBridgeDevice::ParseNMEA(const char *String, NMEAInfo &info)
{
  LogString("Recieving NMEA: " + std::String(String));
  //LogString("NMEA Info: " + info);
  return true;
}

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
