F_CPU = 16000000
MCU = atmega328p

all:
	@mkdir -p build temp

	# Compilar assembly
	avr-gcc -x assembler-with-cpp -mmcu=$(MCU) -Os -g -c src/boot/boot.S -o temp/boot.o
	avr-gcc -x assembler-with-cpp -mmcu=$(MCU) -Os -g -c src/hd/delay.S -o temp/delay-s.o

	# Compilar C
	avr-gcc -mmcu=$(MCU) -Os -g -DF_CPU=$(F_CPU)UL -c src/hd/delay.c -o temp/delay.o -Iinclude
	avr-gcc -mmcu=$(MCU) -Os -g -DF_CPU=$(F_CPU)UL -c src/hd/millis.c -o temp/millis.o -Iinclude
	avr-gcc -mmcu=$(MCU) -Os -g -DF_CPU=$(F_CPU)UL -c src/kernel/main.c -o temp/kernel.o -Iinclude

	# Linkar
	avr-gcc -mmcu=$(MCU) -Os -g temp/*.o -o build/main.elf

	# Gerar hex
	avr-objcopy -O ihex build/main.elf build/main.hex
	avr-size -C --mcu=$(MCU) build/main.elf

upload:
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:build/main.hex:i

clean:
	@rm -rf build/* temp/*