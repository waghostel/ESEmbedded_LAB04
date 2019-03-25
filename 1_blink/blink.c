#include <stdint.h>
#include "reg.h"

//Initializaiton the target LED
void led_init(unsigned int led)
{

 	//Setup RCC(Reset and clock contro) to enable GPIOD
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTD)); 
	//RCC_AHB1ENR_OFFSET: 需要加上offset 0x30的offset

	//MODER led pin = 01 => General purpose output mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_1_BIT(led)); //把第31bit轉成0
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_0_BIT(led));//把第30bit轉成0
	

	//OT(Output type) led pin = 0 => Output push-pull output type
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OTYPER_OFFSET, OTy_BIT(led)); 

	//OSPEEDR(output speed register) led pin = 00 => Low speed(對LED閃爍其實沒差，因為low speed也太快了)
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(led));//Set bit 31 to 0
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(led));//Set bit 30 to 0

	//PUPDR(pull-up/pull-down register) led pin = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(led));//Set bit 31 to 0
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(led));//Set bit 30 to 1


}

//Blink target LED forever
void blink(unsigned int led)
{
//	led_init(led);

	unsigned int i;


		//set GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));

		for (i = 0; i < 100000; i++)
			;

		//reset GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));

		for (i = 0; i < 100000; i++)
			;
}

//Blink target LED for count times
void blink_count(unsigned int led, unsigned int count)
{

	/*
	led_init(led);
unsigned int i;
	for(i=0;i<count;i++){
		blink(led);
	}
*/

	led_init(led);


	for (unsigned int j = 0; j < count; j++)
	{
	blink(led);
	}
}
