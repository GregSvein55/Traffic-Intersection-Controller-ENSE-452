#include "Lights.h"
char save_state = 'x';


/**
 Sets the different output states for the LEDs
 then sets the state to the next state

 Also handles Pedestrian/ERV inputs, and sets the intersection
 to the correct state
 */
char lightSet(char state)
{
	if (state == 'a'){//Red both ways
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'b';
	}
	else if(state == 'b'){//Primary Turning light On
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_SET);
		state = 'c';

	}

	else if(state == 'c'){//Primary Green and Walk On
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'd';
	}

	else if(state == 'd'){//Primary Green On, Walk turns off
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'e';
	}

	else if(state == 'e'){//Primary Yellow
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'f';
	}

	else if(state == 'f'){//All Red again
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'g';
	}

	else if(state == 'g'){//Secondary Green and Walk On
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'h';
	}

	else if(state == 'h'){//Secondary Green On, Walk turns off
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'i';
	}

	else if(state == 'i'){//Secondary Yellow
		save_state = state;
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'a';
	}

	else if(state == 'm'){//Primary Pedestrian input
		if (save_state == 'a' || save_state == 'b' || save_state == 'c' || save_state == 'd' || save_state == 'e' || save_state == 'f'){
			//straight to pri green and walk
			state = 'c';
		}
		else{//yellow secondary, then onto primary
			state = 'i';
		}
	}

	else if(state == 'n'){//Secondary Pedestrian input
		if (save_state == 'a' || save_state == 'f' || save_state == 'g' || save_state == 'h' || save_state == 'i'){
			//straight to sec green and walk
			state = 'h';
		}
		else{//yellow primary, then onto secondary

			state = 'e';
		}
	}

	else if(state == 'o'){//Primary ERV input
		if (save_state == 'a' || save_state == 'b' || save_state == 'c' || save_state == 'd' || save_state == 'e' || save_state == 'f'){
			//straight to pri green and walk
			state = 'c';
		}
		else{//yellow secondary, then onto primary
			state = 'i';
		}
	}

	else if(state == 'p'){//Secondary ERV input
		if (save_state == 'a' || save_state == 'f' || save_state == 'g' || save_state == 'h' || save_state == 'i'){
			//straight to sec green and walk
			state = 'h';
		}
		else{//yellow primary, then onto secondary

			state = 'e';
		}
	}

	else if(state == 'x'){//Four Way Red
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'y';
	}

	else if(state == 'y'){//Used to flash red for failsafe mode
		HAL_GPIO_TogglePin(GPIOA, R1_Pin);
		HAL_GPIO_TogglePin(GPIOA, R2_Pin);
	}

	else if(state == 'z'){//IIT mode
		HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, W2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, T1_Pin, GPIO_PIN_RESET);
		state = 'x';
	}
	else{
		//Failsafe mode is default, if this were an actual intersection, this would be necessary for safety purposes
		state = 'x';
	}

	return state;
}


/**
 This function sets the amount of time each light state will be active
 Can also accelerate the light by a factor of 1x - 100x
 */
int periodSet(char state, int acceleration)
{
	int period;

	if (state == 'a'){//4 way red
		period = 2000;
	}

	else if (state == 'b'){//primary turning
		period = 20500;
	}

	else if (state == 'c'){//primary green + walk
		period = 40500;
	}

	else if (state == 'd'){//primary Green
		period = 6000;
	}

	else if (state == 'e'){//primary yellow
		period = 3500;
	}

	else if (state == 'f'){//4 way red
		period = 2000;
	}

	else if (state == 'g'){//secondary green + walk
		period = 28500;
	}

	else if (state == 'h'){//secondary green
		period = 6000;
	}

	else if (state == 'i'){//secondary yellow
		period = 3500;
	}

	else if (state == 'm'){
		period = 100;
	}

	else if (state == 'n'){
		period = 100;
	}

	else if (state == 'o'){
		period = 100;
	}

	else if (state == 'p'){
		period = 100;
	}

	else if (state == 'x'){//time on fsm
		period = 1500;
	}

	else if (state == 'y'){//time off fsm
		period = 500;
	}

	else if (state == 'z'){//IIT mode time
		period = 3000;

	}


	return period / acceleration;//adding acceleration for atm
}

