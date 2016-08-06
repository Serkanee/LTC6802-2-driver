# LTC6802-2-driver
software written up for controlling the LTC6802-2 chip in general C code. Note that the actual implementation requires a few software changes to account for the microcontroller being used, such as general serial in/out and GPIO pin functions that need to be replaced with the hardware specific implementation

Note this is a work in progress; the software has yet to actually be tested with an IC. Initial features such as serial error check byte calculation has been verified
