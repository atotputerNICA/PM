PORT ?= COM12

all: main.hex

program: upload

main.elf: main.c lcd/lcd.c keypad/key.c buzzer/buzzer.c led/led.c timer/timer.c
	avr-g++ -mmcu=atmega324p -DF_CPU=16000000 -Wall -Os -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.elf

upload: main.hex
	avrdude -c arduino -P $(PORT) -b 57600 -p atmega324p -U flash:w:$<:a

clean:
	rm -rf main.elf main.hex

.PHONY: all clean program upload
