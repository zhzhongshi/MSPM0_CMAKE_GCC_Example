#include "ti_msp_dl_config.h"


#define DELAY (16000000)

int main(void)
{
	SYSCFG_DL_init(); //芯片资源初始化,由SysConfig配置软件自动生成
	while(1)
	{
		DL_GPIO_clearPins(LED1_PORT,LED1_PIN_14_PIN);
		DL_Common_delayCycles(DELAY);//延时0.5秒
		DL_GPIO_setPins(LED1_PORT,LED1_PIN_14_PIN);
		DL_Common_delayCycles(DELAY);//延时0.5秒
	}
}

