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
    Driver::Driver(std::string_view devicePath, uint32_t speed, uint8_t bitsPerWord, uint8_t rdMode, uint8_t wrMode):
        m_DevicePath(devicePath)
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

    bool Driver::WriteRead(uint8_t* txData, uint8_t* rxData, size_t len)
    {
        assert(m_Fd > 0);
        if (len == 0)
        {
            return false;
        }

        spi_ioc_transfer tr{0};
        std::memset(&tr, 0, sizeof(tr));

        tr.tx_buf = reinterpret_cast<unsigned long>(txData);
        tr.rx_buf = reinterpret_cast<unsigned long>(rxData);
        tr.len = static_cast<uint32_t>(len);
        // tr.cs_change = 1;
        tr.delay_usecs = 1;

        const int ret = ioctl(m_Fd, SPI_IOC_MESSAGE(1), &tr);
        return ret == len;
    }
}
