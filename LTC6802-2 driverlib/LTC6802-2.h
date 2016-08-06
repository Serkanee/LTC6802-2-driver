#include <stdint.h>
#include <stdbool.h>

//command bytes 
#define WRCFG 		0x01
#define RDCFG 		0x02
#define RDCV  		0x04
#define RDCVA 		0x06
#define RDCVB 		0x08
#define RDCVC 		0x0A
#define RDFLG		0X0C
#define RDTMP 		0X0E
#define STCVAD_ALL 	0X10
#define STCVAD_C1	0X11
#define STCVAD_C2	0X12
#define STCVAD_C3	0X13
#define STCVAD_C4	0X14
#define STCVAD_C5	0X15
#define STCVAD_C6	0X16
#define STCVAD_C7	0X17
#define STCVAD_C8	0X18
#define STCVAD_C9	0X19
#define STCVAD_C10	0X1A
#define STCVAD_C11	0X1B
#define STCVAD_C12	0X1C
#define STCVAD_CC	0X1D
#define STCVAD_ST1	0X1E
#define STCVAD_ST2	0X1F
#define STOWAD_ALL	0X20
#define STOWAD_C1	0X21
#define STOWAD_C2	0X22
#define STOWAD_C3	0X23
#define STOWAD_C4	0X24
#define STOWAD_C5	0X25
#define STOWAD_C6	0X26
#define STOWAD_C7	0X27
#define STOWAD_C8	0X28
#define STOWAD_C9	0X29
#define STOWAD_C10	0X2A
#define STOWAD_C11	0X2B
#define STOWAD_C12	0X2C
#define STTMPAD_ALL	0x30
#define STTMPAD_EX1	0X31
#define STTMPAD_EX2	0X32
#define STTMPAD_IN	0X33
#define STTMPAD_ST1	0X3E
#define STTMPAD_ST2	0X3F
#define PLADC		0X40
#define PLINT		0X50
#define DAGN		0X52
#define RDDGNR		0X54
#define STCVDC_ALL	0X60
#define STCVDC_C1	0X61
#define STCVDC_C2	0X62
#define STCVDC_C3	0X63
#define STCVDC_C4	0X64
#define STCVDC_C5	0X65
#define STCVDC_C6	0X66
#define STCVDC_C7	0X67
#define STCVDC_C8	0X68
#define STCVDC_C9	0X69
#define STCVDC_C10	0X6A
#define STCVDC_C11	0X6B
#define STCVDC_C12	0X6C
#define STOWDC_ALL	0X70
#define STOWDC_C1	0X71
#define STOWDC_C2	0X72
#define STOWDC_C3	0X73
#define STOWDC_C4	0X74
#define STOWDC_C5	0X75
#define STOWDC_C6	0X76
#define STOWDC_C7	0X77
#define STOWDC_C8	0X78
#define STOWDC_C9	0X79
#define STOWDC_C10	0X7A
#define STOWDC_C11	0X7B
#define STOWDC_C12	0X7C //phew

//command byte PEC's 
#define WRCFG_PEC 		0xC7
#define RDCFG_PEC  		0xCE
#define RDCV_PEC   		0xDC
#define RDCVA_PEC  		0xD2
#define RDCVB_PEC  		0xF8
#define RDCVC_PEC  		0xF6
#define RDFLG_PEC 		0xE4
#define RDTMP_PEC  		0xEA
#define STCVAD_ALL_PEC 	0xB0
#define STCVAD_C1_PEC 	0xB7
#define STCVAD_C2_PEC 	0xBE
#define STCVAD_C3_PEC 	0xB9
#define STCVAD_C4_PEC 	0xAC
#define STCVAD_C5_PEC 	0xAB
#define STCVAD_C6_PEC 	0xA2
#define STCVAD_C7_PEC 	0xA5
#define STCVAD_C8_PEC 	0x88
#define STCVAD_C9_PEC 	0x8F
#define STCVAD_C10_PEC  0x86
#define STCVAD_C11_PEC 	0x81
#define STCVAD_C12_PEC 	0x94
#define STCVAD_CC_PEC 	0x93
#define STCVAD_ST1_PEC 	0x9A
#define STCVAD_ST2_PEC 	0x9D
#define STOWAD_ALL_PEC 	0x20
#define STOWAD_C1_PEC 	0x27
#define STOWAD_C2_PEC 	0X2E
#define STOWAD_C3_PEC 	0X29
#define STOWAD_C4_PEC 	0X3C
#define STOWAD_C5_PEC 	0X3B
#define STOWAD_C6_PEC 	0X32
#define STOWAD_C7_PEC 	0X35
#define STOWAD_C8_PEC 	0X18
#define STOWAD_C9_PEC 	0X1F
#define STOWAD_C10_PEC 	0X16
#define STOWAD_C11_PEC 	0X11
#define STOWAD_C12_PEC 	0X4
#define STTMPAD_ALL_PEC	0x50
#define STTMPAD_EX1_PEC	0X57
#define STTMPAD_EX2_PEC	0X5E
#define STTMPAD_IN_PEC 	0X59
#define STTMPAD_ST1_PEC 0X7A
#define STTMPAD_ST2_PEC 0X7D
#define PLADC_PEC 		0X07
#define PLINT_PEC 		0X77
#define DAGN_PEC 		0X79
#define RDDGNR_PEC 		0X6B
#define STCVDC_ALL_PEC 	0XE7
#define STCVDC_C1_PEC 	0XE0
#define STCVDC_C2_PEC 	0XE9
#define STCVDC_C3_PEC 	0XEE
#define STCVDC_C4_PEC 	0XFB
#define STCVDC_C5_PEC 	0XFC
#define STCVDC_C6_PEC 	0XF5
#define STCVDC_C7_PEC 	0xF2
#define STCVDC_C8_PEC 	0XDF
#define STCVDC_C9_PEC 	0XD8
#define STCVDC_C10_PEC 	0XD1
#define STCVDC_C11_PEC 	0XD6
#define STCVDC_C12_PEC 	0xC3
#define STOWDC_ALL_PEC 	0X97
#define STOWDC_C1_PEC 	0X90
#define STOWDC_C2_PEC 	0X99
#define STOWDC_C3_PEC 	0X9E
#define STOWDC_C4_PEC 	0X8B
#define STOWDC_C5_PEC 	0X8C
#define STOWDC_C6_PEC 	0X85
#define STOWDC_C7_PEC 	0X82
#define STOWDC_C8_PEC 	0XAF
#define STOWDC_C9_PEC 	0XA8
#define STOWDC_C10_PEC 	0XA1
#define STOWDC_C11_PEC 	0XA6
#define STOWDC_C12_PEC 	0XB3

//cfgRegister bit names --R4 and 5 excluded as they don't have individual bits to be set
#define R0_WDT		0b10000000
#define R0_GPIO2	0b01000000
#define R0_GPIO1	0b00100000
#define R0_LVLPL	0b00010000
#define R0_CELL10	0b00001000
#define R0_CDC2		0b00000100
#define R0_CDC1		0b00000010
#define R0_CDC0		0b00000001
#define R1_DCC8		0b10000000
#define R1_DCC7		0b01000000
#define R1_DCC6		0b00100000
#define R1_DCC5		0b00010000
#define R1_DCC4		0b00001000
#define R1_DCC3		0b00000100
#define R1_DCC2		0b00000010
#define R1_DCC1		0b00000001
#define R2_MC4I		0b10000000
#define R2_MC3I		0b01000000
#define R2_MC2I		0b00100000
#define R2_MC1I		0b00010000
#define R2_DCC12	0b00001000
#define R2_DCC11	0b00000100
#define R2_DCC10	0b00000010
#define R2_DCC9		0b00000001
#define R3_MC12I	0b10000000
#define R3_MC11I	0b01000000
#define R3_MC10I	0b00100000
#define R3_MC9I		0b00010000
#define R3_MC8I		0b00001000
#define R3_MC7I		0b00000100
#define R3_MC6I		0b00000010
#define R3_MC5I		0b00000001

//flag register bits

#define R0_C4OV 	0b10000000
#define R0_C4UV 	0b01000000
#define R0_C3OV 	0b00100000
#define R0_C3UV 	0b00010000
#define R0_C2OV		0b00001000
#define R0_C2UV 	0b00000100
#define R0_C1OV 	0b00000010
#define R0_C1UV 	0b00000001
#define R1_C8OV		0b10000000
#define R1_C8UV 	0b01000000
#define R1_C7OV 	0b00100000
#define R1_C7UV 	0b00010000
#define R1_C6OV 	0b00001000
#define R1_C6UV 	0b00000100
#define R1_C5OV		0b00000010
#define R1_C5UV		0b00000001
#define R2_C12OV	0b10000000
#define R2_C12UV	0b01000000
#define R2_C11OV	0b00100000
#define R2_C11UV	0b00010000
#define R2_C10OV	0b00001000
#define R2_C10UV	0b00000100
#define R2_C9OV		0b00000010
#define R2_C9UV		0b00000001


//other
#define BROADCAST_ADDRESS 			 0xFF
#define START_ALL					 0


#define CFG_REG_STRUCT_BIT_COUNT	 48
#define CFG_REGISTERS_COUNT			 6


#define VOLT_REGISTERS_COUNT_FULL	 18
#define VOLT_REGISTERS_COUNT_PARTIAL 18
#define VOLT_REGISTERS_COMP_ALL		 1
#define VOLT_REGISTERS_COMP_A 		 2
#define VOLT_REGISTERS_COMP_B		 3
#define VOLT_REGISTERS_COMP_C		 4

#define TEMP_REGISTERS_COUNT		 5
#define FLAGS_REGISTERS_COUNT 		 3
#define DIAGS_REGISTERS_COUNT		 2

#define START_EXTERNAL_TEMP1 		 1
#define START_EXTERNAL_TEMP2 		 2
#define START_INTERNAL_TEMP 		 3
#define START_TEST_TEMP1 	 		 4
#define START_TEST_TEMP2	 		 5

#define FIRST_BIT_SHIFT				 0
#define SECOND_BIT_SHIFT			 1
#define THIRD_BIT_SHIFT				 2
#define FOURTH_BIT_SHIFT			 3
#define FIFTH_BIT_SHIFT				 4
#define SIXTH_BIT_SHIFT				 5
#define SEVENTH_BIT_SHIFT			 6
#define EIGHTH_BIT_SHIFT			 7
#define FOURTYEIGHTH_BIT_SHIFT		 47

#define DONT_MOD_CONFIG_REG			 0xFFFF
#define MOD_ALL_CONFIG_REG			 0xFF
#define ALL_FLAGS_CLEAR				 0

typedef struct {
	uint8_t cfgr0;
	uint8_t cfgr1;
	uint8_t cfgr2;
	uint8_t cfgr3;
	uint8_t cfgr4;	
	uint8_t cfgr5;
} cfgRegisterStruct;

typedef struct{
	uint8_t flgr0;
	uint8_t flgr1;
	uint8_t flgr2;
} flagRegisterStruct;

typedef struct{
	uint16_t refVolt;
	uint8_t revisionCode;
	bool muxfail;
} diagnosticStruct;

typedef struct{
	uint16_t cell1Voltage;
	uint16_t cell2Voltage;
	uint16_t cell3Voltage;
	uint16_t cell4Voltage;
	uint16_t cell5Voltage;
	uint16_t cell6Voltage;
	uint16_t cell7Voltage;
	uint16_t cell8Voltage;
	uint16_t cell9Voltage;
	uint16_t cell10Voltage;
	uint16_t cell11Voltage;
	uint16_t cell12Voltage;
} cellVoltageStruct;

typedef struct{
	uint16_t externalTemp1;
	uint16_t externalTemp2;
	uint16_t internalTemp;
	bool thermalShutdownFlag;
} temperatureStruct;




void initConfigStruct(cfgRegisterStruct * cfgRegister);
/*
prereq: address <= 15
*/
void configWrite(uint8_t address, cfgRegisterStruct * cfgRegister);

void configRead(uint8_t address, cfgRegisterStruct * cfgRegister);

void readAllCells(uint8_t address, cellVoltageStruct * cellVolts);

void readCell1to4(uint8_t address, cellVoltageStruct * cellVolts);

void readCell5to8(uint8_t address, cellVoltageStruct * cellVolts);

void readCell9to12(uint8_t address, cellVoltageStruct * cellVolts);

void readTemperatures(uint8_t address, temperatureStruct * temperatures);

void readFlagRegister(uint8_t address, flagRegisterStruct * flags);

void readDiagnosticRegister(uint8_t address, diagnosticStruct * diags);

void startVoltADCAndPoll(uint8_t address, uint8_t cellNumber);

void clearConverter(uint8_t address);

void startADCTest1(uint8_t address);

void startADCTest2(uint8_t address);

void startOpenADCAndPoll(uint8_t address, uint8_t cellNumber);

void startTempADCAndPoll(uint8_t address, uint8_t operation);

void startDiagnosticAndPoll(uint8_t address);

void voltADCPollAndDischarge(uint8_t address, uint8_t cellNumber);

void openADCPollAndDischarge(uint8_t address, uint8_t cellNumber);

void pollADCStatus(uint8_t address);

void pollInterruptStatus(uint8_t address);

void setConfigs(cfgRegisterStruct * cfgRegister, uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3);

void desetConfigs(cfgRegisterStruct * cfgRegister, uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3);

void modifyUVCompVolt(cfgRegisterStruct * cfgRegister, uint16_t uvCompVolt);

void modifyOVCompVolt(cfgRegisterStruct * cfgRegister, uint16_t ovCompVolt);

void setWDT(cfgRegisterStruct * cfgRegister);

void desetWDT(cfgRegisterStruct * cfgRegister);

void setGPIO1(cfgRegisterStruct * cfgRegister);

void desetGPIO1(cfgRegisterStruct * cfgRegister);

void setGPIO2(cfgRegisterStruct * cfgRegister);

void desetGPIO2(cfgRegisterStruct * cfgRegister);

void setLevelPolling(cfgRegisterStruct * cfgRegister);

void setTogglePolling(cfgRegisterStruct * cfgRegister);

void setOnly10Cells(cfgRegisterStruct * cfgRegister);

void desetOnly10Cells(cfgRegisterStruct * cfgRegister);

void modifyCDC(cfgRegisterStruct * cfgRegister, uint8_t newCDC);

void startDischargeCell(cfgRegisterStruct * cfgRegister, uint8_t cellNumber);

void stopDischargeCell(cfgRegisterStruct * cfgRegister, uint8_t cellNumber);

void maskCellInterrupt(cfgRegisterStruct * cfgRegister, uint8_t cellNumber);

void demaskCellInterupt(cfgRegisterStruct * cfgRegister, uint8_t cellNumber);

//returns ALL_FLAGS_CLEAR if all overvoltage flags good, else returns the number of which cell is overvolting

uint8_t checkSpecificUV(flagRegisterStruct * flags, uint8_t cellToCheck);

uint8_t checkSpecificOV(flagRegisterStruct * flags, uint8_t cellToCheck);

uint8_t checkUV(flagRegisterStruct * flags);

uint8_t checkOV(flagRegisterStruct * flags);

uint8_t checkUVOnly10(flagRegisterStruct * flags);

uint8_t checkOVOnly10(flagRegisterStruct * flags);

uint8_t checkForLevelPoll(void * ptrToGPIOPin);






//Functions called by functions


uint8_t makeAddressPEC(uint8_t message);

static uint8_t makeConfigStructPEC(cfgRegisterStruct * cfgRegister);

//function wrappers for hardware serial API's
static void serialOut(uint8_t message);

static uint8_t serialIn();

static uint8_t GPIOCheck(void * ptrToGPIOPin);

static void readIn(uint8_t buffer[], uint8_t byteCount);

static void computeRegisterToVolt(uint8_t buffer[], cellVoltageStruct * cellVolts, uint8_t count);

static void computeRegisterToTemperature(uint8_t buffer[], temperatureStruct * temperatures);

static void computeRegisterToDiagnostic(uint8_t buffer[], diagnosticStruct * diags);

static uint8_t encodeAddress(uint8_t address);