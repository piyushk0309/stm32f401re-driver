# stm32f401re-driver  
->  Developed GPIO, SPI, I2C Driver for my STM32 F401RE MicroController.  

->  /inc contains the header files for both peripherals.

->  /src contains the implementation of API'S declared in /inc header files

    
# Tested the GPIO driver with 4 Examples  
->001ledtoggle.c                       // program to toggle an led with some delay  
->002ledbutton.c                      // program to toggle led on onboard button click of nucleo using polling  
->003led_button_ext.c                //  program to toggle led with external button click using polling   
->004led_button_extinterrupt.c      // program to toggle led with external button using interrupt and ISR  #

 # Tested the SPI driver with 1 Example
 ->006spi_tx_testing.c                // program to send string "hello world" via spi at sclk freq 8MHz

