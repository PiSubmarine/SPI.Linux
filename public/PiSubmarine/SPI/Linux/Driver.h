#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <linux/spi/spidev.h>

#include "PiSubmarine/SPI/Api/IDriver.h"

namespace PiSubmarine::SPI::Linux
{
    class Driver : public Api::IDriver
    {
    public:
        explicit Driver(std::string_view devicePath, uint32_t speed, uint8_t bitsPerWord = 8, uint8_t rdMode = SPI_MODE_0, uint8_t wrMode = SPI_MODE_0, size_t delay = 1);
        ~Driver() override;

        bool WriteRead(uint8_t* txData, uint8_t* rxData, std::size_t len) override;

    private:
        std::string m_DevicePath;
        int m_Fd = 0;
        size_t m_Delay = 0;
    };
}