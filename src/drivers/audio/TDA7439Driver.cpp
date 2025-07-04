#include "TDA7439Driver.h"
#include "core/Logger.h"

TDA7439Driver::TDA7439Driver(I2CBus& bus, uint8_t address)
    : _i2c(bus), _i2cAddress(address) {   // ✅ Reference MUST be initialized here
}

bool TDA7439Driver::Init() {
    //Logger::Info("Audio", "TDA7439 initialized at address 0x%02X", _address);
    AddLogDebug("TDA7439", "TDA7439 initialized at address 0x%02X", getAddress()); 
    return true;
}

void TDA7439Driver::SetVolume(uint8_t level) {
    AddLogCore("TDA7439Driver", "Set Volume %d",level);
    uint8_t val = constrain(31 - level, 0, 31);
    WriteRegister(0x00, val);
    AddLogDebug("TDA7439", "Volume set to %d", level);
}

void TDA7439Driver::SetInput(uint8_t input) {
    WriteRegister(0x01, input & 0x03);
}

void TDA7439Driver::SetLoudness(bool enable) {
    WriteRegister(0x02, enable ? 0x10 : 0x00);
}

void TDA7439Driver::SetBass(int8_t level) {
    WriteRegister(0x03, level & 0x0F);
}

void TDA7439Driver::SetTreble(int8_t level) {
    WriteRegister(0x04, level & 0x0F);
}

void TDA7439Driver::SetBalance(int8_t level) {
    WriteRegister(0x04, level & 0x0F);
}

void TDA7439Driver::SaveState() {
    // Use EEPROM or FlashStorage
}

void TDA7439Driver::LoadState() {
    // Load previous settings
}

void TDA7439Driver::WriteRegister(uint8_t reg, uint8_t value) {
    AddLogCore("TDA7439","Write reg 0x%02X = 0x%02X", reg, value);
    _i2c.Write(_i2cAddress,reg,value);

    AddLogCore("TDA7439", "Write Register End");
}

