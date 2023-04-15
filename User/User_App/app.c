#include "app.h"
#include "GUI.h"

//outfireRobotState_t outfireRobotState;
//rescueRobotState_t rescueRobotState;
uint32_t parameter[NAME_OF_LIST];
appStruct_t app;
uint8_t version;
void app_ParameterInit(void)
{
	
	{
//		parameter[NAME_VERSION] = VERSION;
//		//转弯时间控制角度
//		parameter[NAME_FRONT_TURN_LEFT_TIME_90] = FRONT_TURN_LEFT_TIME_90;
//		
//		parameter[NAME_FRONT_TURN_LEFT_TIME_180] = FRONT_TURN_LEFT_TIME_180;
//		
//		parameter[NAME_FRONT_TURN_RIGHT_TIME_90] = FRONT_TURN_RIGHT_TIME_90;
//		
//		parameter[NAME_FRONT_TURN_RIGHT_TIME_180] = FRONT_TURN_RIGHT_TIME_180;
//		
//		parameter[NAME_FRONT_TURN_LEFT_TIME_135] = FRONT_TURN_LEFT_TIME_135;
//		
//		parameter[NAME_FRONT_TURN_LEFT_TIME_45] = FRONT_TURN_LEFT_TIME_45;
//		
//		parameter[NAME_FRONT_TURN_RIGHT_TIME_135] = FRONT_TURN_RIGHT_TIME_135;
//		
//		parameter[NAME_FRONT_TURN_RIGHT_TIME_45] = FRONT_TURN_RIGHT_TIME_45;
//		
//		parameter[NAME_BEHIND_TURN_LEFT_TIME_45] = BEHIND_TURN_LEFT_TIME_45;
//		
//		parameter[NAME_BEHIND_TURN_RIGHT_TIME_45] = BEHIND_TURN_RIGHT_TIME_45;
//		
//		parameter[NAME_REVERSE_TURN_TIME_45] = REVERSE_TURN_LEFT_TIME_45;
//		
//		parameter[NAME_REVERSE_TURN_TIME_90] = REVERSE_TURN_LEFT_TIME_90;
//		
//		parameter[NAME_REVERSE_TURN_TIME_135] = REVERSE_TURN_LEFT_TIME_135;
//		
//		parameter[NAME_REVERSE_TURN_TIME_180] = REVERSE_TURN_LEFT_TIME_180;
//		
//		parameter[NAME_GO_STRAIGHT_TIME] = GO_STRAIGHT_TIME;
//		
//		parameter[NAME_SET_ZERO_TIME] = SET_ZERO_TIME;
//		//转弯的轮子转速
//		parameter[NAME_TURN_LEFT__LEFT_RATE] = TURN_LEFT__LEFT_RATE;
//		parameter[NAME_TURN_LEFT__RIGHT_RATE] = TURN_LEFT__RIGHT_RATE;
//		
//		parameter[NAME_TURN_RIGHT__LEFT_RATE] = TURN_RIGHT__LEFT_RATE;
//		parameter[NAME_TURN_RIGHT__RIGHT_RATE] = TURN_RIGHT__RIGHT_RATE;
////		
//		parameter[NAME_REVERSE_LEFT_TURN__LEFT_RATE] = REVERSE_LEFT_TURN__LEFT_RATE;
//		parameter[NAME_REVERSE_LEFT_TURN__RIGHT_RATE] = REVERSE_LEFT_TURN__RIGHT_RATE;
//		
//		parameter[NAME_REVERSE_RIGHT_TURN__LEFT_RATE] = REVERSE_RIGHT_TURN__LEFT_RATE;
//		parameter[NAME_REVERSE_RIGHT_TURN__RIGHT_RATE] = REVERSE_RIGHT_TURN__RIGHT_RATE;
////		
//		parameter[NAME_GO_STRAIGHT__LEFT_RATE] = GO_STRAIGHT__LEFT_RATE;
//		parameter[NAME_GO_STRAIGHT__RIGHT_RATE] = GO_STRAIGHT__RIGHT_RATE;
//		
//		parameter[NAME_SET_ZERO__LEFT_RATE] = SET_ZERO__LEFT_RATE;
//		parameter[NAME_SET_ZERO__RIGHT_RATE] = SET_ZERO__RIGHT_RATE;
//		
	}
	
	bsp_ReadCpuFlash(FLASH_SAVE_START_ADDR + NAME_VERSION,(uint8_t *)&version, 2);
	
	if(version == 0xFF){
		app_FlashWriteUdata();
	}
	else{
		app_FlashReadUdata();
	}
}



