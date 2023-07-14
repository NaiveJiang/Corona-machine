#include "app.h"
#include "GUI.h"

uint32_t parameter[NAME_OF_LIST];
appStruct_t app;
uint8_t version;
//默认参数初始化
void app_ParameterInit(void){
	
	{
		parameter[NAME_VERSION] = VERSION;
		
		parameter[POWER] = DEAFULT_POWER;
		
		parameter[CONTROL_MODE] = DEAFULT_CONTROL_MODE;
		
		parameter[POWER_MODE] = DEAFULT_POWER_MODE;
		
		parameter[SPD_SIGNAL] = DEAFULT_SPD_SIGNAL;
		
		parameter[POWER_DENSITY] = DEAFULT_POWER_DENSITY;
		
		parameter[SPD_MAX] = DEAFULT_SPD_MAX;
		
		parameter[SPD_MIN] = DEAFULT_SPD_MIN;
		
		parameter[MANUAL_POWER] = DEAFULT_MANUAL_POWER;
		
		parameter[MAX_SPEED] = DEAFULT_MAX_SPEED;
		
		parameter[LOW_POWER] = DEAFULT_LOW_POWER;
		
		parameter[SET_SPD_DELAY] = DEAFULT_SET_SPD_DELAY_TIME;
		
		parameter[SET_PULSE_DELAY] = DEAFULT_SET_PULSE_DELAY_TIME;
		
		parameter[SET_REMAIN] = DEAFULT_SET_REMAIN_DELAY_TIME;
		
		parameter[SET_LINE_DELAY] = DEAFULT_SET_LINE_DELAY_TIME;
		
		parameter[SET_DELAY_LENGTH1] = DEAFULT_SET_DELAY_LENGTH1;
		
		parameter[SET_DELAY_LENGTH2] = DEAFULT_SET_DELAY_LENGTH2;
		
		parameter[SPD_UP] = DEAFULT_SPD_UP;
		
		parameter[ROLLER_DIAMETER_LOCAL] = DEAFULT_ROLLER_DIAMETER_LOACAL;
		
		parameter[ROLLER_DIAMETER_EXTERNAL] = DEAFULT_ROLLER_DIAMETER_EXTERNAL;
		
		parameter[ROLLER_WIDTH] = DEAFULT_ROLLER_WIDTH;
		
		parameter[ROLLER_PULSE_LOCAL] = DEAFULT_ROLLER_PULSE_LOCAL;
		
		parameter[ROLLER_PULSE_EXTERNAL] = DEAFULT_ROLLER_PULSE_EXTERNAL;
		
	}
	
	//从flash中读取版本号
	bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR + NAME_VERSION,(uint8_t *)&version, 2);
	
	//如果版本号为0xFF，即flash无内容
	if(version == 0xFF){
		app_FlashWriteUdata();
	}
	//flash中存在内容，则版本号不为0xFF，读取flash中的内容
	else{
		app_FlashReadUdata();
	}
}

void app_ControlParameterLoad(void){
	//读取flash的控制信息
	get_controlData()->rated_power = (float)parameter[POWER] * 0.01f;
	
	get_controlData()->control_mode = parameter[CONTROL_MODE];
	get_controlData()->power_mode = parameter[POWER_MODE];
	get_controlData()->speed_signal = parameter[SPD_SIGNAL];
	
	//获取控制参数
	get_controlData()->power_density = (uint16_t)parameter[POWER_DENSITY];
	get_spdDischargeData()->max_spd = (float)parameter[MAX_SPEED];
	get_spdDischargeData()->spd_max_pow = (float)parameter[SPD_MAX] * 0.01f;
	get_spdDischargeData()->spd_min_pow = (float)parameter[SPD_MIN] * 0.01f;
	get_controlData()->manual_power = (float)parameter[MANUAL_POWER] * 0.01f;
	get_controlData()->set_speed_up = (float)parameter[SPD_UP] * 0.01f;
	get_dischargeCtrlData()->low_power = (float)parameter[LOW_POWER] * 0.01f;
	
	get_spdDischargeData()->set_delay_time = parameter[SET_SPD_DELAY];
	get_pulseDischargeData()->set_delay_time = parameter[SET_PULSE_DELAY];
	get_spdDischargeData()->set_remain_time = parameter[SET_REMAIN];
	get_spdDischargeData()->set_line_delay_time = parameter[SET_LINE_DELAY];
	get_rcCtrlData()->set_delay_length1 = parameter[SET_DELAY_LENGTH1];
	get_rcCtrlData()->set_delay_length2 = parameter[SET_DELAY_LENGTH2];
	
	//得到滚筒单个脉冲所占线长 
	get_spdDischargeData()->roller_pulse_length = (float)parameter[ROLLER_DIAMETER_LOCAL] * 0.01f * PI / (float)parameter[ROLLER_PULSE_LOCAL]; //本地滚轴
	get_spdDischargeData()->external_pulase_length = (float)parameter[ROLLER_DIAMETER_EXTERNAL] * 0.01f * PI / (float)parameter[ROLLER_PULSE_EXTERNAL]; //外地滚轴
	get_dryCtrlData()->max_power = get_controlData()->rated_power * 0.5f;	//湿启动功率为额定功率的50%
	
	//得到滚筒宽度
	get_spdDischargeData()->roller_width = (float)parameter[ROLLER_WIDTH];
}



