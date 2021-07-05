/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    garapico_led.c

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

#include "garapico_led.h"

#include "./animation_data/pattern.h"       //HEART_REV, BREAK_HEART
#include "./animation_data/broken.h"        //BROKEN
#include "./animation_data/startup.h"       //STARTUP
#include "./animation_data/hanabi.h"        //HANABI
#include "./animation_data/sleep_heart.h"   //SLEEP HEART
#include "./animation_data/normal_blink.h"  //NORMAL_BLINK
#include "./animation_data/star.h"          //STAR

#include "./animation_data/wave.h"          //WAVE
#include "./animation_data/energy.h"        //ENERGY
#include "./animation_data/fire.h"          //FIRE
#include "./animation_data/mini_heart.h"    //MINI HEART
#include "./animation_data/clock_anime.h"   //CLOCK
#include "./animation_data/drop.h"          //DROP

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
    This structure should be initialized by the GARAPICO_LED_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

GARAPICO_LED_DATA garapico_ledData;
//GARAPICO gp;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */

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
    void GARAPICO_LED_Initialize ( void )

  Remarks:
    See prototype in garapico_led.h.
 */

void GARAPICO_LED_Initialize(void) {
    /* Place the App state machine in its initial state. */
    garapico_ledData.state = GARAPICO_LED_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void GARAPICO_LED_Tasks ( void )

  Remarks:
    See prototype in garapico_led.h.
 */

void GARAPICO_LED_Tasks(void) {
    
    GARAPICO gp = {dummy,frame_dummy,0,0};
    
    /* Check the application's current state. */
    switch (garapico_ledData.state) {
            /* Application's initial state. */
        case GARAPICO_LED_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized) {

                garapico_ledData.state = GARAPICO_LED_STATE_SERVICE_TASKS;
            }
            break;
        }

        case GARAPICO_LED_STATE_SERVICE_TASKS:
        {
            frameCount++;
            switch (myData[0]) {

                default:
                    setPattern(break_heart, 2);
                    break;


                case 0:
                    deletePattern();
                    break;


                case UP:
                    //START UP
                    gp.picture = startup;
                    gp.frame = frame_startup;
                    gp.framesize = ARRAY_SIZE(frame_startup);

                    g_animation(gp, 4, LOOP, 2);
                    break;



                case DOWN:
                    //HANABI
                    gp.picture = hanabi;
                    gp.frame = frame_hanabi;
                    gp.framesize = ARRAY_SIZE(frame_hanabi);
                    gp.reset = 1;

                    g_animation(gp, 3, ONCE, 2);
                    break;



                case LEFT:
                    //NORMAL BLINK
                    gp.picture = normal_blink;
                    gp.frame = frame_normal_blink;
                    gp.framesize = ARRAY_SIZE(frame_normal_blink);

                    g_animation(gp, 16, LOOP, 2);
                    break;

                case RIGHT:
                    //BROKEN BLINK
                    gp.picture = broken;
                    gp.frame = frame_broken;
                    gp.framesize = ARRAY_SIZE(frame_broken);

                    g_animation(gp, 3, LOOP, 2);
                    break;

                case BATSU:
                    //DELETE
                    myData[0] = 0;
                    deletePattern();
                    break;


                case SANKAKU:
                    //BATSU
                    setPattern(batsu, 2);
                    break;


                case MARU:
                    //HATENA?
                    setPattern(hatena, 2);
                    break;


                case SHIKAKU:
                    //BREAK HEART
                    setPattern(break_heart, 2);
                    break;


//JOYSTICK L
                case STK_L_LEFT:
                    //DROP CYAN
                    setPattern(drop[1], 2);
                    break;


                case STK_L_RIGHT:
                    //FIRE
                    setPattern(fire[0], 2);

                    break;


                case STK_L_UP:
                    //WAVE
                    gp.picture = wave;
                    gp.frame = frame_wave;
                    gp.framesize = ARRAY_SIZE(frame_wave);

                    g_animation(gp, 3, LOOP, 2);

                    break;


                case STK_L_DOWN:
                    //CLOCK
                    gp.picture = clock_anime;
                    gp.frame = frame_clock_anime;
                    gp.framesize = ARRAY_SIZE(frame_clock_anime);

                    g_animation(gp, 4, LOOP, 2);
                    break;

//JOYSTICK R
                case STK_R_LEFT:
                    //MINI HEART1
                    setPattern(mini_heart1[0], 2);
                    break;

                case STK_R_RIGHT:
                    //MINI_HEART2
                    setPattern(mini_heart2[0], 2);
                    break;

                case STK_R_UP:
                    //DROP
                    setPattern(drop[0], 2);
                    break;

                case STK_R_DOWN:
                    //ENERGY
                    gp.picture = energy;
                    gp.frame = frame_energy;
                    gp.framesize = ARRAY_SIZE(frame_energy);

                    g_animation(gp, 4, ONCE, 2);
                    break;
            }

            show();


            break;
        }

            /* TODO: implement your application state machine.*/


            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
