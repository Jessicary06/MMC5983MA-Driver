#include <mbed.h>
#include <cinttypes>
#include "MMC5983MA.h"

int main()
{
    PinName mosi = PB_5;    // SPI 1
    PinName miso = PA_6;    // SPI 1
    PinName sclk = PA_5;    // SPI 1
    PinName ssel = PD_14;   // SPI 1
    
    MMC5983MA_SPI mag(mosi, miso, sclk, ssel);
    
    while (1)
    {
        printf("\nMMC5983MA Test Suite:\n");
        printf("Select a test: \n");
        printf("1.  Test MMC5983MA init\n");
        printf("2.  Test MMC5983MA readMagData\n");
        printf("3.  Test MMC5983MA readStatusRegister\n");
        printf("4.  Test MMC5983MA readTemp\n");
        printf("9.  Exit Test Suite\n");

        // scanf("%d", &test);
        int testNumber = 0;
        int read = 0;
        
        while (read <= 0) {
            read = scanf("%d", &testNumber);
            if (read <= 0) {
                // Clear the input buffer
                while (getchar() != '\n');
                printf("\nInvalid input. Please enter a valid test number: ");
            }
        }
        printf("Running test %d:\n\n", testNumber);

        // Run Tests
        switch (testNumber)
        {
            case 1: // Test mag init
            {
                bool init_success = mag.init();
                printf(init_success ? "Init Success!\n" : "Init Failed!\n");
                break;
            }
            case 2:
            {
                mag.readMagData();
                break;
            }
            case 3:
            {
                mag.readStatusRegister();
                break;
            }
            case 4:
            {
                mag.readTemp();
                break;
            }
            case 9: // Exit test suite
            {
                printf("\nExiting Test Suite\n");
                return 0;
            }
            default:
            {
                printf("%d Is an Invalid Test Number Selection.\n", testNumber);
                fflush(stdin);
                break;
            }
        }

        printf("Done.\r\n");
    }
}