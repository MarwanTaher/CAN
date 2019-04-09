

#ifndef MY_TASK_H_
#define MY_TASK_H_

extern QueueHandle_t Quee;
 void vTaskCode( void * pvParameters );/*init task */
 void vTaskCode2( void * pvParameters );
 void vTaskCode3( void * pvParameters );/*buttun  2 task */
 void vTaskCode6( void * pvParameters );/*buttun  1 task */
 void vTaskCode4( void * pvParameters );
 void vTaskCode5( void * pvParameters );
#define ZERO 0
#define ONE 1
#define TWO 2

#endif /* MY_TASK_H_ */
