#include "app.h"


appStruct_t appSupervisior;
appSupStruct_t supervisiorData;

appSupStruct_t *get_supervisiorData(void){
	return &supervisiorData;
}

//互锁开关
void app_sup_LE(void){
	uint8_t le_error;
	if(!LE3) get_controlData()->error_sta &= 0xFFFFFF87;	//LE3为1时有效
	else{
		le_error |= (uint8_t)LE0;
		le_error |= (uint8_t)(LE1 << 1);
		le_error |= (uint8_t)(LE2 << 2);
		get_controlData()->error_sta &= 0xFFFFFF87;
		get_controlData()->error_sta |= (le_error + 1) << 3;
	}
}

//状态机监控
void app_supervisiorTask(void *Parameters){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1){
		vTaskDelayUntil(&xLastWakeTime, SUPER_TASK_PERIOD);
		
		//打开PBLE3时检测互锁开关状态
		if(PBLE3) app_sup_LE();							//互锁开关
		error_set(&QSALARM,QSALARM_ERROR);				//缺项检测
		error_set(&DCVCHK,DCVCHK_ERROR);				//低压电源检测
		error_set(&JTJC,EMERGENCY_STOP);				//急停报警
		error_set(&IN_ALARM,SYSTEM_ERROR);				//系统报警
		error_set(&PVDD,POWER_DOWN_ERROR);				//低压电源检测
		error_set(&DHAL,HIGH_VOLTAGE_SPARK_ERROR);		//高压打火报警		
		error_set(&HIAL,HIGH_VOLTAGE_OVERCURRENT);		//高压放电过流
		error_set(&IGBTBAL,IGBTB_OVERCURRENT);			//IGBTB过流
		error_set(&IGBTAAL,IGBTA_OVERCURRENT);			//IGBTA过流
		error_set(&TIAL,PRIMARY_OVERCURRENT);			//原边电流过流
		
		//写入flash
		if(get_supervisiorData()->flash_sw){
			app_FlashWriteUdata();
			digitalLo(&get_supervisiorData()->flash_sw);
		}
		IWDG_Feed(); //喂狗
	}
}	


void app_supervisiorTaskInit(void){
	xTaskCreate(app_supervisiorTask,"SUPERVISIOR",SUPER_STACK_SIZE,NULL,SUPER_PRIORITY,&appSupervisior.xHandleTask);
}



