#include "PiSubmarine/SPI/Linux/Driver.h"

#include <cassert>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <stdexcept>

namespace PiSubmarine::SPI::Linux
{
    Driver::Driver(std::string_view devicePath, uint32_t speed, uint8_t bitsPerWord, uint8_t rdMode, uint8_t wrMode,
                   size_t delay) :
        m_DevicePath(devicePath),
        m_Delay(delay)
    {
        m_Fd = open(m_DevicePath.c_str(), O_RDWR);
        if (m_Fd < 0)
        {
            throw std::runtime_error("Failed to open " + m_DevicePath);
        }

        ioctl(m_Fd, SPI_IOC_RD_MODE, &rdMode);
        ioctl(m_Fd, SPI_IOC_WR_MODE, &wrMode);
        ioctl(m_Fd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
        ioctl(m_Fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    }

    Driver::~Driver()
    {
        if (m_Fd > 0)
        {
            close(m_Fd);
        }
    }

    bool Driver::WriteRead(const std::span<const uint8_t> txData, const std::span<uint8_t> rxData)
    {
        assert(m_Fd > 0);
        if (txData.empty() || txData.size() != rxData.size())
        {
            return false;
        }

        spi_ioc_transfer tr{0};
        std::memset(&tr, 0, sizeof(tr));

        tr.tx_buf = reinterpret_cast<unsigned long>(txData.data());
        tr.rx_buf = reinterpret_cast<unsigned long>(rxData.data());
        tr.len = static_cast<uint32_t>(txData.size());
        // tr.cs_change = 1;
        tr.delay_usecs = m_Delay;

        const int ret = ioctl(m_Fd, SPI_IOC_MESSAGE(1), &tr);
        return ret == static_cast<int>(txData.size());
    }
}
