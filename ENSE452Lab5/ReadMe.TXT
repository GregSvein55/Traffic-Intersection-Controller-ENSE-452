Lab 5 
Greg Sveinbjornson
Nov. 23, 2022

Description

This application is a Command-Line Interface (CLI)
that enables users to interact with a target microcontroller 
board. A welcome message is printed by the CLI when it is booted,
and it appears on the screen. Up top the period of the LED is displayed.

In a scrollable window below, the CLI then prints the prompt
"To change the period of the LED, enter 'period x', where x is the new period".
A command can then be entered by the user.
If the command was improperly formatted, an error notice is displayed. 
Incorrect typing can be fixed by pressing the backspace key.


Commands

"period x" - this will change the period of the flashing LED to 'x',
	     'x' must be an integer value > 0. 


Errors

Sometimes the CLI doesn't update the shown period value, even thought the 
LED is flashing at the new period.
