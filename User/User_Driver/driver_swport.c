#include "driver.h"
#include "app.h"
//IO口初始化
void driver_port_Init(void){
	
	BSP_GPIO_Init(LKEN_PORT,GPIO_Mode_Out_PP);			//允许线控使能光耦互锁
	BSP_GPIO_Init(DCVCHK_PORT,GPIO_Mode_IN_FLOATING);	//低压电源检测
	
	//错误代码LE2:LE1:LE0,LE3为1时有效
	BSP_GPIO_Init(PBLE3_PORT,GPIO_Mode_Out_PP);		//屏蔽LE3
	BSP_GPIO_Init(LE0_PORT,GPIO_Mode_IN_FLOATING);	//LE0
	BSP_GPIO_Init(LE1_PORT,GPIO_Mode_IN_FLOATING);	//LE1
	BSP_GPIO_Init(LE2_PORT,GPIO_Mode_IN_FLOATING);	//LE2
	BSP_GPIO_Init(LE3_PORT,GPIO_Mode_IN_FLOATING);	//LE3报警有效位，LE3为1时LE0~2有效
	
	BSP_GPIO_Init(OPIN1_PORT,GPIO_Mode_IN_FLOATING);//光耦输入1
	
	//脉冲信号输出
	BSP_GPIO_Init(DJOPEN_PORT,GPIO_Mode_Out_PP);	//打开电极			0.1s脉冲
	BSP_GPIO_Init(DJCLOSE_PORT,GPIO_Mode_Out_PP);	//关闭电极			0.1s脉冲
	BSP_GPIO_Init(O2CJ3_PORT,GPIO_Mode_Out_PP);		//启动臭氧风机 		0.1s脉冲
	BSP_GPIO_Init(STOPCJ3_PORT,GPIO_Mode_Out_PP);	//启动CJ1上电		0.1s脉冲
	BSP_GPIO_Init(UPEDCJ2_PORT,GPIO_Mode_Out_PP);	//启动CJ2			50ms脉冲
	BSP_GPIO_Init(STARTS_PORT,GPIO_Mode_Out_PP);	//启动系统功率电源	0.1s脉冲
	BSP_GPIO_Init(STOP_P_PORT,GPIO_Mode_Out_PP);	//关闭功率电源停机	0.1s脉冲
	
	//常态输出
	BSP_GPIO_Init(FYKL_PORT,GPIO_Mode_Out_PP);		//屏蔽负压开关
	BSP_GPIO_Init(STANDBY_PORT,GPIO_Mode_Out_PP);	//禁止3875移相输出
	BSP_GPIO_Init(FD_PORT,GPIO_Mode_Out_PP);		//已放电,启动放电继电器
	BSP_GPIO_Init(PLBJ_PORT,GPIO_Mode_Out_PP);		//CPU输出功率低报警
	BSP_GPIO_Init(PHBJ_PORT,GPIO_Mode_Out_PP);		//CPU输出功率高报警
	BSP_GPIO_Init(HJSHDL_PORT,GPIO_Mode_Out_PP);	//换卷动作延时
	BSP_GPIO_Init(STOPCS_PORT,GPIO_Mode_Out_PP);	//CPU输出禁止3875输出波形
	BSP_GPIO_Init(ALARM_PORT,GPIO_Mode_Out_PP);		//报警执行停功率电源，停机
	BSP_GPIO_Init(RESET_SYS_PORT,GPIO_Mode_Out_PP);	//CPU输出系统复位信号
	
	//信号输入检测
	BSP_GPIO_Init(CJ3OK_PORT,GPIO_Mode_IN_FLOATING);	//臭氧风机检测开关
	BSP_GPIO_Init(PUPOK_PORT,GPIO_Mode_IN_FLOATING);	//初上电检测，达到80%启动CJ2
	BSP_GPIO_Init(CJ12OK_PORT,GPIO_Mode_IN_FLOATING);	//CJ1~CJ2上电完成
	BSP_GPIO_Init(LRUN_PORT,GPIO_Mode_IN_FLOATING);		//生产线运行标志
	BSP_GPIO_Init(DHAL_PORT,GPIO_Mode_IN_FLOATING);		//高压打火报警
	BSP_GPIO_Init(HIAL_PORT,GPIO_Mode_IN_FLOATING);		//高压放电过流
	BSP_GPIO_Init(IGBTBAL_PORT,GPIO_Mode_IN_FLOATING);	//IGBTB过流
	BSP_GPIO_Init(IGBTAAL_PORT,GPIO_Mode_IN_FLOATING);	//IGBTA过流
	BSP_GPIO_Init(TIAL_PORT,GPIO_Mode_IN_FLOATING);		//原边电流过流
	BSP_GPIO_Init(IDCAL_PORT,GPIO_Mode_IN_FLOATING);	//IDC过流报警
	BSP_GPIO_Init(QSALARM_PORT,GPIO_Mode_IN_FLOATING);	//缺相报警
	BSP_GPIO_Init(HJSH_PORT,GPIO_Mode_IN_FLOATING);		//换卷信号
	BSP_GPIO_Init(JTJC_PORT,GPIO_Mode_IN_FLOATING);		//急停报警
	BSP_GPIO_Init(IN_ALARM_PORT,GPIO_Mode_IN_FLOATING);	//系统报警
	BSP_GPIO_Init(PVDD_PORT,GPIO_Mode_IN_FLOATING);		//掉电报警
	
}

//冷启动端口准备
void driver_port_detection(void){
	STANDBY = 1;	//禁止3875所有输出
	STOPCS = 1;
	
	FYKL = 1;	//屏蔽负压开关		
	
	RESET_SYS = 1;		//硬件系统复位 0.1s
	delay_ms(100);
	RESET_SYS = 0;
	
	if(QSALARM) get_controlData()->error_sta |= QSALARM_ERROR;		//缺项检测
	if(DCVCHK) get_controlData()->error_sta |= DCVCHK_ERROR;		//低压电源检测
}

//脉冲输出
void pulse_output(volatile unsigned long *pulase_port,uint32_t pulse_time){
	*pulase_port = 1;
	vTaskDelay(pulse_time);
	*pulase_port = 0;
}


