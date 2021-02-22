/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    serial_rcv.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "SERIAL_RCV_Initialize" and "SERIAL_RCV_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "SERIAL_RCV_STATES" definition).  Both
    are defined here for convenience.
 *******************************************************************************/

#ifndef _SERIAL_RCV_H
#define _SERIAL_RCV_H

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
#include "driver/usart/drv_usart.h"
#include "peripheral/gpio/plib_gpio.h"
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

    #define SERIAL_RCV_DATA_SIZE   1

    typedef enum {
        /* Application's state machine's initial state. */
        SERIAL_RCV_STATE_INIT = 0,
        SERIAL_RCV_STATE_SERVICE_TASKS,
        /* TODO: Define states used by the application state machine. */
        //        SERIAL_RCV_STATE_TRANSMIT_MESSAGE,
        //        SERIAL_RCV_STATE_WAIT_MESSAGE_TRANSFER_COMPLETE,

        SERIAL_RCV_STATE_RECEIVE_DATA,
        SERIAL_RCV_STATE_WAIT_RECEIVE_COMPLETE,
        SERIAL_RCV_STATE_GARAPIKO_RECEIVE,
        SERIAL_RCV_STATE_GARAPIKO_LED,

        //        SERIAL_RCV_STATE_TRANSMIT_DATA,
        //        SERIAL_RCV_STATE_WAIT_TRANSMIT_COMPLETE,

        SERIAL_RCV_STATE_ERROR,
        SERIAL_RCV_STATE_IDLE,
    } SERIAL_RCV_STATES;


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
        SERIAL_RCV_STATES state;

        /* TODO: Define any additional data used by the application. */
        DRV_HANDLE usartHandle;
        DRV_USART_BUFFER_HANDLE bufferHandle;
        char readBuffer[SERIAL_RCV_DATA_SIZE];
//        volatile bool transferStatus;
    } SERIAL_RCV_DATA;

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
        void SERIAL_RCV_Initialize ( void )

      Summary:
         MPLAB Harmony application initialization routine.

      Description:
        This function initializes the Harmony application.  It places the
        application in its initial state and prepares it to run so that its
        SERIAL_RCV_Tasks function can be called.

      Precondition:
        All other system initialization routines should be called before calling
        this routine (in "SYS_Initialize").

      Parameters:
        None.

      Returns:
        None.

      Example:
        <code>
        SERIAL_RCV_Initialize();
        </code>

      Remarks:
        This routine must be called from the SYS_Initialize function.
     */

    void SERIAL_RCV_Initialize(void);


    /*******************************************************************************
      Function:
        void SERIAL_RCV_Tasks ( void )

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
        SERIAL_RCV_Tasks();
        </code>

      Remarks:
        This routine must be called from SYS_Tasks() routine.
     */

    void SERIAL_RCV_Tasks(void);
    void GARAPIKO_receive(uint8_t RcvData);
    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _SERIAL_RCV_H */

/*******************************************************************************
 End of File
 */

