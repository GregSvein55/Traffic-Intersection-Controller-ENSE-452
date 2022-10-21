CLI V2
Gregory Sveinbjornson
Oct. 21, 2022


Description

This application is a Command-Line Interface (CLI)
that enables users to interact with a target microcontroller 
board. A welcome message is printed by the CLI when it is booted,
and it appears on the screen for a little while.
In a scrollable window, the CLI then prints the prompt
"Enter a command for the LED:". A command can then be entered by the user.
The prompt is simply repeated when blank lines are entered, and if the 
command was improperly formatted, an error notice is displayed. 
Incorrect typing can be fixed by pressing the backspace key.

Ther are 4 commands:

1. "on" turns the green LED on

2. "off" turns the green LED off

3. "query" prints out the state of the green LED

4. "help" prints all possible commands