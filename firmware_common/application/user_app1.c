/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  /* Backlight to white */  
  LedOn(LCD_RED);
  LedOn(LCD_GREEN);
  LedOn(LCD_BLUE);
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u8 u8ColorIndex = 0;
  static u16 u16CounterFinale = 0;
  static u16 u16Counter = 0;
  static u16 u16Finale = 0;
  static LedRateType eRateW=LED_PWM_0;
  static LedRateType eRateP=LED_PWM_100;
  static LedRateType eRateB=LED_PWM_0;
  static LedRateType eRateC=LED_PWM_100;
  static LedRateType eRateG=LED_PWM_0;
  static LedRateType eRateY=LED_PWM_100;
  static LedRateType eRateO=LED_PWM_0;
  static LedRateType eRateR=LED_PWM_100;
  static bool bflip=FALSE;
  u16Counter++;
  u16Finale++;

  /* 1 
  First if statement of the main color loop.
  causes the white LED to start from LED_PWM_0 and increment up
  to LED_PWM_100. Alternates this order back for each
  subsequent LED from a starting point of LED_PWM_0 to LED_PWM_100.
  */
  if(u16Counter == MAIN_TIMER_LIMIT && bflip == FALSE && u16Finale < FINALE_TIMER_LIMIT)
    {
    u16Counter=0;
    eRateW++;
    eRateP--;
    eRateB++;
    eRateC--;
    eRateG++;
    eRateY--;
    eRateO++;
    eRateR--;
    if(eRateW <= LED_PWM_100)
      {
      LedPWM(WHITE,eRateW);
      LedPWM(PURPLE,eRateP);
      LedPWM(BLUE,eRateB);
      LedPWM(CYAN,eRateC);
      LedPWM(GREEN,eRateG);
      LedPWM(YELLOW,eRateY);
      LedPWM(ORANGE,eRateO);
      LedPWM(RED,eRateR);
      }
    }
  /* 2
  does the exact opposite of 1.
  */
  if(u16Counter == MAIN_TIMER_LIMIT && bflip == TRUE && u16Finale < FINALE_TIMER_LIMIT)
    {
    u16Counter=0;
    eRateW--;
    eRateP++;
    eRateB--;
    eRateC++;
    eRateG--;
    eRateY++;
    eRateO--;
    eRateR++;
    if(eRateW >= LED_PWM_0)
      {
      LedPWM(WHITE,eRateW);
      LedPWM(PURPLE,eRateP);
      LedPWM(BLUE,eRateB);
      LedPWM(CYAN,eRateC);
      LedPWM(GREEN,eRateG);
      LedPWM(YELLOW,eRateY);
      LedPWM(ORANGE,eRateO);
      LedPWM(RED,eRateR);
      }
    }
      if(eRateW == LED_PWM_0)
      {
        bflip=FALSE;
      }
      if(eRateW == LED_PWM_100)
      {
        bflip=TRUE;
      }
     /* 3
      begins the Finale Loop. Counter for Finale has been
  incrementing since the start of the program. Once it hits the
  specified value, the main color loop terminates and 
  */
  if(u16Finale>=FINALE_TIMER_LIMIT)
  {
    u16CounterFinale++;
    
    if(u16CounterFinale == 10)
    {
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
    }
    
    if(u16CounterFinale == 300)
    {
      LedToggle(RED);
      LedToggle(WHITE);
    }
    
    if(u16CounterFinale == 600)
    {
      LedToggle(ORANGE);
      LedToggle(PURPLE);
    }
    
    if(u16CounterFinale == 900)
    {
      LedToggle(YELLOW);
      LedToggle(BLUE);
    }
    
    if(u16CounterFinale == 1200)
    {
      LedToggle(CYAN);
      LedToggle(GREEN);
    }
    
    if(u16CounterFinale == 1500)
    {
      LedToggle(WHITE);
    }
    
    if(u16CounterFinale == 1600)
    {
      LedToggle(PURPLE);
    }
    
    if(u16CounterFinale == 1700)
    {
      LedToggle(BLUE);
    }
    
    if(u16CounterFinale == 1800)
    {
      LedToggle(CYAN);
    }
    
    if(u16CounterFinale == 1900)
    {
      LedToggle(GREEN);
    }
    
    if(u16CounterFinale == 2000)
    {
      LedToggle(YELLOW);
    }
    
    if(u16CounterFinale == 2100)
    {
      LedToggle(ORANGE);
    }
    
    if(u16CounterFinale == 2200)
    {
      LedToggle(RED);
    }
    
    if(u16CounterFinale > 2300)
    {
     u8ColorIndex++;
     if(u8ColorIndex == 7)
     {
       u8ColorIndex = 0;
     }
     switch(u8ColorIndex)
      {
        case 0: /* white */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;

        case 1: /* purple */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 2: /* blue */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 3: /* cyan */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 4: /* green */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 5: /* yellow */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 6: /* red */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        default: /* off */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
      }
    u16CounterFinale = 0;
    u16Finale = 0;
    u16Counter=0;
    }
    
  }
 
  

       
  
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
