#include "bms_library.h"


void initConfigStruct(cfgRegisterStruct * cfgRegister)
{
    desetConfigs(cfgRegister, R0_WDT | R0_GPIO1 | R0_GPIO2 | R0_CELL10, MOD_ALL_CONFIG_REG, MOD_ALL_CONFIG_REG, MOD_ALL_CONFIG_REG);
    setConfigs(cfgRegister, R0_LVLPL, DONT_MOD_CONFIG_REG, DONT_MOD_CONFIG_REG, DONT_MOD_CONFIG_REG);
    modifyCDC(cfgRegister, 2);
    modifyUVCompVolt(cfgRegister, 100);
    modifyOVCompVolt(cfgRegister, 100);
}

void configRead(uint8_t address, cfgRegisterStruct * cfgRegister)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }//if not, then it's broadcast write
    
    serialOut(RDCFG);
    serialOut(RDCFG_PEC);
    
    readIn(buffer, CFG_REGISTERS_COUNT);
    
    cfgRegister -> cfgr0 = buffer[0];
    cfgRegister -> cfgr1 = buffer[1];
    cfgRegister -> cfgr2 = buffer[2];
    cfgRegister -> cfgr3 = buffer[3];
    cfgRegister -> cfgr4 = buffer[4];
    cfgRegister -> cfgr5 = buffer[5];

}

void configWrite(uint8_t address, cfgRegisterStruct * cfgRegister)
{
    uint8_t dataPEC;
    dataPEC = makeConfigStructPEC(cfgRegister);
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(WRCFG);
    serialOut(WRCFG_PEC);
    serialOut(cfgRegister -> cfgr0);
    serialOut(cfgRegister -> cfgr1);
    serialOut(cfgRegister -> cfgr2);
    serialOut(cfgRegister -> cfgr3);
    serialOut(cfgRegister -> cfgr4);
    serialOut(cfgRegister -> cfgr5);
    serialOut(dataPEC);

}

void readAllCells(uint8_t address, cellVoltageStruct * cellVolts)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
        
    serialOut(RDCV);
    serialOut(RDCV_PEC);
    
    readIn(buffer, VOLT_REGISTERS_COUNT_FULL); //read in the data into the buffer
    
    computeRegisterToVolt(buffer, cellVolts, VOLT_REGISTERS_COMP_ALL); //convert registers into actual voltage rating
    
}

void readCell1to4(uint8_t address, cellVoltageStruct * cellVolts)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
        
    serialOut(RDCVA);
    serialOut(RDCVA_PEC);
    
    readIn(buffer, VOLT_REGISTERS_COUNT_PARTIAL); //read in the data into the buffer
    
    computeRegisterToVolt(buffer, cellVolts, VOLT_REGISTERS_COMP_A); //convert registers into actual voltage rating
}

void readCell5to8(uint8_t address, cellVoltageStruct * cellVolts)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC); 
    }
        
    serialOut(RDCVB);
    serialOut(RDCVB_PEC);
    
    readIn(buffer, VOLT_REGISTERS_COUNT_PARTIAL); //read in the data into the buffer
    
    computeRegisterToVolt(buffer, cellVolts, VOLT_REGISTERS_COMP_B); //convert registers into actual voltage rating
}

void readCell9to12(uint8_t address, cellVoltageStruct * cellVolts)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
    
    serialOut(RDCVC);
    serialOut(RDCVC_PEC);
    
    readIn(buffer, VOLT_REGISTERS_COUNT_PARTIAL); //read in the data into the buffer
    
    computeRegisterToVolt(buffer, cellVolts, VOLT_REGISTERS_COMP_C); //convert registers into actual voltage rating
}

void readTemperatures(uint8_t address, temperatureStruct * temperatures)
{
     uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
        
    serialOut(RDTMP);
    serialOut(RDTMP_PEC);
    
    readIn(buffer, TEMP_REGISTERS_COUNT); //read in the data into the buffer
    
    computeRegisterToTemperature(buffer, temperatures);
}

void readFlagRegister(uint8_t address, flagRegisterStruct * flags)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
        
    serialOut(RDFLG);
    serialOut(RDFLG_PEC);
    
    readIn(buffer, FLAGS_REGISTERS_COUNT); //read in the data into the buffer
    
    flags -> flgr0 = buffer[0];
    flags -> flgr1 = buffer[1];
    flags -> flgr2 = buffer[2];
}

void readDiagnosticRegister(uint8_t address, diagnosticStruct * diags)
{
    uint8_t buffer[20];
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }
        
    
    serialOut(RDDGNR);
    serialOut(RDDGNR_PEC);
    
    readIn(buffer, DIAGS_REGISTERS_COUNT); //read in the data into the buffer
    
    computeRegisterToDiagnostic(buffer, diags);
}

void startVoltADCAndPoll(uint8_t address, uint8_t cellNumber)
{
    uint8_t command, commandPEC;
    switch(cellNumber)
    {
        case START_ALL:
            command = (STCVAD_ALL);
            commandPEC = (STCVAD_ALL_PEC);
            break;
            
        case 1:
            command = (STCVAD_C1);
            commandPEC = (STCVAD_C1_PEC);
            break;
            
        case 2:
            command = (STCVAD_C2);
            commandPEC = (STCVAD_C2_PEC);
            break;
            
        case 3:
            command = (STCVAD_C3);
            commandPEC = (STCVAD_C3_PEC);
            break;
            
        case 4:
            command = (STCVAD_C4);
            commandPEC = (STCVAD_C4_PEC);
            break;
            
        case 5:
            command = (STCVAD_C5);
            commandPEC = (STCVAD_C5_PEC);
            break;
            
        case 6:
            command = (STCVAD_C6);
            commandPEC = (STCVAD_C6_PEC);
            break;
            
        case 7:
            command = (STCVAD_C7);
            commandPEC = (STCVAD_C7_PEC);
            break;
            
        case 8:
            command = (STCVAD_C8);
            commandPEC = (STCVAD_C8_PEC);
            break;
            
        case 9:;
            command = (STCVAD_C9);
            commandPEC = (STCVAD_C9_PEC);
            break;
            
        case 10:
            command = (STCVAD_C10);
            commandPEC = (STCVAD_C10_PEC);
            break;
            
        case 11:
            command = (STCVAD_C11);
            commandPEC = (STCVAD_C11_PEC);
            break;
            
        case 12:
            command = (STCVAD_C12);
            commandPEC = (STCVAD_C12_PEC);
            break;
    }
        
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(command);
    serialOut(commandPEC);
}

void clearConverter(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
        
    }

    serialOut(STCVAD_CC);
    serialOut(STCVAD_CC_PEC);
}

void startADCTest1(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }

    serialOut(STCVAD_ST1);
    serialOut(STCVAD_ST1_PEC);
}

void startADCTest2(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }

    serialOut(STCVAD_ST2);
    serialOut(STCVAD_ST2_PEC);
}

void startOpenADCAndPoll(uint8_t address, uint8_t cellNumber)
{
    uint8_t command, commandPEC;
    
    switch(cellNumber) //different commands based on if you want to read all cells or 1 specific cell, switch case checks which it is and stores it and its PEC into the variables
    {
        case START_ALL:
            command = (STOWAD_ALL);
            commandPEC = (STOWAD_ALL_PEC);
            break;
            
        case 1:
            command = (STOWAD_C1);
            commandPEC = (STOWAD_C1_PEC);
            break;
            
        case 2:
            command = (STOWAD_C2);
            commandPEC = (STOWAD_C2_PEC);
            break;
            
        case 3:
            command = (STOWAD_C3);
            commandPEC = (STOWAD_C3_PEC);
            break;
            
        case 4:
            command = (STOWAD_C4);
            commandPEC = (STOWAD_C4_PEC);
            break;
            
        case 5:
            command = (STOWAD_C5);
            commandPEC = (STOWAD_C5_PEC);
            break;
            
        case 6:
            command = (STOWAD_C6);
            commandPEC = (STOWAD_C6_PEC);
            break;
            
        case 7:
            command = (STOWAD_C7);
            commandPEC = (STOWAD_C7_PEC);
            break;
            
        case 8:
            command = (STOWAD_C8);
            commandPEC = (STOWAD_C8_PEC);
            break;
            
        case 9:
            command = (STOWAD_C9);
            commandPEC = (STOWAD_C9_PEC);
            break;
            
        case 10:
            command = (STOWAD_C10);
            commandPEC = (STOWAD_C10_PEC);
            break;
            
        case 11:
            command = (STOWAD_C11);
            commandPEC = (STOWAD_C11_PEC);
            break;
            
        case 12:
            command = (STOWAD_C12);
            commandPEC = (STOWAD_C12_PEC);
            break;
    }
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC, command, commandPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(command);
    serialOut(commandPEC);
}

void voltADCPollAndDischarge(uint8_t address, uint8_t cellNumber)
{
    uint8_t command, commandPEC;
    switch(cellNumber)
    {
        case START_ALL:
            command = (STCVDC_ALL);
            commandPEC = (STCVDC_ALL_PEC);
            break;
            
        case 1:
            command = (STCVDC_C1);
            commandPEC = (STCVDC_C1_PEC);
            break;
            
        case 2:
            command = (STCVDC_C2);
            commandPEC = (STCVDC_C2_PEC);
            break;
            
        case 3:
            command = t(STCVDC_C3);
            commandPEC = (STCVDC_C3_PEC);
            break;
            
        case 4:
            command = (STCVDC_C4);
            commandPEC = (STCVDC_C4_PEC);
            break;
            
        case 5:
            command = (STCVDC_C5);
            commandPEC = (STCVDC_C5_PEC);
            break;
            
        case 6:
            command = (STCVDC_C6);
            commandPEC = (STCVDC_C6_PEC);
            break;
            
        case 7:
            command = (STCVDC_C7);
            commandPEC = (STCVDC_C7_PEC);
            break;
            
        case 8:
            command = (STCVDC_C8);
            commandPEC = (STCVDC_C8_PEC);
            break;
            
        case 9:
            command = (STCVDC_C9);
            commandPEC = (STCVDC_C9_PEC);
            break;
            
        case 10:
            command = (STCVDC_C10);
            commandPEC = (STCVDC_C10_PEC);
            break;
            
        case 11:
            command = (STCVDC_C11);
            commandPEC = (STCVDC_C11_PEC);
            break;
            
        case 12:
            command = (STCVDC_C12);
            commandPEC = (STCVDC_C12_PEC);
            break;
    }
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(command);
    serialOut(commandPEC);
}

void openADCPollAndDischarge(uint8_t address, uint8_t cellNumber)
{
    uint8_t command, commandPEC;
    switch(cellNumber)
    {
        case START_ALL:
            command = (STOWDC_ALL);
            commandPEC = (STOWDC_ALL_PEC);
            break;
            
        case 1:
            command = (STOWDC_C1);
            commandPEC = (STOWDC_C1_PEC);
            break;
            
        case 2:
            command = (STOWDC_C2);
            commandPEC = (STOWDC_C2_PEC);
            break;
            
        case 3:
            command = (STOWDC_C3);
            commandPEC = (STOWDC_C3_PEC);
            break;
            
        case 4:
            command = (STOWDC_C4);
            commandPEC = (STOWDC_C4_PEC);
            break;
            
        case 5:
            command = (STOWDC_C5);
            commandPEC = (STOWDC_C5_PEC);
            break;
            
        case 6:
            command = (STOWDC_C6);
            commandPEC = (STOWDC_C6_PEC);
            break;
            
        case 7:
            command = (STOWDC_C7);
            commandPEC = (STOWDC_C7_PEC);
            break;
            
        case 8:
            command = (STOWDC_C8);
            commandPEC = (STOWDC_C8_PEC);
            break;
            
        case 9:
            command = (STOWDC_C9);
            commandPEC = (STOWDC_C9_PEC);
            break;
            
        case 10:
            command = (STOWDC_C10);
            commandPEC = (STOWDC_C10_PEC);
            break;
            
        case 11:
            command = (STOWDC_C11);
            commandPEC = (STOWDC_C11_PEC);
            break;
            
        case 12:
            command = (STOWDC_C12);
            commandPEC = (STOWDC_C12_PEC);
            break;
    }
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(command);
    serialOut(commandPEC);
}

void startTempADCAndPoll(uint8_t address, uint8_t operation)
{
    uint8_t command, commandPEC;
    switch(operation)
    {
        case START_ALL:
            command = (STTMPAD_ALL);
            commandPEC = (STTMPAD_ALL_PEC);
            break;
            
        case START_EXTERNAL_TEMP1:
            command = (STTMPAD_EX1);
            commandPEC = (STTMPAD_EX1_PEC);
            break;
            
        case START_EXTERNAL_TEMP2:
            command = (STTMPAD_EX2);
            commandPEC = (STTMPAD_EX2_PEC);
            break;
            
        case START_INTERNAL_TEMP:
            command = (STTMPAD_IN);
            commandPEC = (STTMPAD_IN_PEC);
            break;
            
        case START_TEST_TEMP1:
            command = (STTMPAD_ST1);
            commandPEC = (STTMPAD_ST1_PEC);
            break;
            
        case START_TEST_TEMP2:
            command = (STTMPAD_ST2);
            commandPEC = (STTMPAD_ST2_PEC);
            break;
    }
    
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address);
        serialOut(addressPEC);
    }
    
    serialOut(command);
    serialOut(commandPEC);
}

void startDiagnosticAndPoll(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }

    serialOut(DAGN);
    serialOut(DAGN_PEC);
}

void pollADCStatus(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }

    serialOut(PLADC);
    serialOut(PLADC_PEC);
}

void pollInterruptStatus(uint8_t address)
{
    if((address >= 0) && (address != BROADCAST_ADDRESS)) //address write
    {
        uint8_t addressPEC;
        
        address = encodeAddress(address); //converts the address into the protocol the chop receives
        addressPEC = makeAddressPEC(address);
        
        serialOut(address); //write out data
        serialOut(addressPEC);
    }

    serialOut(PLINT);
    serialOut(PLINT_PEC);
}

void setConfigs(cfgRegisterStruct * cfgRegister, uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3)
{
    if(reg0 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr0 |= (uint8_t)reg0;
    
    if(reg1 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr1 |= (uint8_t)reg1;
        
    if(reg2 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr2 |= (uint8_t)reg2;
        
    if(reg3 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr3 |= (uint8_t)reg3;
}

void desetConfigs(cfgRegisterStruct * cfgRegister, uint16_t reg0, uint16_t reg1, uint16_t reg2, uint16_t reg3)
{
    if(reg0 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr0 &= ~((uint8_t)reg0);
    
    if(reg1 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr1 &= ~((uint8_t)reg1);
        
    if(reg2 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr2 &= ~((uint8_t)reg2);
        
    if(reg3 != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr3 &= ~((uint8_t)reg3);
}

void modifyUVCompVolt(cfgRegisterStruct * cfgRegister, uint16_t uvCompVolt)
{
    if(uvCompVolt != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr4 = (uint8_t)uvCompVolt;
}

void modifyOVCompVolt(cfgRegisterStruct * cfgRegister, uint16_t ovCompVolt)
{
    if(ovCompVolt != DONT_MOD_CONFIG_REG)
        cfgRegister -> cfgr5 = (uint8_t)ovCompVolt;
}

void setWDT(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 |= R0_WDT;
}

void desetWDT(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 &= ~R0_WDT;
}

void setGPIO1(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 |= R0_GPIO1;
}

void desetGPIO1(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 &= ~R0_GPIO1;
}

void setGPIO2(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 |= R0_GPIO2;
}

void desetGPIO2(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 &= ~R0_GPIO2;
}

void setLevelPolling(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 |= R0_LVLPL;
}

void setTogglePolling(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 &= ~R0_LVLPL;    
}

void setOnly10Cells(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 |= R0_CELL10;
}

void desetOnly10Cells(cfgRegisterStruct * cfgRegister)
{
    cfgRegister -> cfgr0 &= ~R0_CELL10;
}

void modifyCDC(cfgRegisterStruct * cfgRegister, uint8_t newCDC)
{
    newCDC &= 0b00000111;
    cfgRegister -> cfgr0 |= newCDC;
}

void startDischargeCell(cfgRegisterStruct * cfgRegister, uint8_t cellNumber)
{
    if(cellNumber <= 8)
    {
        cfgRegister -> cfgr1 |= (1 << (cellNumber - 1));
    }
    else if(cellNumber <= 12)
    {
        cfgRegister -> cfgr2 |= (1 << (cellNumber - 9));
    }
}

void stopDischargeCell(cfgRegisterStruct * cfgRegister, uint8_t cellNumber)
{
    if(cellNumber <= 8)
    {
        cfgRegister -> cfgr1 &= ~(1 << (cellNumber - 1));
    }
    else if(cellNumber <= 12)
    {
        cfgRegister -> cfgr2 &= ~(1 << (cellNumber - 9));
    }
}

void maskCellInterrupt(cfgRegisterStruct * cfgRegister, uint8_t cellNumber)
{
    if(cellNumber <= 4)
    {
        cfgRegister -> cfgr2 |= (1 << (cellNumber + 3));
    }
    else if(cellNumber <= 12)
    {
        cfgRegister -> cfgr3 |= (1 << (cellNumber - 5));
    }
}

void demaskCellInterupt(cfgRegisterStruct * cfgRegister, uint8_t cellNumber)
{
    if(cellNumber <= 4)
    {
        cfgRegister -> cfgr2 &= ~(1 << (cellNumber + 3));
    }
    else if(cellNumber <= 12)
    {
        cfgRegister -> cfgr3 &= ~(1 << (cellNumber - 5));
    }
}

uint8_t checkSpecificUV(flagRegisterStruct * flags, uint8_t cellToCheck)
{
    uint8_t flagged = 0;
    if(cellToCheck <= 4)
    {
        flagged = ((flags -> flgr0 >> (2 * (cellToCheck - 1))) & 1);
    }
    else if(cellToCheck <= 8)
    {
        flagged = ((flags -> flgr1 >> (2 * (cellToCheck - 5))) & 1);
    }
    else if(cellToCheck <= 12)
    {
        flagged = ((flags -> flgr2 >> (2 * (cellToCheck - 9))) & 1);
    }
    
    return(flagged);
}

uint8_t checkSpecificOV(flagRegisterStruct * flags, uint8_t cellToCheck)
{
    uint8_t flagged = 0;
    if(cellToCheck <= 4)
    {
        flagged = ((flags -> flgr0 >> ((2 * cellToCheck) - 1)) & 1);
    }
    else if(cellToCheck <= 8)
    {
        flagged = ((flags -> flgr1 >> ((2 * cellToCheck) - 9)) & 1);
    }
    else if(cellToCheck <= 12)
    {
        flagged = ((flags -> flgr1 >> ((2 * cellToCheck) - 17)) & 1);
    }
    
    return(flagged);
}

uint8_t checkUV(flagRegisterStruct * flags)
{
    uint8_t flagged = ALL_FLAGS_CLEAR;
    
    if((flags -> flgr0 >> 0) & 1)//cell 1
        flagged = 1;
    else if((flags -> flgr0 >> 2) & 1)//cell 2
        flagged = 2;
    else if((flags -> flgr0 >> 4) & 1)//cell 3
        flagged = 3;
    else if((flags -> flgr0 >> 6) & 1)//cell 4
        flagged = 4;
    else if((flags -> flgr1 >> 0) & 1)//cell 5
        flagged = 5;
    else if((flags -> flgr1 >> 2) & 1)//cell 6
        flagged = 6;
    else if((flags -> flgr1 >> 4) & 1)//cell 7
        flagged = 7;
    else if((flags -> flgr1 >> 6) & 1)//cell 8
        flagged = 8;
    else if((flags -> flgr2 >> 0) & 1)//cell 9
        flagged = 9;
    else if((flags -> flgr2 >> 2) & 1)//cell 10
        flagged = 10;
    else if((flags -> flgr2 >> 4) & 1)//cell 11
        flagged = 11;
    else if((flags -> flgr2 >> 6) & 1)//cell 12
        flagged = 12;
        
    return(flagged);
}

uint8_t checkOV(flagRegisterStruct * flags)
{
    uint8_t flagged = ALL_FLAGS_CLEAR;
    
    if((flags -> flgr0 >> 1) & 1)//cell 1
        flagged = 1;
    else if((flags -> flgr0 >> 3) & 1)//cell 2
        flagged = 2;
    else if((flags -> flgr0 >> 5) & 1)//cell 3
        flagged = 3;
    else if((flags -> flgr0 >> 7) & 1)//cell 4
        flagged = 4;
    else if((flags -> flgr1 >> 1) & 1)//cell 5
        flagged = 5;
    else if((flags -> flgr1 >> 3) & 1)//cell 6
        flagged = 6;
    else if((flags -> flgr1 >> 5) & 1)//cell 7
        flagged = 7;
    else if((flags -> flgr1 >> 7) & 1)//cell 8
        flagged = 8;
    else if((flags -> flgr2 >> 1) & 1)//cell 9
        flagged = 9;
    else if((flags -> flgr2 >> 3) & 1)//cell 10
        flagged = 10;
    else if((flags -> flgr2 >> 5) & 1)//cell 11
        flagged = 11;
    else if((flags -> flgr2 >> 7) & 1)//cell 12
        flagged = 12;
        
    return(flagged);
}

uint8_t checkUVOnly10(flagRegisterStruct * flags)
{
    uint8_t flagged = ALL_FLAGS_CLEAR;
    
    if((flags -> flgr0 >> 0) & 1)//cell 1
        flagged = 1;
    else if((flags -> flgr0 >> 2) & 1)//cell 2
        flagged = 2;
    else if((flags -> flgr0 >> 4) & 1)//cell 3
        flagged = 3;
    else if((flags -> flgr0 >> 6) & 1)//cell 4
        flagged = 4;
    else if((flags -> flgr1 >> 0) & 1)//cell 5
        flagged = 5;
    else if((flags -> flgr1 >> 2) & 1)//cell 6
        flagged = 6;
    else if((flags -> flgr1 >> 4) & 1)//cell 7
        flagged = 7;
    else if((flags -> flgr1 >> 6) & 1)//cell 8
        flagged = 8;
    else if((flags -> flgr2 >> 0) & 1)//cell 9
        flagged = 9;
    else if((flags -> flgr2 >> 2) & 1)//cell 10
        flagged = 10;
        
    return(flagged);
}

uint8_t checkOVOnly10(flagRegisterStruct * flags)
{
    uint8_t flagged = ALL_FLAGS_CLEAR;
    
    if((flags -> flgr0 >> 1) & 1)//cell 1
        flagged = 1;
    else if((flags -> flgr0 >> 3) & 1)//cell 2
        flagged = 2;
    else if((flags -> flgr0 >> 5) & 1)//cell 3
        flagged = 3;
    else if((flags -> flgr0 >> 7) & 1)//cell 4
        flagged = 4;
    else if((flags -> flgr1 >> 1) & 1)//cell 5
        flagged = 5;
    else if((flags -> flgr1 >> 3) & 1)//cell 6
        flagged = 6;
    else if((flags -> flgr1 >> 5) & 1)//cell 7
        flagged = 7;
    else if((flags -> flgr1 >> 7) & 1)//cell 8
        flagged = 8;
    else if((flags -> flgr2 >> 1) & 1)//cell 9
        flagged = 9;
    else if((flags -> flgr2 >> 3) & 1)//cell 10
        flagged = 10;
        
    return(flagged);
}

uint8_t checkForLevelPoll(void * ptrToGPIOPin)
{
    if(GPIOCheck(ptrToGPIOPin) == 0) //line will be low if polling
        return 1;
    else
        return 0;
}

void readIn(uint8_t buffer[], uint8_t byteCount)
{
    int i;
    for(i = 0; i < byteCount; i++)
    {
        buffer[i] = serialIn();
    }
}

void computeRegisterToVolt(uint8_t buffer[], cellVoltageStruct * cellVolts, uint8_t count)
{
    uint16_t temp1, temp2;
    
    if(count == VOLT_REGISTERS_COMP_ALL || count == VOLT_REGISTERS_COMP_A)
    {
        temp1 = (uint16_t)buffer[1];
        temp2 = (uint16_t)buffer[0];
        temp1 &= 0x000F; //first byte and first half of second byte represent voltage 1
        temp2 &= 0x00FF;
        cellVolts -> cell1Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[1];
        temp2 = (uint16_t)buffer[2];
        temp1 &= 0x00F0;//third byte and second half of second byte represent voltage 2
        temp2 &= 0x00FF;
        cellVolts -> cell2Voltage = (temp1 >> 4) + (temp2 << 4);
        
        temp1 = (uint16_t)buffer[4];
        temp2 = (uint16_t)buffer[3];
        temp1 &= 0x000F; //and so on
        temp2 &= 0x00FF;
        cellVolts -> cell3Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[4];
        temp2 = (uint16_t)buffer[5];
        temp1 &= 0x00F0;//
        temp2 &= 0x00FF;
        cellVolts -> cell4Voltage = (temp1 >> 4) + (temp2 << 4);
    }
    
    if(count == VOLT_REGISTERS_COMP_ALL || count == VOLT_REGISTERS_COMP_B)
    {
        temp1 = (uint16_t)buffer[7];
        temp2 = (uint16_t)buffer[6];
        temp1 &= 0x000F; //
        temp2 &= 0x00FF;
        cellVolts -> cell5Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[7];
        temp2 = (uint16_t)buffer[8];
        temp1 &= 0x00F0;//
        temp2 &= 0x00FF;
        cellVolts -> cell6Voltage = (temp1 >> 4) + (temp2 << 4);
        
        temp1 = (uint16_t)buffer[10];
        temp2 = (uint16_t)buffer[9];
        temp1 &= 0x000F; //
        temp2 &= 0x00FF;
        cellVolts -> cell7Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[10];
        temp2 = (uint16_t)buffer[11];
        temp1 &= 0x00F0;//
        temp2 &= 0x00FF;
        cellVolts -> cell8Voltage = (temp1 >> 4) + (temp2 << 4);
    }
    
    if(count == VOLT_REGISTERS_COMP_ALL || count == VOLT_REGISTERS_COMP_C)
    {
        temp1 = (uint16_t)buffer[13];
        temp2 = (uint16_t)buffer[12];
        temp1 &= 0x000F; //
        temp2 &= 0x00FF;
        cellVolts -> cell9Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[13];
        temp2 = (uint16_t)buffer[14];
        temp1 &= 0x00F0;//
        temp2 &= 0x00FF;
        cellVolts -> cell10Voltage = (temp1 >> 4) + (temp2 << 4);
        
        temp1 = (uint16_t)buffer[16];
        temp2 = (uint16_t)buffer[15];
        temp1 &= 0x000F; //
        temp2 &= 0x00FF;
        cellVolts -> cell11Voltage = (temp1 << 8) + temp2;
        
        temp1 = (uint16_t)buffer[16];
        temp2 = (uint16_t)buffer[17];
        temp1 &= 0x00F0;//
        temp2 &= 0x00FF;
        cellVolts -> cell12Voltage = (temp1 >> 4) + (temp2 << 4);
    }
}

void computeRegisterToTemperature(uint8_t buffer[], temperatureStruct * temperatures)
{
    uint16_t temp1, temp2;
    
    temp1 = (uint16_t)buffer[1];
    temp2 = (uint16_t)buffer[0];
    temp1 &= 0x000F; //first byte and first half of second byte represent temp 1
    temp2 &= 0x00FF;
    temperatures -> externalTemp1 = (temp1 << 8) + temp2;
    temp1 = (uint16_t)buffer[1];
    temp2 = (uint16_t)buffer[2];
    temp1 &= 0x00F0;//third byte and second half of second byte represent temp 2
    temp2 &= 0x00FF;
    temperatures -> externalTemp2 = (temp1 >> 4) + (temp2 << 4);
    
    temp1 = (uint16_t)buffer[4];
    temp2 = (uint16_t)buffer[3];
    temp1 &= 0x000F; //and so on
    temp2 &= 0x00FF;
    temperatures -> internalTemp = (temp1 << 8) + temp2;
    
    temp1 = buffer[4];//masks R4[4], which is the Shutdown flag, then saves it to the struct
    temp1 &= 0b00010000;
    if(temp1 > 0)
        temp2 = 1;
    else
        temp2 = 0;
        
    temperatures -> thermalShutdownFlag = temp2;
    
}

void computeRegisterToDiagnostic(uint8_t buffer[], diagnosticStruct * diags)
{
    uint16_t temp1, temp2;
        
    temp1 = (uint16_t)buffer[1];
    temp2 = (uint16_t)buffer[0];
    temp1 &= 0x000F; //first byte and first half of second byte represent ref voltage
    temp2 &= 0x00FF;
    diags -> refVolt = (temp1 << 8) + temp2;
    
    diags -> revisionCode = ((buffer[1] & 0b11000000) >> 6);
    
    diags -> muxfail = ((buffer[1] & 0b00100000) >> 5);
}


uint8_t makeAddressPEC(uint8_t message)
{
    uint8_t temp, pec = 0b01000001;
    bool in0, in1, in2, bIn;
    
    int i;
    for(i = 0; i < 8; i++)
    {
        temp = message << i;
        bIn = ((temp >> EIGHTH_BIT_SHIFT) & 1); //message[7] = bIn (will recieve MSB first on recieving end)
        in0 = bIn ^ ((pec >> EIGHTH_BIT_SHIFT) & 1); //pec[7] ^ bIn = in0
        in1 = in0 ^ ((pec >> FIRST_BIT_SHIFT) & 1); //pec[0] ^ in0 = in1
        in2 = in0 ^ ((pec >> SECOND_BIT_SHIFT) & 1); //pec[1] ^ in0 = in2
        
        pec = pec << 1; //p7 = p6, p6 = p5, p5 = p4...p1 = p0, p0 = 0;
        
        if(in2)
            pec |= 0b00000100;
        else
            pec &= 0b11111011;//pec[2] = in2
        if(in1)
            pec |= 0b00000010;
        else
            pec &= 0b11111101;//pec[1] = in1
        if(in0)
            pec |= 0b00000001;
        else
            pec &= 0b11111110;//pec[0] = in0
        
    }
    
    return(pec);
}

uint8_t makeConfigStructPEC(cfgRegisterStruct * cfgRegister)
{
    uint64_t message = 0;
    uint8_t temp, pec = 0b01000001;
    bool in0, in1, in2, bIn;

    message += cfgRegister -> cfgr0;
    message += ((uint64_t)(cfgRegister -> cfgr1) << (8 * 1));
    message += ((uint64_t)(cfgRegister -> cfgr2) << (8 * 2));
    message += ((uint64_t)(cfgRegister -> cfgr3) << (8 * 3));
    message += ((uint64_t)(cfgRegister -> cfgr4) << (8 * 4));
    message += ((uint64_t)(cfgRegister -> cfgr5) << (8 * 5));
    
    int i;
    for(i = 0; i < CFG_REG_STRUCT_BIT_COUNT; i++)
    {	
        temp = message << i;
		bIn = ((temp >> FOURTYEIGHTH_BIT_SHIFT) & 1); //message[47] = bIn (will recieve MSB first on recieving end)
		in0 = bIn ^ ((pec >> EIGHTH_BIT_SHIFT) & 1); //pec[7] ^ bIn = in0
		in1 = in0 ^ ((pec >> FIRST_BIT_SHIFT) & 1); //pec[0] ^ in0 = in1
		in2 = in0 ^ ((pec >> SECOND_BIT_SHIFT) & 1); //pec[1] ^ in0 = in2
		
		pec = pec << 1; //p7 = p6, p6 = p5, p5 = p4...p1 = p0, p0 = 0;
		
		if(in2)
		    pec |= 0b00000100;
		else
		    pec &= 0b11111011;//pec[2] = in2
		if(in1)
		    pec |= 0b00000010;
		else
		    pec &= 0b11111101;//pec[1] = in1
		if(in0)
		    pec |= 0b00000001;
		else
		    pec &= 0b11111110;//pec[0] = in0
        
    }
    
    return(pec);
}

uint8_t encodeAddress(uint8_t address)
{
    address &= 0b00001111; //ensuring that address has only first 4 bits
    address += 0b10000000; //adding on '1000' to the front. '1000xxxx' is keyword for addressing
    return(address);
}

uint8_t serialIn()
{
    uint8_t x; //insert hardware specific code here
    return x;
}

void serialOut(uint8_t message)
{
    int x; //insert hardware specific code here
}

uint8_t GPIOCheck(void * ptrToGPIOPin)
{
    int x; //insert hardware specific code here
    return x;
}