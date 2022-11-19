CLI V2 Gregory Sveinbjornson Oct. 21, 2022

Description


This application is a Command-Line Interface (CLI) that enables users to interact with a target microcontroller board.
A welcome message is printed by the CLI when it is booted, and it appears on the screen. Up top the number of commands
is displayed in the static upper window. In a scrollable window below, the CLI then prints the prompt "Enter a command 
for the LED:". A command can then be entered by the user. If the command was improperly formatted, an error notice is
displayed. Incorrect typing can be fixed by pressing the backspace key.

This Lab added the Time tests which can be accessed by running the command "test". All tests are implemented and timed,
the times can be changed by playing with th eoptimization level of the compiler. All reseults are printed onto the screen.

Ther are 5 commands:

"on" turns the green LED on

"off" turns the green LED off

"query" prints out the state of the green LED

"help" prints all possible commands

"test" runs and prints the time tests
