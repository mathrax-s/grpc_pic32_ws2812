/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    serial_rcv.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "serial_rcv.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the SERIAL_RCV_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

SERIAL_RCV_DATA serial_rcvData;

static const char messageBuffer[] =
"*** GARAPICO ***\r\n";
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */
static void SERIAL_RCV_USARTBufferEventHandler(
    DRV_USART_BUFFER_EVENT bufferEvent,
    DRV_USART_BUFFER_HANDLE bufferHandle,
    uintptr_t context
)
{
    switch(bufferEvent)
    {
        case DRV_USART_BUFFER_EVENT_COMPLETE:
            serial_rcvData.transferStatus = true;
            break;

        case DRV_USART_BUFFER_EVENT_ERROR:
            serial_rcvData.state = SERIAL_RCV_STATE_ERROR;
            break;

        default:
            break;
    }
}
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SERIAL_RCV_Initialize ( void )

  Remarks:
    See prototype in serial_rcv.h.
 */

void SERIAL_RCV_Initialize(void) {
    /* Place the App state machine in its initial state. */
    serial_rcvData.state = SERIAL_RCV_STATE_INIT;


    /* Place the App state machine in its initial state. */
    serial_rcvData.transferStatus  = false;
    serial_rcvData.usartHandle     = DRV_HANDLE_INVALID;
    serial_rcvData.bufferHandle    = DRV_USART_BUFFER_HANDLE_INVALID;

    led_Clear();
    resetAnimation();
    myData[0] = -1;
}

/******************************************************************************
  Function:
    void SERIAL_RCV_Tasks ( void )

  Remarks:
    See prototype in serial_rcv.h.
 */

void SERIAL_RCV_Tasks(void) {

    /* Check the application's current state. */
    switch (serial_rcvData.state) {
        //初期化
        case SERIAL_RCV_STATE_INIT:
        {
            serial_rcvData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READ);
            if (serial_rcvData.usartHandle != DRV_HANDLE_INVALID)
            {
                DRV_USART_BufferEventHandlerSet(serial_rcvData.usartHandle, SERIAL_RCV_USARTBufferEventHandler, 0);
                serial_rcvData.state = SERIAL_RCV_STATE_RECEIVE_DATA;
            }
            else
            {
                serial_rcvData.state = SERIAL_RCV_STATE_ERROR;
            }

            break;
        }
        
        //受信待機
        case SERIAL_RCV_STATE_RECEIVE_DATA:

            DRV_USART_ReadBufferAdd(serial_rcvData.usartHandle, serial_rcvData.readBuffer, SERIAL_RCV_DATA_SIZE, &serial_rcvData.bufferHandle);
            if (serial_rcvData.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID)
            {
                serial_rcvData.state = SERIAL_RCV_STATE_WAIT_RECEIVE_COMPLETE;
            }
            else
            {
                serial_rcvData.state = SERIAL_RCV_STATE_ERROR;
            }
            break;

        //受信完了
        case SERIAL_RCV_STATE_WAIT_RECEIVE_COMPLETE:
            if(serial_rcvData.transferStatus == true)
            {
                serial_rcvData.transferStatus = false;
  
                led_Toggle();
                serial_rcvData.state = SERIAL_RCV_STATE_RECEIVE_DATA;
                GARAPIKO_receive(serial_rcvData.readBuffer[0]);
            }
            break;


        //エラー
        case SERIAL_RCV_STATE_ERROR:
            
            led_Clear();
            serial_rcvData.state = SERIAL_RCV_STATE_RECEIVE_DATA;
            break;

        //通常
        case SERIAL_RCV_STATE_IDLE:
        default:
            led_Clear();
            serial_rcvData.state = SERIAL_RCV_STATE_RECEIVE_DATA;
            break;
    }
}

void GARAPIKO_receive(uint8_t RcvData) {
    if (RcvData == 255) {
        dataPos = 0;
    } else {
        if (
                RcvData == BATSU
                || RcvData == SANKAKU
                || RcvData == MARU
                || RcvData == SHIKAKU

                || RcvData == UP
                || RcvData == DOWN
                || RcvData == LEFT
                || RcvData == RIGHT

                || RcvData == STK_L_LEFT
                || RcvData == STK_L_RIGHT
                || RcvData == STK_L_UP
                || RcvData == STK_L_DOWN

                || RcvData == STK_R_LEFT
                || RcvData == STK_R_RIGHT
                || RcvData == STK_R_UP
                || RcvData == STK_R_DOWN


                || RcvData == 'a' //L1
                || RcvData == 'b' //R1
                || RcvData == 'c' //L2
                || RcvData == 'd' //R2

                ) {

            if (lastData != RcvData) {
                myData[dataPos] = RcvData;

                if (
                        RcvData == UP
                        || RcvData == DOWN
                        || RcvData == LEFT
                        || RcvData == RIGHT
                        || RcvData == BATSU

                        || RcvData == STK_L_LEFT
                        || RcvData == STK_L_RIGHT
                        || RcvData == STK_L_UP
                        || RcvData == STK_L_DOWN

                        || RcvData == STK_R_LEFT
                        || RcvData == STK_R_RIGHT
                        || RcvData == STK_R_UP
                        || RcvData == STK_R_DOWN

                        ) {
                    frameCount = 0;
                    aCnt = 0;

                } else {
                    deletePattern();
                }
                //            } else if (
                //                    RcvData == STK_L_DOWN) {
                //                frameCount = 0;
                //                aCnt = 0;

            }
            dataPos++;

            if (dataPos >= 2)dataPos = 0;
        }
    }
    lastData = myData[0];
}

/*******************************************************************************
 End of File
 */
