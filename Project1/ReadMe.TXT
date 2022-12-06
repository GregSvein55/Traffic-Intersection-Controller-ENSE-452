DEMO VIDEO - https://youtu.be/PFta1p5ewJ8

Final Project - Greg Sveinbjornson
My Files: main.c, Lights.c, Lights.h


Description

This project is a intersection controller, running on the STM32F103RB microcontroller using
FreeRTOS. The microcontroller is connected to a sample intersection using a breadboard and small 
LEDs. The link to my demo video is here https://youtu.be/PFta1p5ewJ8, I'm not sure if we have to demo in class 
so I just took this video quickly. 

When booted, a welcome message is printed out on the command line and stays on the screen for a 
few seconds. Afterwards the CLI boots up and creates a scrollable window. The current mode is displayed
in the top left corner. The CLI will prompt the user for a case-sensitive command, if a command is entered wrong, the
user is told that there is an error and will have the message repeated back so they can see their mistake.
Blank lines simply make a new prompt with no error message. 



Modes

1. Failsafe mode (FSM): 4-way flashing red, at 0.5Hz with a 75% duty cycle

2. Static Cycle mode (SCM): Regular traffic light cycle with fixed cycle times.

3. Low Volume mode (LVM): Same as SCM but it runs at twice the speed because of the low traffic

4. Fixed Cycle mode (FCM): Same as SCM, but can now handle pedestrian and ERV events

5. Intersection Initialization mode (IIM): only runs for the first 3 seconds to initialize 
					   controller, 4-way solid red.


Commands

1. help - displays a list of commands

2. mode fsm - switches controller to Failsafe mode

3. mode scm - switches controller to Static Cycle mode

4. "atm x" - puts microcontroller into accelerated test mode with multiplication 
	     factor between 1 and 100 (x)

5. clear - clears the screen

6. mode lvm - switches controller to Low Volume mode

7. mode fcm - switches controller to Fixed Cycle mode

Event Commands - can only work when controller is in Fixed Cycle Mode

8. event pp - Primary Pedestrian Event, switches to primary green faster

9. event sp - Secondary Pedestrian Event, switches to secondary green faster

10. event pev - Primary Emergency Vehicle Event, switches to primary green faster

11. event sev - Secondary Emergency Vehicle Event, switches to secondary green faster


Things of note:
I decided to just leave my walk light solid for the whole time. Most new walk lights in the real world
use a countdown now instead of a flashing light, so I decided to leave it as such.
In my video the turning and green lights are hard to differentiate, the turning lights are the ones 
furthest away from the red lights.
The primary walk lights are only behing the primary set of lights because I ran out of room on 
my breadboard.
The mode cannont switch until a state switch happens on the lights, not a huge issue, just have to
wait a few seconds.

