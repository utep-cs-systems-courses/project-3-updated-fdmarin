# makefile



COMMON_OBJECTS =



CPU		= MSP430G2553



CFLAGS		= -mmcu=${CPU} -Os -I../h



LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include







CC		= msp430-elf-gcc



AS		= msp430-elf-as



AR 		= msp430-elf-ar







all: main.elf







main.elf: ${COMMON_OBJECTS} main.o triangle.o p1_interrupt_handler.o led.o switches.o buzzer.o stateMachine.o ../lib/libTimer.a



	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lLcd -lp2sw -lTimer



load: main.elf



	msp430loader.sh main.elf







clean:



	rm -f *.o *.elf *~
