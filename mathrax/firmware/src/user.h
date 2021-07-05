/* ************************************************************************** */
/** Descriptive File Name

  @Company
   MATHRAX LLC.

  @File Name
    usr.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _USER_H    /* Guard against multiple inclusion */
#define _USER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdint.h>


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
#define EXAMPLE_CONSTANT 0

#define ARRAY_SIZE(dArray) (sizeof(dArray)/sizeof(dArray[0]))
#define ONCE 0
#define LOOP 1

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    //    typedef struct _example_struct_t {
    //        /* Describe structure member. */
    //        int some_number;
    //
    //        /* Describe structure member. */
    //        bool some_flag;
    //
    //    } example_struct_t;

    extern uint8_t red[1024];
    extern uint8_t blu[1024];
    extern uint8_t grn[1024];

    extern uint8_t myRed;
    extern uint8_t myGrn;
    extern uint8_t myBlu;

    extern uint8_t aCnt;
    extern uint8_t frameCount;
    extern uint8_t firstReset;

    extern uint8_t dataPos;
    extern uint8_t myData[2];
    extern uint8_t lastData;

    extern uint8_t aCnt;
    extern uint8_t frameCount;
    extern uint8_t firstReset;

    typedef struct {
        const unsigned char (*picture)[768];
        const unsigned char *frame;
        unsigned int framesize;
        unsigned char reset;
        unsigned char bright;
    } GARAPICO;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    int setPixelColor(unsigned int pixel, unsigned char r, unsigned char g, unsigned char b);
    int show(void);
    int deletePattern(void);
    int resetAnimation(void);
    int g_animation(GARAPICO _g, uint8_t _speed, uint8_t _loop, uint8_t _bright);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _USER_H */

/* *****************************************************************************
 End of File
 */
