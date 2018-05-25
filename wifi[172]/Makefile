PORT ?= COM12

all: wifi.hex

program: upload

wifi.elf: wifi.c USART_RS232_C_file.c ../lcd/lcd.c
	avr-g++ -mmcu=atmega324p -DF_CPU=16000000 -Wall -Os -o $@ $^

wifi.hex: wifi.elf
	avr-objcopy -j .text -j .data -O ihex wifi.elf wifi.hex
	avr-size wifi.elf

upload: wifi.hex
	avrdude -c arduino -P $(PORT) -b 57600 -p atmega324p -U flash:w:$<:a

clean:
	rm -rf wifi.elf wifi.hex

.PHONY: all clean program upload
