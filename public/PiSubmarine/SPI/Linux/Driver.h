#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
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

        bool WriteRead(std::span<const uint8_t> txData, std::span<uint8_t> rxData) override;

    private:
        std::string m_DevicePath;
        int m_Fd = 0;
        size_t m_Delay = 0;
    };
}
