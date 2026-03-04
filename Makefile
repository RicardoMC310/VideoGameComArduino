all:
	@mkdir -p build temp

	avr-gcc -nostdlib -x assembler-with-cpp -mmcu=atmega328p -Os -g -c src/boot/boot.S -o temp/boot.o
	avr-gcc -nostdlib -mmcu=atmega328p -Os -g -c src/kernel/main.c -o temp/kernel.o

	avr-gcc -nostdlib -mmcu=atmega328p -Os -g temp/*.o -o build/main.o

	avr-objcopy -O ihex build/main.o build/main.hex

	avr-size -C --mcu=atmega328p build/main.o

upload:
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:build/main.hex:i