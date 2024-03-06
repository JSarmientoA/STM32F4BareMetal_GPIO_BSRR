#include "stm32f4xx.h"//Se deben cargar el dispositivo, el include y la referencia especifica
/*Registro BSRR
 * El registro BSRR se conose como registro de ajuste / reinio de bits GPIO, se utiliza para poner
 * un (1)uno logico o un (0)cero logico en la salida de un puerto.
 * El registro consta de 32 bits donde los 16 primeros (BS0-BS15) se denominan BS inicio de bists y se utilizan para
 * estableser un uno(1), 3,3v de salida y los bits del 16 al 32 (BRO-BR32) se denoinan reinicio de bits
 * y se utilzan para podenr un 0, 0.0v*/
#define GPIOAEN			(1U<<0)// Estableser un 1 logico en el bit 0
#define PIN5			(1U<<5)// Estableser un 1 logico en el bit 5
#define LED_PIN			PIN5
int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;//Conectar reloj al puerto A (pormedio del bus AHB1)

	/*Configuración del registro Moder peroferico GPIOA. pin A5 como salida*/
	GPIOA->MODER |=(1U<<10);// Estableser un 1 logico en el bit 10
	GPIOA->MODER &=~(1U<<11);// Estableser un 0 logico en el bit 11
	while(1)
	{
		/*Esta configuración del registro BSRR grantiza un 1 logico (3.3v) en el pin 5*/
		GPIOA->BSRR = (0U<<21);//Establese un 0 en el bit 21. Correspndiente al pin 5
		GPIOA->BSRR = LED_PIN;//Establese un 1 en el bit 5. Correspndiente al pin 5
		for(int i=0;i<1500000;i++){}

		/*Esta configuración del registro BSRR grantiza un 0 logico (0.0v) en el pin 5*/
		GPIOA->BSRR = (0U<<5);//Establese un 0 en el bit 5. Correspndiente al pin 5
		GPIOA->BSRR = (1U<<21);//Establese un 1 en el bit 21. Correspndiente al pin 5

		for(int j=0;j<2500000;j++){}
	}
}
/*Cada puerto maneja dos bist un un BS y un BR. Para poner un pin con 1(3.3v) se debe poner BSx=1 y BRx=0. para npner un pin con 0(0.0v)
 *se debe poner BSx=0 y BRx=1.*/
