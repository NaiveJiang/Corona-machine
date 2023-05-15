#include "driver.h"

//���岶�񱣴�
pulse_captureStruct BSPSI_CALC;
pulse_captureStruct LSPSI_CALC;

//���벶������
BSP_TIM_ICAP_TypeDef BSPSI_ICAP = {		//PB6-------CH1
	BSPSI,
	TIM_ICPolarity_Falling,
};

BSP_TIM_ICAP_TypeDef LSPSI_ICAP = {		//PB7-------CH2
	LSPSI,
	TIM_ICPolarity_Falling,
};


void drive_pulse_capture_Init(TIM_TypeDef* ICAP_TIMx){
#if USE_TEST_ICAP
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_Pin_TO_PinAFConfig(TIM_TO_GPIO_PinRemap(ICAP_TIMx));
#endif
	//TIM ICAP��ʼ��
	BSP_TIM_ICAP_Init(ICAP_TIMx,ICAP_TIMER_PEROID,ICAP_TIMER_PRESCALER,&BSPSI_ICAP,&LSPSI_ICAP,NULL,NULL,ICAP_PREEMPTIONPRIORITY,ICAP_SUBPRIORITY);
}


