#include "MMC5983MA.h"
#include <cinttypes>

/**
 * @brief Construct a new MMC5983MA Base::MMC5983MA Base object
 * 
 */
MMC5983MA_Base::MMC5983MA_Base() : dataMode(0)
{
    // Note that we default to 16-bit output mode
    // If you want 18-bit output mode, call setDataMode(1)
}

/**
 * @brief Mode 0 = 16-bit output | Mode 1 = 18-bit output
 * 
 * @param mode 
 */
void MMC5983MA_Base::setBitOutput(bool mode)
{
    if(mode == 0)
        dataMode = 0;

    else if(mode == 1)
        dataMode = 1;

    return;
}

/**
 * @brief Construct a new MMC5983MA_I2C::MMC5983MA_I2C object
 * The I2C address is 0x30 (see DATA TRANSFER section, pg 12, paragraph 2)
 * 
 * @param sda
 * @param scl
 * @param address
 */
MMC5983MA_I2C::MMC5983MA_I2C(PinName sda, PinName scl, uint8_t address) : 
    i2c(sda, scl), addr(address)
{
    //TODO
}

/**
 * @brief Construct a new MMC5983MA_SPI::MMC5983MA_SPI object
 * 
 * @param mosi
 * @param miso
 * @param sclk
 * @param ssel
 */
MMC5983MA_SPI::MMC5983MA_SPI(PinName mosi, PinName miso, PinName sclk, PinName ssel) : 
    spi(mosi, miso, sclk, ssel, use_gpio_ssel)
{
    /**
     * Mode	    Polarity	Phase
     * 0	    0	        0
     * 1	    0	        1
     * 2	    1	        0
     * 3	    1	        1
     * 
     * 00 --> clk active low, sampling on pos edge
     * 01 --> clk active low, samling on neg edge
     * 10 --> clock active high, sampling on neg edge
     * 11 --> clock active high, sampling on pos edge
     */
    spi.format(8, 0);                  // Says, use 8 bits per transfer, mode 3
    spi.set_default_write_value(0x1F); //
    spi.frequency(1'000'000);          // SPI INTERFACE I/O CHARACTERISTICS section
}

bool MMC5983MA_I2C::init()
{
    //TODO
    return false;
}

void MMC5983MA_I2C::readMagData()
{
    //TODO
    return;
}

void MMC5983MA_I2C::readRegisterI2C(Register reg, char* data, uint8_t numOfRead)
{
    //TODO
    return;
}

void MMC5983MA_I2C::writeRegisterI2C(Register reg, char* data, uint8_t numOfWrite)
{
    //TODO
    return;
}

bool MMC5983MA_SPI::init()
{
    // Might not be most efficient way to init, because we're using a 
    // pointer to a uint8_t to read a uint8_t, but it's a trade-off for better
    // performance due to bulk reads (e.g. we have cases where we read 6 bytes at once
    // and we don't want to have to call readRegisterSPI 6 times)

    // Read the product ID
    char data[1];
    readRegisterSPI(Register::ProductID_1, data, 1);

    // If we read 0x30, we successfully init'd (properly read the product ID)
    // Note that 0x30 is both the prod. ID and i2c address
    if(data[0] == 0x30)
        return true;

    // Otherwise, we failed to init
    return false;
}

void MMC5983MA_SPI::readMagData()
{
    //TODO
    char data[8];
    readRegisterSPI(Register::Xout0, data, 7);

    mag18.x = (data[0] << 10) | (data[1] << 2) | ((data[6] >> 6) & 0x3);
    mag18.y = (data[2] << 10) | (data[3] << 2) | ((data[6] >> 4) & 0x3);
    mag18.z = (data[4] << 10) | (data[5] << 2) | ((data[6] >> 2) & 0x3);

    temp = data[7];
        
    printf("x: %ld\n", mag18.x);
    printf("y: %ld\n", mag18.y);
    printf("z: %ld\n", mag18.z);
    printf("temp: %d\n", temp);

    return;
}

void MMC5983MA_SPI::readRegisterSPI(Register reg, char* data, uint8_t numOfRead)
{
    // Be aware that if we use async transfers, we need to use the CacheAlignedBuffer
    // You can declare it like this:
    // CacheAlignedBuffer<uint8_t, 2> response;

    spi.select();
    spi.write(0x80 | static_cast<uint8_t>(reg));
    // set data to spi.write(0x0) to read data
    for(int i=0; i<numOfRead; i++)
    {
        data[i] = spi.write(0x1F);
    }
    spi.deselect();

    // printf("reg: %x\n", (0x80 | static_cast<uint8_t>(reg)));
    // printf("data: %x\n", *reinterpret_cast<uint8_t*>(data));
    // printf("whoami: %x\n", whoami);

    // uint8_t toSend = 0x80 | static_cast<uint8_t>(reg);
    // printf("toSend: %x\n", toSend);

    // spi.select();
    // int numBytesWritten = spi.write(reinterpret_cast<char*>(toSend), 1, data, numOfRead);
    // spi.deselect();

    // printf("data: %d\n", *reinterpret_cast<uint8_t*>(data));
    // printf("numBytesWritten: %d\n", numBytesWritten);

    return;
}

void MMC5983MA_SPI::writeRegisterSPI(Register reg, char* data, uint8_t numOfWrite)
{
    //TODO
    return;
}

void MMC5983MA_SPI::readStatusRegister()
{
    char status[1];
    readRegisterSPI(Register::Status, status, 1);

    printf("status: %x\n", *reinterpret_cast<uint8_t*>(status));
    return;
}

void MMC5983MA_SPI::readTemp()
{
    char temp[1];
    readRegisterSPI(Register::Tout, temp, 1);

    printf("temp: %x\n", *reinterpret_cast<uint8_t*>(temp));
    return;
}