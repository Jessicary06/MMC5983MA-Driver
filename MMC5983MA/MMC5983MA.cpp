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
    spi.format(8, 2);                   // 
    spi.set_default_write_value(0x1F);  //
    spi.frequency(10'000'000);          // SPI INTERFACE I/O CHARACTERISTICS section
}

bool MMC5983MA_I2C::init()
{
    //TODO
    return false;
}

void MMC5983MA_I2C::readMagData(void *data)
{
    //TODO
    return;
}

void MMC5983MA_I2C::readRegisterI2C(Register reg, void* data, uint8_t numToRead)
{
    //TODO
    return;
}

void MMC5983MA_I2C::writeRegisterI2C(Register reg, void* data, uint8_t numToWrite)
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
    uint8_t data = 0;
    readRegisterSPI(Register::ProductID_1, &data, 1);

    // If we read 0x30, we successfully init'd (properly read the product ID)
    if(data == 0x30)
        return true;
    
    // Otherwise, we failed to init
    return false;
}

void MMC5983MA_SPI::readMagData(void *data)
{
    //TODO
    return;
}

void MMC5983MA_SPI::readRegisterSPI(Register reg, void* data, uint8_t numToRead)
{
    spi.select();
    spi.write(0x80 | static_cast<uint8_t>(reg));
    int whoami = spi.write(0x00);
    spi.deselect();

    printf("reg: %x\n", (0x80 | static_cast<uint8_t>(reg)));
    printf("whoami: %d\n", whoami);
    printf("data: %d\n", *reinterpret_cast<uint8_t*>(data));

    // int toSend = 0x80 | static_cast<uint8_t>(reg);
    // printf("toSend: %x\n", toSend);

    // spi.select();
    // int numBytesWritten = spi.write(reinterpret_cast<char*>(toSend), 1,
    //                                 reinterpret_cast<char*>(data), numToRead);
    
    // spi.deselect();

    // printf("numBytesWritten: %d\n", numBytesWritten);

    return;
}

void MMC5983MA_SPI::writeRegisterSPI(Register reg, void* data, uint8_t numToWrite)
{
    //TODO
    return;
}