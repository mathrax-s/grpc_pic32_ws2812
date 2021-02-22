/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    garapico_led.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "GARAPICO_LED_Initialize" and "GARAPICO_LED_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "GARAPICO_LED_STATES" definition).  Both
    are defined here for convenience.
 *******************************************************************************/

#ifndef _GARAPICO_LED_H
#define _GARAPICO_LED_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "./user.h"
#include "./ledmatrix_ws2812.h"
#include "./vsc3_keyname.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    // DOM-IGNORE-END

    // *****************************************************************************
    // *****************************************************************************
    // Section: Type Definitions
    // *****************************************************************************
    // *****************************************************************************

    // *****************************************************************************

    /* Application states

      Summary:
        Application states enumeration

      Description:
        This enumeration defines the valid application states.  These states
        determine the behavior of the application at various times.
     */

    typedef enum {
        /* Application's state machine's initial state. */
        GARAPICO_LED_STATE_INIT = 0,
        GARAPICO_LED_STATE_SERVICE_TASKS,
        /* TODO: Define states used by the application state machine. */

    } GARAPICO_LED_STATES;


    // *****************************************************************************

    /* Application Data

      Summary:
        Holds application data

      Description:
        This structure holds the application's data.

      Remarks:
        Application strings and buffers are be defined outside this structure.
     */

    typedef struct {
        /* The application's current state */
        GARAPICO_LED_STATES state;

        /* TODO: Define any additional data used by the application. */

    } GARAPICO_LED_DATA;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Callback Routines
    // *****************************************************************************
    // *****************************************************************************
    /* These routines are called by drivers when certain events occur.
     */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Initialization and State Machine Functions
    // *****************************************************************************
    // *****************************************************************************

    /*******************************************************************************
      Function:
        void GARAPICO_LED_Initialize ( void )

      Summary:
         MPLAB Harmony application initialization routine.

      Description:
        This function initializes the Harmony application.  It places the
        application in its initial state and prepares it to run so that its
        GARAPICO_LED_Tasks function can be called.

      Precondition:
        All other system initialization routines should be called before calling
        this routine (in "SYS_Initialize").

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        GARAPICO_LED_Initialize();
        </code>

      Remarks:
        This routine must be called from the SYS_Initialize function.
     */

    void GARAPICO_LED_Initialize(void);


    /*******************************************************************************
      Function:
        void GARAPICO_LED_Tasks ( void )

      Summary:
        MPLAB Harmony Demo application tasks function

      Description:
        This routine is the Harmony Demo application's tasks function.  It
        defines the application's state machine and core logic.

      Precondition:
        The system and application initialization ("SYS_Initialize") should be
        called before calling this.

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        GARAPICO_LED_Tasks();
        </code>

      Remarks:
        This routine must be called from SYS_Tasks() routine.
     */

    void GARAPICO_LED_Tasks(void);

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _GARAPICO_LED_H */

/*******************************************************************************
 End of File
 */

