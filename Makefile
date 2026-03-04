all:
	@mkdir -p build temp

	avr-gcc -nostdlib -x assembler-with-cpp -mmcu=atmega328p -Os -g -c src/boot/boot.S -o temp/boot.o
	avr-gcc -nostdlib -x assembler-with-cpp -mmcu=atmega328p -Os -g -c src/hd/*.S -o temp/hd-s.o

	avr-gcc -nostdlib -mmcu=atmega328p -Os -g -c src/hd/*.c -o temp/hd-c.o -Iinclude
	avr-gcc -nostdlib -mmcu=atmega328p -Os -g -c src/kernel/main.c -o temp/kernel.o -Iinclude

	avr-gcc -nostdlib -mmcu=atmega328p -Os -g temp/*.o -o build/main.o

	avr-objcopy -O ihex build/main.o build/main.hex

	avr-size -C --mcu=atmega328p build/main.o

upload:
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:build/main.hex:i

clean:
	@rm -rf build/* temp/*