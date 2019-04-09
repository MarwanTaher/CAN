/*
 * FSM.h
 *
 *  Created on: Apr 4, 2019
 *      Author: AVE-LAP-005
 */

#ifndef FSM_H_
#define FSM_H_
typedef enum{
    N_one=0,
    N_two,
    N_three,
    N_FOUR

}Node_Id;
#define NUM_OF_NODES 4
extern void FSM_Task();
extern void Button_Task(void);
extern void Led_Task();

#endif /* FSM_H_ */
