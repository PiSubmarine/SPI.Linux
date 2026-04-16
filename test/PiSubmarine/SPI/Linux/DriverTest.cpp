#include <gtest/gtest.h>
#include "PiSubmarine/SPI/Linux/Driver.h"
#include "PiSubmarine/SPI/Api/DriverConcept.h"

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <span>

namespace PiSubmarine::SPI::Linux
{
    TEST(DriverTest, Construct)
    {
        static_assert(Api::DriverConcept<Driver>, "Driver must satisfy DriverConcept");
        Driver driver{"/dev/spidev0.0", 5000000};
    }

    TEST(DriverTest, Read)
    {
        Driver driver{"/dev/spidev0.0", 1000000};

        uint8_t reg = 7;
        uint16_t dataOut = reg;
        // dataOut |= (1 << 14);
        uint16_t dataIn = 0;
        bool ok = driver.WriteRead(
            std::span<const uint8_t>(reinterpret_cast<const uint8_t*>(&dataOut), 2),
            std::span<uint8_t>(reinterpret_cast<uint8_t*>(&dataIn), 2));
        if (!ok)
        {
            std::string err = std::strerror(errno);
            SCOPED_TRACE(err);
        }
        std::cout << std::hex << dataIn << std::endl;
        ASSERT_TRUE(ok);
        sleep(1);
    }
}
