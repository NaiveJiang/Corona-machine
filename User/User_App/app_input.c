#include "app.h"

appStruct_t appInput;
//测试用变量
float test_adc1[6];
float test_adc3[6];
float set_vdc;
float set_speed;
uint8_t flash_sw;
appControlStruct_t controlData;
controlState_e controlState;
void set_controlState(controlState_e setState){
	controlState = setState;
}
controlState_e get_controlState(void){
	return controlState;
}
appControlStruct_t *get_controlData(void){
	return &controlData;
}

void app_coronaWait(void);

void app_inputUpdata(void){
	driverKeyNowStateUpdate();
	dac_ch1_voltageOut(set_vdc);
	dac_ch2_voltageOut(set_speed);
	appInput.loops += INPUT_TASK_PERIOD;
}
void app_inputTask(void *Parameters){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	
	while(1){
		vTaskDelayUntil(&xLastWakeTime, INPUT_TASK_PERIOD);
		//工作状态
		switch(get_controlState()){
			case CORONA_WAIT:{
				app_coronaWait();
			}break;
			case CORONA_STATE:{
				//电晕工作阶段
			}break;
			case CORONA_STOP:{
				
			}break;
			
		}
		app_inputUpdata();
//		can_Send(USE_CANx,&can_id20A);
//		rs485_send_data(RS_485,sendata,RS485_TEST_LEN);
	}
}

void app_inputTaskInit(void){
	xTaskCreate(app_inputTask,"INPUT",INPUT_STACK_SIZE,NULL,INPUT_PRIORITY,&appInput.xHandleTask);
}

void app_coronaWait(void){
	switch(get_controlData()->control_step){
		case 0:{
			//确认是否开启电晕或者是否开启风机
			if(get_mainData(get_maindata()->main_rev_data,CORONA) || get_mainData(get_maindata()->main_rev_data,FAN))
				digitalIncreasing(&get_controlData()->control_step);
		}break;
		case 1:{
			//打开风机
			pulse_output(&O2CJ3,100);
			digitalHi(&get_controlData()->wait_sw);
			//等待5s后关闭负压屏蔽
			if(get_controlData()->wait_time >= 500){
				digitalLo(&get_controlData()->wait_sw);
				//关闭负压屏蔽
				PBLE3 = 0; //打开报警
				digitalIncreasing(&get_controlData()->control_step);
			}
		}break;
		case 2:{
			//等待是否有电晕开关开启
			if(get_mainData(get_maindata()->main_rev_data,CORONA))
				get_controlData()->control_step = 99;
		}break;
		case 99:{
			//进入电晕
			set_controlState(CORONA_STATE);
			digitalClan(&get_controlData()->control_step);
		}break;
	}
}

//启动电晕状态
void app_corona_state(void){
	switch(get_controlData()->control_step){
		case 0:{
			//只有这些错误解决了，才能进入继电器闭合
			
		}break;
		case 1:{
			//等待VDC检测到达80%,继电器闭合
			
		}break;
		case 2:{
			//检测继电器闭合后,使能3875输出
			
		}break;
		case 3:{
			//放电
			
		}break;
	}
}

