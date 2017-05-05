#ifndef KEY_STACK_H
#define KEY_STACK_H
/*
//---------------------------------------------------------
// GLOBAL VARIABLES
//---------------------------------------------------------

char key_stack[7]; ///< Track the ORDER of the keys pressed.

char top_stack_key; ///< The key on top of the stack
char last_key_states; ///< EACH BIT --> Key state. Track the key states for previous calls to the 'update_key_stack' methods.

//---------------------------------------------------------
// Key stack methods && key state methods
//---------------------------------------------------------

void key_stack_purge();
void key_stack_push(const char key);
char key_stack_top();
char key_stack_empty();
char key_stack_find(const char key);
void key_stack_remove(const char key);

bit update_key_stack_add();
bit update_key_stack_remove();

//---------------------------------------------------------
// key_stack.h methods
//---------------------------------------------------------



// @name: key_stack_purge
// @brief: Set every element in the stack to NOT_KEY
void key_stack_purge()
{
	char i;
	for(i=0 ; i<NUM_KEYS ; ++i)
	{
		key_stack[i] = NUM_KEYS;
	}
}



// @name: key_stack_push
// @brief: Shift the contents of the stack up an index. Insert a new element
//			at index 0.
void key_stack_push(const char key)
{
	char i;
	for(i=NUM_KEYS-1 ; i>=1 ; --i)
	{
		key_stack[i] = key_stack[i-1];
	}
	key_stack[0] = key;	
}



// @name: key_stack_top
// @brief: Return the key on the top of the stack.
char key_stack_top()
{
	return key_stack[0];
}



// @name: key_stack_empty
// @brief: Return 1 if the stack is empty. Else false.
char key_stack_empty()
{
	if(key_stack_top() == NOT_KEY)
	{
		return 0;
	}
	else
	{
	 	return 1;
	}
}



// @name: key_stack_find
// @brief: Find the index of the key in the stack. Internal use only.
char key_stack_find(const char key)
{
	char i;
	for(i=0 ; i < NUM_KEYS ; ++i)
	{
	 	if(key == key_stack[i])
		{
		    return i;
		}
	}
	return NOT_KEY;
}



// @name: key_stack_remove
// @brief: Remove a key from the stack. Shift every other element after the
//			one removed towards the top of the stack.
void key_stack_remove(const char key)
{
	char i, index = key_stack_find(key);
	if(index != NOT_KEY)
	{
		for(i=index ; i < NUM_KEYS-1 ; ++i)
		{
			key_stack[i] = key_stack[i+1];
		}
		key_stack[NUM_KEYS-1] = NOT_KEY;
	}
}



// @name: update_key_stack_add
// @brief: Check all the keys. If any were just pressed, add them to the stack.
//			Return TRUE if a key was added. Else false.
bit update_key_stack_add()
{
	bit just_pressed, current_state, last_state;
	char i;
	char bit_mask = 1; // Start at first bit.
	char num_keys = (sf_bool) ? NUM_SF_KEYS : NUM_KEYS;
	
	for(i=0 ; i<num_keys ; ++i)
	{
		current_state = get_key_state(i);
		last_state = (last_key_states & bit_mask) ? 1 : 0;
		just_pressed = btn_just_pressed(current_state, last_state); // Check

		// Update state if changed.
		if(current_state != last_state)
		{
			if(last_state) // If 0 now and previously 1
			{
				last_key_states-=bit_mask; // 1 --> 0
			}
			else
			{
				last_key_states+=bit_mask; // 0 --> 1
			}
		}

		// Add the key to the stack.
		if(just_pressed)
		{
			key_stack_push(i);
			return 1;
		}
		bit_mask*=2; // Check next bit next iteration.
	}
	return 0;
}



// @name: key_just_pressed
// @brief: Check all the keys. If any were just released, remove them from the
//			stack. Return TRUE if a key was removed. Else false.
bit update_key_stack_remove()
{
	bit just_released, current_state, last_state;
	char i;
	char bit_mask = 1; // Start at first bit.
	char num_keys = (sf_bool) ? NUM_SF_KEYS : NUM_KEYS;
	
	for(i=0 ; i<num_keys ; ++i)
	{
		current_state = get_key_state(i);
		last_state = (last_key_states & bit_mask) ? 1 : 0;
		just_released = btn_just_released(current_state, last_state); // Check

		// Update state if changed.
		if(current_state != last_state)
		{
			if(last_state) // If 0 now and previously 1
			{
				last_key_states-=bit_mask; // 1 --> 0
			}
			else
			{
				last_key_states+=bit_mask; // 0 --> 1
			}
		}

		// Add the key to the stack.
		if(just_released)
		{
			key_stack_remove(i);
			return 1;
		}
		bit_mask*=2; // Check next bit next iteration.
	}
	return 0;
}
*/
#endif