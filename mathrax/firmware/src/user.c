/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdint.h>
#include "config/default/peripheral/gpio/plib_gpio.h"
#include "./user.h"
#include "./ledmatrix_ws2812.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
//int global_data;

uint8_t dataPos;
uint8_t myData[2];
uint8_t lastData;

uint8_t red[1024];
uint8_t blu[1024];
uint8_t grn[1024];

uint8_t myRed;
uint8_t myGrn;
uint8_t myBlu;

uint8_t aCnt;
uint8_t frameCount;
uint8_t firstReset;
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
//static int ExampleLocalFunction(int param1, int param2) {
//    return 0;
//}

int setPixelColor(unsigned int pixel, unsigned char r, unsigned char g, unsigned char b) {

    red[pixel] = r;
    grn[pixel] = g;
    blu[pixel] = b;

    return 0;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int setPattern (const unsigned char* ptn, unsigned char div) 

  @Summary
    Set ledmatrix pattern of 16x16 dots.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */

int setPattern(const unsigned char * ptn, unsigned char div) {
    unsigned char x, y;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            myRed = (int) (ptn[x + y * 16]) >> div;
            myGrn = (int) (ptn[256 + x + y * 16]) >> div;
            myBlu = (int) (ptn[512 + x + y * 16]) >> div;

            setPixelColor((x * 2) + (y * 64), myRed, myGrn, myBlu);
            setPixelColor((x * 2) + (y * 64) + 1, myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2), myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2 + 1), myRed, myGrn, myBlu);
        }
    }
    return 0;
}

int setAnimation(const unsigned char * ptn, unsigned char div) {
    unsigned char x, y;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            myRed = ptn[x + y * 16] >> div;
            myGrn = ptn[256 + x + y * 16] >> div;
            myBlu = ptn[512 + x + y * 16] >> div;

            setPixelColor((x * 2) + (y * 64), myRed, myGrn, myBlu);
            setPixelColor((x * 2) + (y * 64) + 1, myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2), myRed, myGrn, myBlu);
            setPixelColor(63 + (y * 64) - (x * 2 + 1), myRed, myGrn, myBlu);
        }
    }
    return 0;
}

int show() {
    unsigned int i;

    __builtin_disable_interrupts();

    neopixel_Clear();
    for (i = 0; i < 5000; i++) {
        Nop();
    }

    for (i = 0; i < 1024; i++) {
        //Bit7
        if (grn[i] & 0b10000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit6
        if (grn[i] & 0b01000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit5
        if (grn[i] & 0b00100000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit4
        if (grn[i] & 0b00010000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();
        }

        //Bit3
        if (grn[i] & 0b00001000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit2
        if (grn[i] & 0b00000100) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit1
        if (grn[i] & 0b00000010) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }
        //Bit0
        if (grn[i] & 0b00000001) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }


        //Bit7
        if (red[i] & 0b10000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit6
        if (red[i] & 0b01000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit5
        if (red[i] & 0b00100000) {
            neopixel_Set();
            Neopixel700us();
            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit4
        if (red[i] & 0b00010000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit3
        if (red[i] & 0b00001000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit2
        if (red[i] & 0b00000100) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit1
        if (red[i] & 0b00000010) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }
        //Bit0
        if (red[i] & 0b00000001) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }






        //Bit7
        if (blu[i] & 0b10000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit6
        if (blu[i] & 0b01000000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit5
        if (blu[i] & 0b00100000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit4
        if (blu[i] & 0b00010000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit3
        if (blu[i] & 0b00001000) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit2
        if (blu[i] & 0b00000100) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }

        //Bit1
        if (blu[i] & 0b00000010) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {
            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }
        //Bit0
        if (blu[i] & 0b00000001) {
            neopixel_Set();
            Neopixel700us();

            neopixel_Clear();
            Neopixel600us();

        } else {

            neopixel_Set();
            Neopixel350us();
            neopixel_Clear();
            Neopixel800us();

        }
    }

    //    INTEnableInterrupts();
    __builtin_enable_interrupts();

    return 0;
}

int deletePattern() {
    int i;
    for (i = 0; i < 1024; i++) {

        red[i] = 0;
        grn[i] = 0;
        blu[i] = 0;
    }
    return 0;
}

int resetAnimation() {
    int i = 0;

    for (i = 0; i < 1024; i++) {
        red[i] = 0;
        grn[i] = 0;
        blu[i] = 0;
    }
    frameCount = 0;
    aCnt = 0;

    return 0;

}

int g_animation(GARAPICO _g, uint8_t _speed, uint8_t _loop, uint8_t _bright) {
    
    //    ENERGY
    if (frameCount % _speed == 0) {
        frameCount = 0;
        aCnt++;
        if (aCnt >= _g.framesize) {
            if (_loop == ONCE) {
                aCnt = _g.framesize - 1;
            } else if (_loop == LOOP) {
                aCnt = 0;
            }
            if (_g.reset == 1) {
                myData[0] = 0;
                deletePattern();
            }
        }
    }
    setPattern(_g.picture[_g.frame[aCnt]], _bright);
    return 0;
}

/* *****************************************************************************
 End of File
 */
