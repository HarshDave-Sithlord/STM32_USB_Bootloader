# STM32_USB_Bootloader
- Bootloader for STM32F7 series controller, allows to load the binary from USB stick into the flash memory, and boot from that binary image.
- Incorporates flash interface, an abstraction layer that is easy to port with minimal configuration.
- An interface to relocate the vector table, which will be required for storing multiple application image within the flash.

Check Readme directory for architecture design document.

Demo Video @ https://www.youtube.com/watch?v=Kq3xcXK52XU&t=7s
