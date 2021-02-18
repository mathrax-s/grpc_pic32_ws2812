/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

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

#include "app.h"
#include "./user.h"
#include "./ledmatrix_ws2812.h"
#include "./vsc3_keyname.h"

//#include "./animation_data/pattern.h"       //HEART_REV, BREAK_HEART
//#include "./animation_data/broken.h"        //BROKEN
//#include "./animation_data/startup.h"       //STARTUP
//#include "./animation_data/hanabi.h"        //HANABI
//#include "./animation_data/sleep_heart.h"   //SLEEP HEART
//#include "./animation_data/normal_blink.h"  //NORMAL_BLINK
//#include "./animation_data/star.h"          //STAR
//
//#include "./animation_data/wave.h"          //WAVE
//#include "./animation_data/energy.h"        //ENERGY
//#include "./animation_data/onpu_blue.h"     //ONPU_BLUE
//#include "./animation_data/onpu_pink.h"     //ONPU_PINK
//#include "./animation_data/shinobi.h"       //SHINOBI
//#include "./animation_data/mini_heart.h"    //MINI HEART
//#include "./animation_data/baloon.h"        //BALOON
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
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

static const char messageBuffer[] =
        "*** GARAPICO Application ***\r\n";

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */
static void APP_USARTBufferEventHandler(
        DRV_USART_BUFFER_EVENT bufferEvent,
        DRV_USART_BUFFER_HANDLE bufferHandle,
        uintptr_t context
        ) {
    switch (bufferEvent) {
        case DRV_USART_BUFFER_EVENT_COMPLETE:
            appData.transferStatus = true;
            break;

        case DRV_USART_BUFFER_EVENT_ERROR:
            appData.state = APP_STATE_ERROR;
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
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    appData.transferStatus = false;
    appData.usartHandle = DRV_HANDLE_INVALID;
    appData.bufferHandle = DRV_USART_BUFFER_HANDLE_INVALID;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void) {

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            appData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);
            if (appData.usartHandle != DRV_HANDLE_INVALID) {
                DRV_USART_BufferEventHandlerSet(appData.usartHandle, APP_USARTBufferEventHandler, 0);
                appData.state = APP_STATE_TRANSMIT_MESSAGE;
            } else {
                appData.state = APP_STATE_ERROR;
            }

            resetAnimation();
            myData[0] = -1;
            break;
        }

            /* TODO: implement your application state machine.*/
        case APP_STATE_TRANSMIT_MESSAGE:
        {
            DRV_USART_WriteBufferAdd(appData.usartHandle, (void*) messageBuffer, strlen(messageBuffer), &appData.bufferHandle);
            if (appData.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID) {
                appData.state = APP_STATE_WAIT_MESSAGE_TRANSFER_COMPLETE;
            } else {
                appData.state = APP_STATE_ERROR;
            }
            break;
        }

        case APP_STATE_WAIT_MESSAGE_TRANSFER_COMPLETE:
            if (appData.transferStatus == true) {
                appData.transferStatus = false;
                appData.state = APP_STATE_RECEIVE_DATA;
            }
            break;

        case APP_STATE_RECEIVE_DATA:

            DRV_USART_ReadBufferAdd(appData.usartHandle, appData.readBuffer, APP_DATA_SIZE, &appData.bufferHandle);
            if (appData.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID) {
                appData.state = APP_STATE_WAIT_RECEIVE_COMPLETE;
            } else {
                appData.state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WAIT_RECEIVE_COMPLETE:

            if (appData.transferStatus == true) {
                appData.transferStatus = false;
                appData.state = APP_STATE_GARAPIKO_RECEIVE;
            }
            break;

        case APP_STATE_GARAPIKO_RECEIVE:
            led_Toggle();
            GARAPIKO_receive(appData.readBuffer[0]);
            appData.state = APP_STATE_RECEIVE_DATA;

            break;


            //        case APP_STATE_TRANSMIT_DATA:
            //            
            //            /* Echo the received data back on the terminal */
            //            DRV_USART_WriteBufferAdd(appData.usartHandle, appData.readBuffer, APP_DATA_SIZE, &appData.bufferHandle);
            //            if (appData.bufferHandle != DRV_USART_BUFFER_HANDLE_INVALID) {
            //                appData.state = APP_STATE_WAIT_TRANSMIT_COMPLETE;
            //            } else {
            //                appData.state = APP_STATE_ERROR;
            //            }
            //            break;

            //        case APP_STATE_WAIT_TRANSMIT_COMPLETE:
            //
            //            if (appData.transferStatus == true) {
            //                appData.transferStatus = false;
            //
            //                led_Toggle();
            //
            //                appData.state = APP_STATE_RECEIVE_DATA;
            //            }
            //            break;

        case APP_STATE_ERROR:

            led_Clear();
            appData.state = APP_STATE_IDLE;
            break;

        case APP_STATE_IDLE:
            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */


            break;
        }
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

//void GARAPIKO_pattern(void) {
//    frameCount++;
//    switch (myData[0]) {
//
//        default:
//            setPattern(break_heart, 2);
//            break;
//
//
//        case 0:
//            deletePattern();
//            break;
//
//
//        case UP:
//            //START UP
//            gp.picture = startup;
//            gp.frame = frame_startup;
//            gp.framesize = ARRAY_SIZE(frame_startup);
//            
//            g_animation(gp, 4, LOOP);
//            break;
//
//
//
//        case DOWN:
//            //HANABI
//            gp.picture = hanabi;
//            gp.frame = frame_hanabi;
//            gp.framesize = ARRAY_SIZE(frame_hanabi);
//            
//            g_animation(gp, 3, ONCE);
//            break;
//
//
//
//        case LEFT:
//            //NORMAL BLINK
//            gp.picture = normal_blink;
//            gp.frame = frame_normal_blink;
//            gp.framesize = ARRAY_SIZE(frame_normal_blink);
//            
//            g_animation(gp, 16, LOOP);
//            break;
//
//        case RIGHT:
//            //BROKEN BLINK
//            gp.picture = broken;
//            gp.frame = frame_broken;
//            gp.framesize = ARRAY_SIZE(frame_broken);
//            
//            g_animation(gp, 3, LOOP);
//            break;
//
//        case BATSU:
//            //DELETE
//            myData[0] = 0;
//            deletePattern();
//            break;
//
//
//        case SANKAKU:
//            //BATSU
//            setPattern(batsu, 2);
//            break;
//
//
//        case MARU:
//            //HATENA?
//            setPattern(hatena, 2);
//            break;
//
//
//        case SHIKAKU:
//            //BREAK HEART
//            setPattern(break_heart, 2);
//            break;
//
//
//
//
//
//        case STK_L_LEFT:
//            //STAR
//            gp.picture = star;
//            gp.frame = frame_star;
//            gp.framesize = ARRAY_SIZE(frame_star);
//            
//            g_animation(gp, 3, LOOP);
//            break;
//
//
//        case STK_L_RIGHT:
//            //SHINOBI
//            setPattern(shinobi[0], 2);
//
//            break;
//
//
//        case STK_L_UP:
//            //WAVE
//            gp.picture = wave;
//            gp.frame = frame_wave;
//            gp.framesize = ARRAY_SIZE(frame_wave);
//            
//            g_animation(gp, 3, LOOP);
//
//            break;
//
//
//        case STK_L_DOWN:
//            //ONPU_PINK ANIME
//            gp.picture = onpu_pink_anime;
//            gp.frame = frame_onpu_pink_anime;
//            gp.framesize = ARRAY_SIZE(frame_onpu_pink_anime);
//            
//            g_animation(gp, 12, ONCE);
//            break;
//
//
//        case STK_R_LEFT:
//            //MINI HEART1
//            setPattern(mini_heart1[0], 2);
//            break;
//
//        case STK_R_RIGHT:
//            //MINI_HEART2
//            setPattern(mini_heart2[0], 2);
//            break;
//
//        case STK_R_UP:
//            //BALOON
//            setPattern(baloon[0], 2);
//            break;
//
//        case STK_R_DOWN:
//            //ONPU BLUE ANIME
//            gp.picture = onpu_blue_anime;
//            gp.frame = frame_onpu_blue_anime;
//            gp.framesize = ARRAY_SIZE(frame_onpu_blue_anime);
//            
//            g_animation(gp, 12, ONCE);
//            break;
//    }
//
//    show();
//}
//
//void g_animation(GARAPICO g, uint8_t speed, uint8_t loop) {
//    //    ENERGY
//    if (frameCount % speed == 0) {
//        frameCount = 0;
//        aCnt++;
//        if (aCnt >= g.framesize) {
//            if (loop == ONCE) {
//                aCnt = g.framesize - 1;
//            } else if (loop == LOOP) {
//                aCnt = 0;
//            }
//        }
//    }
//    setPattern(g.picture[g.frame[aCnt]], 2);
//}

/*******************************************************************************
 End of File
 */
