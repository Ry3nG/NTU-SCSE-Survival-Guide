// FlashProgram.c
// Runs on MSP432
// Provide functions that initialize the flash memory, write
// 32-bit data to flash, write an array of 32-bit data to flash,
// and erase a 4 KB block.
// Daniel Valvano
// May 11, 2016

/* This example accompanies the book
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

#include <stdint.h>
#include "FlashProgram.h"

#define FLASH_BANK0_MIN     0x00000000  // Flash Bank0 minimum address
#define FLASH_BANK0_MAX     0x0001FFFF  // Flash Bank0 maximum address
#define FLASH_BANK1_MIN     0x00020000  // Flash Bank1 minimum address
#define FLASH_BANK1_MAX     0x0003FFFF  // Flash Bank1 maximum address
#define FLASH_OFFSET_MAX    0x0003FFFF  // Address Offset max
#define MAX_PRG_PLS_TLV 5               // from Flash.c
#define MAX_ERA_PLS_TLV 50              // from Flash.c
#define FLCTL_POWER_STAT                                   (*((volatile uint32_t *)(0x40011000))) /* Power Status Register */
#define FLCTL_BANK0_RDCTL                                  (*((volatile uint32_t *)(0x40011010))) /* Bank0 Read Control Register */
#define FLCTL_BANK1_RDCTL                                  (*((volatile uint32_t *)(0x40011014))) /* Bank1 Read Control Register */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M                 (0x000f0000)          /* Read mode */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0                 (0x00000000)          /* Normal read mode */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_1                 (0x00010000)          /* Read Margin 0 */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_2                 (0x00020000)          /* Read Margin 1 */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_3                 (0x00030000)          /* Program Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_4                 (0x00040000)          /* Erase Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_5                 (0x00050000)          /* Leakage Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_9                 (0x00090000)          /* Read Margin 0B */
#define FLCTL_BANK1_RDCTL_RD_MODE_STATUS_10                (0x000a0000)          /* Read Margin 1B */
#define FLCTL_BANK1_RDCTL_WAIT_M                           (0x0000f000)          /* Number of wait states for read */
#define FLCTL_BANK1_RDCTL_WAIT_0                           (0x00000000)          /* 0 wait states */
#define FLCTL_BANK1_RDCTL_WAIT_1                           (0x00001000)          /* 1 wait states */
#define FLCTL_BANK1_RDCTL_WAIT_2                           (0x00002000)          /* 2 wait states */
#define FLCTL_BANK1_RDCTL_WAIT_3                           (0x00003000)          /* 3 wait states */
#define FLCTL_BANK1_RDCTL_WAIT_4                           (0x00004000)          /* 4 wait states */
#define FLCTL_BANK1_RDCTL_WAIT_5                           (0x00005000)          /* 5 wait states */
#define FLCTL_BANK1_RDCTL_RD_MODE_M                        (0x0000000f)          /* Flash read mode control setting for Bank 0 */
#define FLCTL_BANK1_RDCTL_RD_MODE_0                        (0x00000000)          /* Normal read mode */
#define FLCTL_BANK1_RDCTL_RD_MODE_1                        (0x00000001)          /* Read Margin 0 */
#define FLCTL_BANK1_RDCTL_RD_MODE_2                        (0x00000002)          /* Read Margin 1 */
#define FLCTL_BANK1_RDCTL_RD_MODE_3                        (0x00000003)          /* Program Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_4                        (0x00000004)          /* Erase Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_5                        (0x00000005)          /* Leakage Verify */
#define FLCTL_BANK1_RDCTL_RD_MODE_9                        (0x00000009)          /* Read Margin 0B */
#define FLCTL_BANK1_RDCTL_RD_MODE_10                       (0x0000000a)          /* Read Margin 1B */
#define FLCTL_RDBRST_CTLSTAT                               (*((volatile uint32_t *)(0x40011020))) /* Read Burst/Compare Control and Status Register */
#define FLCTL_RDBRST_CTLSTAT_CLR_STAT                      (0x00800000)          /* Clear status bits 19-16 of this register */
#define FLCTL_RDBRST_CTLSTAT_TEST_EN                       (0x00000040)          /* Enable comparison against test data compare registers */
#define FLCTL_RDBRST_CTLSTAT_DATA_CMP                      (0x00000010)          /* Data pattern used for comparison against memory read data */
#define FLCTL_RDBRST_CTLSTAT_STOP_FAIL                     (0x00000008)          /* Terminate burst/compare operation */
#define FLCTL_RDBRST_CTLSTAT_MEM_TYPE_M                    (0x00000006)          /* Type of memory that burst is carried out on */
#define FLCTL_RDBRST_CTLSTAT_MEM_TYPE_0                    (0x00000000)          /* Main Memory */
#define FLCTL_RDBRST_CTLSTAT_MEM_TYPE_1                    (0x00000002)          /* Information Memory */
#define FLCTL_RDBRST_CTLSTAT_MEM_TYPE_2                    (0x00000004)          /* Reserved */
#define FLCTL_RDBRST_CTLSTAT_MEM_TYPE_3                    (0x00000006)          /* Engineering Memory */
#define FLCTL_RDBRST_CTLSTAT_START                         (0x00000001)          /* Start of burst/compare operation */
#define FLCTL_RDBRST_STARTADDR                             (*((volatile uint32_t *)(0x40011024))) /* Read Burst/Compare Start Address Register */
#define FLCTL_RDBRST_LEN                                   (*((volatile uint32_t *)(0x40011028))) /* Read Burst/Compare Length Register */
#define FLCTL_RDBRST_FAILADDR                              (*((volatile uint32_t *)(0x4001103C))) /* Read Burst/Compare Fail Address Register */
#define FLCTL_RDBRST_FAILCNT                               (*((volatile uint32_t *)(0x40011040))) /* Read Burst/Compare Fail Count Register */
#define FLCTL_PRG_CTLSTAT                                  (*((volatile uint32_t *)(0x40011050))) /* Program Control and Status Register */
#define FLCTL_PRG_CTLSTAT_STATUS_M                         (0x00030000)          /* Status of program operations in the Flash memory */
#define FLCTL_PRG_CTLSTAT_STATUS_0                         (0x00000000)          /* Idle (no program operation currently active) */
#define FLCTL_PRG_CTLSTAT_VER_PST                          (0x00000008)          /* Controls automatic post program verify operations */
#define FLCTL_PRG_CTLSTAT_VER_PRE                          (0x00000004)          /* Controls automatic pre program verify operations */
#define FLCTL_PRG_CTLSTAT_MODE                             (0x00000002)          /* Write mode */
#define FLCTL_PRG_CTLSTAT_ENABLE                           (0x00000001)          /* Master control for all word program operations */
#define FLCTL_PRGBRST_CTLSTAT                              (*((volatile uint32_t *)(0x40011054))) /* Program Burst Control and Status Register */
#define FLCTL_PRGBRST_CTLSTAT_CLR_STAT                     (0x00800000)          /* Clear status bits 21-16 of this register */
#define FLCTL_PRGBRST_CTLSTAT_ADDR_ERR                     (0x00200000)          /* Burst Operation was terminated due to attempted program of reserved memory */
#define FLCTL_PRGBRST_CTLSTAT_PST_ERR                      (0x00100000)          /* Burst Operation encountered postprogram auto-verify errors */
#define FLCTL_PRGBRST_CTLSTAT_PRE_ERR                      (0x00080000)          /* Burst Operation encountered preprogram auto-verify errors */
#define FLCTL_PRGBRST_CTLSTAT_AUTO_PST                     (0x00000080)          /* Auto-Verify operation after the Burst Program */
#define FLCTL_PRGBRST_CTLSTAT_AUTO_PRE                     (0x00000040)          /* Auto-Verify operation before the Burst Program */
#define FLCTL_PRGBRST_CTLSTAT_LEN_OFS                      ( 3)                  /* LEN Offset */
#define FLCTL_PRGBRST_CTLSTAT_LEN_M                        (0x00000038)          /* Length of burst */
#define FLCTL_PRGBRST_CTLSTAT_LEN_0                        (0x00000000)          /* No burst operation */
#define FLCTL_PRGBRST_CTLSTAT_LEN_1                        (0x00000008)          /* 1 word burst of 128 bits, starting with address in the FLCTL_PRGBRST_STARTADDR Register */
#define FLCTL_PRGBRST_CTLSTAT_LEN_2                        (0x00000010)          /* 2*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register */
#define FLCTL_PRGBRST_CTLSTAT_LEN_3                        (0x00000018)          /* 3*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register */
#define FLCTL_PRGBRST_CTLSTAT_LEN_4                        (0x00000020)          /* 4*128 bits burst write, starting with address in the FLCTL_PRGBRST_STARTADDR Register */
#define FLCTL_PRGBRST_CTLSTAT_TYPE_M                       (0x00000006)          /* Type of memory that burst program is carried out on */
#define FLCTL_PRGBRST_CTLSTAT_TYPE_0                       (0x00000000)          /* Main Memory */
#define FLCTL_PRGBRST_CTLSTAT_TYPE_1                       (0x00000002)          /* Information Memory */
#define FLCTL_PRGBRST_CTLSTAT_TYPE_2                       (0x00000004)          /* Reserved */
#define FLCTL_PRGBRST_CTLSTAT_TYPE_3                       (0x00000006)          /* Engineering Memory */
#define FLCTL_PRGBRST_CTLSTAT_START                        (0x00000001)          /* Trigger start of burst program operation */
#define FLCTL_PRGBRST_STARTADDR                            (*((volatile uint32_t *)(0x40011058))) /* Program Burst Start Address Register */
#define FLCTL_PRGBRST_DATA0_0                              (*((volatile uint32_t *)(0x40011060))) /* Program Burst Data0 Register0 */
#define FLCTL_PRGBRST_DATA0_1                              (*((volatile uint32_t *)(0x40011064))) /* Program Burst Data0 Register1 */
#define FLCTL_PRGBRST_DATA0_2                              (*((volatile uint32_t *)(0x40011068))) /* Program Burst Data0 Register2 */
#define FLCTL_PRGBRST_DATA0_3                              (*((volatile uint32_t *)(0x4001106C))) /* Program Burst Data0 Register3 */
#define FLCTL_PRGBRST_DATA1_0                              (*((volatile uint32_t *)(0x40011070))) /* Program Burst Data1 Register0 */
#define FLCTL_PRGBRST_DATA1_1                              (*((volatile uint32_t *)(0x40011074))) /* Program Burst Data1 Register1 */
#define FLCTL_PRGBRST_DATA1_2                              (*((volatile uint32_t *)(0x40011078))) /* Program Burst Data1 Register2 */
#define FLCTL_PRGBRST_DATA1_3                              (*((volatile uint32_t *)(0x4001107C))) /* Program Burst Data1 Register3 */
#define FLCTL_PRGBRST_DATA2_0                              (*((volatile uint32_t *)(0x40011080))) /* Program Burst Data2 Register0 */
#define FLCTL_PRGBRST_DATA2_1                              (*((volatile uint32_t *)(0x40011084))) /* Program Burst Data2 Register1 */
#define FLCTL_PRGBRST_DATA2_2                              (*((volatile uint32_t *)(0x40011088))) /* Program Burst Data2 Register2 */
#define FLCTL_PRGBRST_DATA2_3                              (*((volatile uint32_t *)(0x4001108C))) /* Program Burst Data2 Register3 */
#define FLCTL_PRGBRST_DATA3_0                              (*((volatile uint32_t *)(0x40011090))) /* Program Burst Data3 Register0 */
#define FLCTL_PRGBRST_DATA3_1                              (*((volatile uint32_t *)(0x40011094))) /* Program Burst Data3 Register1 */
#define FLCTL_PRGBRST_DATA3_2                              (*((volatile uint32_t *)(0x40011098))) /* Program Burst Data3 Register2 */
#define FLCTL_PRGBRST_DATA3_3                              (*((volatile uint32_t *)(0x4001109C))) /* Program Burst Data3 Register3 */
#define FLCTL_ERASE_CTLSTAT                                (*((volatile uint32_t *)(0x400110A0))) /* Erase Control and Status Register */
#define FLCTL_ERASE_CTLSTAT_CLR_STAT                       (0x00080000)          /* Clear status bits 18-16 of this register */
#define FLCTL_ERASE_CTLSTAT_ADDR_ERR                       (0x00040000)          /* Erase Operation was terminated due to attempted erase of reserved memory address */
#define FLCTL_ERASE_CTLSTAT_STATUS_M                       (0x00030000)          /* Status of erase operations in the Flash memory */
#define FLCTL_ERASE_CTLSTAT_STATUS_0                       (0x00000000)          /* Idle (no program operation currently active) */
#define FLCTL_ERASE_CTLSTAT_STATUS_1                       (0x00010000)          /* Erase operation triggered to START but pending */
#define FLCTL_ERASE_CTLSTAT_STATUS_2                       (0x00020000)          /* Erase operation in progress */
#define FLCTL_ERASE_CTLSTAT_STATUS_3                       (0x00030000)          /* Erase operation completed (status of completed erase remains in this state unless explicitly cleared by SW) */
#define FLCTL_ERASE_CTLSTAT_TYPE_M                         (0x0000000C)          /* Type of memory that erase operation is carried out on */
#define FLCTL_ERASE_CTLSTAT_TYPE_0                         (0x00000000)          /* Main Memory */
#define FLCTL_ERASE_CTLSTAT_TYPE_1                         (0x00000004)          /* Information Memory */
#define FLCTL_ERASE_CTLSTAT_TYPE_2                         (0x00000008)          /* Reserved */
#define FLCTL_ERASE_CTLSTAT_TYPE_3                         (0x0000000C)          /* Engineering Memory */
#define FLCTL_ERASE_CTLSTAT_MODE                           (0x00000002)          /* Erase mode selected by application */
#define FLCTL_ERASE_CTLSTAT_START                          (0x00000001)          /* Start of Erase operation */
#define FLCTL_ERASE_SECTADDR                               (*((volatile uint32_t *)(0x400110A4))) /* Erase Sector Address Register */
#define FLCTL_BANK0_INFO_WEPROT                            (*((volatile uint32_t *)(0x400110B0))) /* Information Memory Bank0 Write/Erase Protection Register */
#define FLCTL_BANK0_MAIN_WEPROT                            (*((volatile uint32_t *)(0x400110B4))) /* Main Memory Bank0 Write/Erase Protection Register */
#define FLCTL_BANK1_INFO_WEPROT                            (*((volatile uint32_t *)(0x400110C0))) /* Information Memory Bank1 Write/Erase Protection Register */
#define FLCTL_BANK1_MAIN_WEPROT                            (*((volatile uint32_t *)(0x400110C4))) /* Main Memory Bank1 Write/Erase Protection Register */
#define FLCTL_BMRK_CTLSTAT                                 (*((volatile uint32_t *)(0x400110D0))) /* Benchmark Control and Status Register */
#define FLCTL_BMRK_IFETCH                                  (*((volatile uint32_t *)(0x400110D4))) /* Benchmark Instruction Fetch Count Register */
#define FLCTL_BMRK_DREAD                                   (*((volatile uint32_t *)(0x400110D8))) /* Benchmark Data Read Count Register */
#define FLCTL_BMRK_CMP                                     (*((volatile uint32_t *)(0x400110DC))) /* Benchmark Count Compare Register */
#define FLCTL_IFG                                          (*((volatile uint32_t *)(0x400110F0))) /* Interrupt Flag Register */
#define FLCTL_IFG_PRG_ERR                                  (0x00000200)          /*  */
#define FLCTL_IFG_ERASE                                    (0x00000020)          /*  */
#define FLCTL_IFG_PRGB                                     (0x00000010)          /*  */
#define FLCTL_IFG_PRG                                      (0x00000008)          /*  */
#define FLCTL_IFG_AVPST                                    (0x00000004)          /*  */
#define FLCTL_IFG_AVPRE                                    (0x00000002)          /*  */
#define FLCTL_IFG_RDBRST                                   (0x00000001)          /*  */
#define FLCTL_IE                                           (*((volatile uint32_t *)(0x400110F4))) /* Interrupt Enable Register */
#define FLCTL_CLRIFG                                       (*((volatile uint32_t *)(0x400110F8))) /* Clear Interrupt Flag Register */
#define FLCTL_CLRIFG_PRG_ERR                               (0x00000200)          /*  */
#define FLCTL_CLRIFG_ERASE                                 (0x00000020)          /*  */
#define FLCTL_CLRIFG_PRGB                                  (0x00000010)          /*  */
#define FLCTL_CLRIFG_PRG                                   (0x00000008)          /*  */
#define FLCTL_CLRIFG_AVPST                                 (0x00000004)          /*  */
#define FLCTL_CLRIFG_AVPRE                                 (0x00000002)          /*  */
#define FLCTL_CLRIFG_RDBRST                                (0x00000001)          /*  */
#define FLCTL_SETIFG                                       (*((volatile uint32_t *)(0x400110FC))) /* Set Interrupt Flag Register */
#define FLCTL_READ_TIMCTL                                  (*((volatile uint32_t *)(0x40011100))) /* Read Timing Control Register */
#define FLCTL_READMARGIN_TIMCTL                            (*((volatile uint32_t *)(0x40011104))) /* Read Margin Timing Control Register */
#define FLCTL_PRGVER_TIMCTL                                (*((volatile uint32_t *)(0x40011108))) /* Program Verify Timing Control Register */
#define FLCTL_ERSVER_TIMCTL                                (*((volatile uint32_t *)(0x4001110C))) /* Erase Verify Timing Control Register */
#define FLCTL_LKGVER_TIMCTL                                (*((volatile uint32_t *)(0x40011110))) /* Leakage Verify Timing Control Register */
#define FLCTL_PROGRAM_TIMCTL                               (*((volatile uint32_t *)(0x40011114))) /* Program Timing Control Register */
#define FLCTL_ERASE_TIMCTL                                 (*((volatile uint32_t *)(0x40011118))) /* Erase Timing Control Register */
#define FLCTL_MASSERASE_TIMCTL                             (*((volatile uint32_t *)(0x4001111C))) /* Mass Erase Timing Control Register */
#define FLCTL_BURSTPRG_TIMCTL                              (*((volatile uint32_t *)(0x40011120))) /* Burst Program Timing Control Register */

// Check if address offset is valid for write operation
// Writing addresses must be 4-byte aligned and within range
static int WriteAddrValid(uint32_t addr){
  // check if address offset works for writing
  // must be 4-byte aligned
  return (((addr % 4) == 0) && (addr <= FLASH_OFFSET_MAX));
}
// Check if address offset is valid for mass writing operation
// Mass writing addresses must be 4-word (16-byte) aligned and within range
static int MassWriteAddrValid(uint32_t addr, uint16_t count){
  // check if address offset works for mass writing
  // must be 4-word (16-byte) aligned
  return (((addr % 16) == 0) && (addr <= FLASH_OFFSET_MAX) && ((addr + 4*count - 1) <= FLASH_OFFSET_MAX));
}
// Check if address offset is valid for erase operation
// Erasing addresses must be 4 KB aligned and within range
static int EraseAddrValid(uint32_t addr){
  // check if address offset works for erasing
  // must be 4 KB aligned
  return (((addr % 4096) == 0) && (addr <= FLASH_OFFSET_MAX));
}
// Check if address is in flash Bank 0
static int IsInBank0(uint32_t addr){
#if (FLASH_BANK0_MIN == 0)
  // Get rid of compiler warning by eliminating pointless unsigned compare with 0.
  return (addr <= FLASH_BANK0_MAX);
#else
  return ((FLASH_BANK0_MIN <= addr) && (addr <= FLASH_BANK0_MAX));
#endif
}
// Check if address is in flash Bank 1
static int IsInBank1(uint32_t addr){
  return ((FLASH_BANK1_MIN <= addr) && (addr <= FLASH_BANK1_MAX));
}

//------------Flash_Init------------
// This function was critical to the write and erase
// operations of the flash memory on the LM3S811
// microcontroller.  But newer processors work slightly
// differently, and for the MSP432 the timing parameters
// for the flash and EEPROM memories are configured along
// with the Clock System.  This function prototype is
// preserved to try to make it easier to reuse program
// code between the LM3S811, TM4C123, and TM4C1294.
// Input: systemClockFreqMHz  system clock frequency (units of MHz)
// Output: none
void Flash_Init(uint8_t systemClockFreqMHz){
  // do nothing; flash and EEPROM memory configured in Clock
  // System or BSP_Clock_InitFastest() initialization functions
  // if the processor is executing code out of flash memory,
  // presumably everything is configured correctly
}

//------------Flash_Write------------
// Write 32-bit data to flash at given address.  Parameter
// 'addr' must be in flash Bank 1, and this function must be in
// flash Bank 0.
// Input: addr 4-byte aligned flash memory address to write
//        data 32-bit data
// Output: 'NOERROR' if successful, 'ERROR' if fail (defined in FlashProgram.h)
// Note: This function is not interrupt safe.
int Flash_Write(uint32_t addr, uint32_t data){
  uint32_t lockStatus, lockMask, numPrgPulses, tempVar, existingData, actualData, failBits, updatedData;
  if((IsInBank0(addr)) || (IsInBank1((int)&Flash_Write))){
    // This function and the flash to be written are in the same bank.
    // Because we cannot change the read mode of the flash that contains
    // the currently running code, we need to either copy this function
    // to RAM or use one of the library functions in ROM.
                 // to do later: fix this
    return ERROR;
  }
  if(WriteAddrValid(addr)){
    // Unlock the block in Flash Main Memory Bank 1.
    lockMask = 1<<((addr - FLASH_BANK1_MIN)>>12);   // 0x00000001 to 0x80000000
    lockStatus = FLCTL_BANK1_MAIN_WEPROT&lockMask;  // save previous value
    FLCTL_BANK1_MAIN_WEPROT = (FLCTL_BANK1_MAIN_WEPROT&~lockMask);
    // Clear pending PRG, PRG_ERR, AVPST, and AVPRE interrupt flags.
    FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
    // Enable immediate program operation.  (ENABLE = 1, MODE = 0 in FLCTL_PRG_CTLSTAT)
    FLCTL_PRG_CTLSTAT |= FLCTL_PRG_CTLSTAT_ENABLE;  // configure for word program operation enabled
    FLCTL_PRG_CTLSTAT &= ~FLCTL_PRG_CTLSTAT_MODE;   // configure for write immediate mode
    // Keep track of the number of programming pulses.
    numPrgPulses = 0;
    // Location to be programmed may not already be erased.
    // Enable Pre and Post Verify option.
    FLCTL_PRG_CTLSTAT |= (FLCTL_PRG_CTLSTAT_VER_PST|FLCTL_PRG_CTLSTAT_VER_PRE);
    // Store data to be programmed ('data') in a temporary variable.
    // This is to prevent the accidental loss of data to be programmed.
    tempVar = data;
    // Initiate data write to the desired flash address with 'data'.
    *(volatile uint32_t *)addr = tempVar;           // writes to flash work like writes to RAM
    // Wait for the programming to complete.
    while((FLCTL_IFG&FLCTL_IFG_PRG) == 0){
                 // to do later: return ERROR if this takes too long
    }
    // Increment programming pulses used.
    numPrgPulses = numPrgPulses + 1;
    while((FLCTL_IFG&FLCTL_IFG_AVPRE) || (FLCTL_IFG&FLCTL_IFG_AVPST)){
      // Check for pre-program verify error.
      if(FLCTL_IFG&FLCTL_IFG_AVPRE){
        // Check if exceeded maximum number of programming pulses.
        if(numPrgPulses > MAX_PRG_PLS_TLV){
          // Clear all error flags in FLCTL_CLRIFG register.
          FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
          // Recall lock status of the block in Flash Main Memory Bank 1.
          FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
          return ERROR;
        }
        // At least one bit was already 0 before programming started.
        // The flash to be written is in Bank 1.
        // Configure for 5 wait states (minimum for 48 MHz operation) and for read mode of Program Verify.
        FLCTL_BANK1_RDCTL = FLCTL_BANK1_RDCTL_WAIT_5|FLCTL_BANK1_RDCTL_RD_MODE_3;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_3){};
        existingData = *(volatile uint32_t *)addr;
        failBits = ~(existingData|tempVar);
        updatedData = tempVar|failBits;             // see Page 378 of MSP432 Datasheet
        // Configure for read mode of Normal Read.
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_RD_MODE_M)|FLCTL_BANK1_RDCTL_RD_MODE_0;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0){};
        // Configure for 2 wait states (minimum for 48 MHz operation).
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_WAIT_M)|FLCTL_BANK1_RDCTL_WAIT_2;
        // Clear all error flags in FLCTL_CLRIFG register.
        FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
        // Check if some bits still need to be written.
        if(updatedData != 0xFFFFFFFF){
          // Enable Post Verify option.
          FLCTL_PRG_CTLSTAT |= FLCTL_PRG_CTLSTAT_VER_PST;
          // Pre Verify not needed since failing bits already masked.
          FLCTL_PRG_CTLSTAT &= ~FLCTL_PRG_CTLSTAT_VER_PRE;
          // Initiate data write to the desired flash address with 'updatedData'.
          *(volatile uint32_t *)addr = updatedData; // writes to flash work like writes to RAM
          // Wait for the programming to complete.
          while((FLCTL_IFG&FLCTL_IFG_PRG) == 0){
                 // to do later: return ERROR if this takes too long
          }
          // Increment programming pulses used.
          numPrgPulses = numPrgPulses + 1;
        }
      }
      // Check for post-program verify error.
      if(FLCTL_IFG&FLCTL_IFG_AVPST){
        // Check if exceeded maximum number of programming pulses.
        if(numPrgPulses > MAX_PRG_PLS_TLV){
          // Clear all error flags in FLCTL_CLRIFG register.
          FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
          // Recall lock status of the block in Flash Main Memory Bank 1.
          FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
          return ERROR;
        }
        // At least one bit was still 1 after programming finished.
        // The flash to be written is in Bank 1.
        // Configure for 5 wait states (minimum for 48 MHz operation) and for read mode of Program Verify.
        FLCTL_BANK1_RDCTL = FLCTL_BANK1_RDCTL_WAIT_5|FLCTL_BANK1_RDCTL_RD_MODE_3;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_3){};
        actualData = *(volatile uint32_t *)addr;
        failBits = (~tempVar)&actualData;
        updatedData = ~failBits;                    // see Page 379 of MSP432 Datasheet
        // Configure for read mode of Normal Read.
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_RD_MODE_M)|FLCTL_BANK1_RDCTL_RD_MODE_0;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0){};
        // Configure for 2 wait states (minimum for 48 MHz operation).
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_WAIT_M)|FLCTL_BANK1_RDCTL_WAIT_2;
        // Clear all error flags in FLCTL_CLRIFG register.
        FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
        // Check if some bits still need to be written.
        if(failBits != 0x00000000){
          // Enable Pre and Post Verify option.
          FLCTL_PRG_CTLSTAT |= (FLCTL_PRG_CTLSTAT_VER_PST|FLCTL_PRG_CTLSTAT_VER_PRE);
          // Initiate data write to the desired flash address with 'updatedData'.
          *(volatile uint32_t *)addr = updatedData; // writes to flash work like writes to RAM
          // Wait for the programming to complete.
          while((FLCTL_IFG&FLCTL_IFG_PRG) == 0){
                 // to do later: return ERROR if this takes too long
          }
          // Increment programming pulses used.
          numPrgPulses = numPrgPulses + 1;
        }
      }
    }
    // Clear all error flags in FLCTL_CLRIFG register.
    FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRG|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
    // Recall lock status of the block in Flash Main Memory Bank 1.
    FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
    return NOERROR;
  }
  return ERROR;
}

//------------Flash_WriteArray------------
// Write an array of 32-bit data to flash starting at given address.
// Parameter 'addr' must be in flash Bank 1.
// Input: source pointer to array of 32-bit data
//        addr   4-byte aligned flash memory address to start writing
//        count  number of 32-bit writes
// Output: number of successful writes; return value == count if completely successful
// Note: at 48 MHz, it takes 612 usec to write 10 words
// Note: This function is not interrupt safe.
int Flash_WriteArray(uint32_t *source, uint32_t addr, uint16_t count){
  uint16_t successfulWrites = 0;
  while((successfulWrites < count) && (Flash_Write(addr + 4*successfulWrites, source[successfulWrites]) == NOERROR)){
    successfulWrites = successfulWrites + 1;
  }
  return successfulWrites;
}

//------------Flash_FastWrite------------
// Write an array of 32-bit data to flash starting at given address.
// This is twice as fast as Flash_WriteArray(), but the address has
// to be 16-byte aligned, and the count has to be <= 16.  Parameter
// 'addr' must be in flash Bank 1, and this function must be in
// flash Bank 0.
// Input: source pointer to array of 32-bit data
//        addr   16-byte aligned flash memory address to start writing
//        count  number of 32-bit writes (<=16)
// Output: number of successful writes; return value == min(count, 16) if completely successful
// Note: at 48 MHz, it takes 97 usec to write 10 words
// Note: This function is not interrupt safe.
int Flash_FastWrite(uint32_t *source, uint32_t addr, uint16_t count){
  volatile uint32_t *FLCTL_PRGBRST_DATAn_x = (volatile uint32_t *)0x40011060; /* Program Burst Data0 Register0 */
  uint32_t lockStatus, lockMask, numPrgPulses, existingData, actualData, failBits[16], updatedData[16];
  int writes = 0, i;
  if((IsInBank0(addr)) || (IsInBank1((int)&Flash_FastWrite))){
    // This function and the flash to be written are in the same bank.
    // Because we cannot change the read mode of the flash that contains
    // the currently running code, we need to either copy this function
    // to RAM or use one of the library functions in ROM.
                 // to do later: fix this
    return 0;
  }
  if(count > 16){
    // Write a maximum of 16 32-bit words.
    count = 16;
  }
  if(MassWriteAddrValid(addr, count)){
    // Clear pending PRGB, PRG_ERR, AVPST, and AVPRE interrupt flags.
    FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
    // Keep track of the number of programming pulses.
    numPrgPulses = 0;
    // Clear any past errors and set status back to "idle".
    FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
    // Unlock the block in Flash Main Memory Bank 1.
    lockMask = 1<<((addr - FLASH_BANK1_MIN)>>12);   // 0x00000001 to 0x80000000
    // Make sure that the last memory location is also unlocked.
    lockMask |= 1<<((addr - FLASH_BANK1_MIN + 4*count - 1)>>12);
    lockStatus = FLCTL_BANK1_MAIN_WEPROT&lockMask;  // save previous value
    FLCTL_BANK1_MAIN_WEPROT = (FLCTL_BANK1_MAIN_WEPROT&~lockMask);
    // Write data to be programmed into the burst data registers.  (FLCTL_PRGBRST_DATAn_x)
    for(i=0; i<count; i=i+1){
      FLCTL_PRGBRST_DATAn_x[i] = source[i];
    }
    for(i=count; i<16; i=i+1){
      FLCTL_PRGBRST_DATAn_x[i] = 0xFFFFFFFF;
    }
    // Location to be programmed may not already be erased.
    // Enable Pre and Post Verify option.
    FLCTL_PRGBRST_CTLSTAT |= (FLCTL_PRGBRST_CTLSTAT_AUTO_PST|FLCTL_PRGBRST_CTLSTAT_AUTO_PRE);
    // Setup burst program operation in FLCTL_PRGBRST_CTLSTAT register.
    // TYPE = Main Memory
    // LEN = number of 128-bit bursts
    // count bursts LEN (bits 5-3)
    // 0     0      000b
    // 1     1      001b
    // 2     1      001b
    // 3     1      001b
    // 4     1      001b
    // 5     2      010b
    // 6     2      010b
    // 7     2      010b
    // 8     2      010b
    // 9     3      011b
    // 10    3      011b
    // 11    3      011b
    // 12    3      011b
    // 13    4      100b
    // 14    4      100b
    // 15    4      100b
    // 16    4      100b
    FLCTL_PRGBRST_CTLSTAT = (FLCTL_PRGBRST_CTLSTAT&~FLCTL_PRGBRST_CTLSTAT_TYPE_M)|FLCTL_PRGBRST_CTLSTAT_TYPE_0;
    FLCTL_PRGBRST_CTLSTAT = (FLCTL_PRGBRST_CTLSTAT&~FLCTL_PRGBRST_CTLSTAT_LEN_M)|(((count+3)/4)<<FLCTL_PRGBRST_CTLSTAT_LEN_OFS);
    // Setup start address of burst operation in FLCTL_PRGBRST_STARTADDR register.
    FLCTL_PRGBRST_STARTADDR = addr;
    // Start burst program operation by setting START bit in FLCTL_PRGBRST_CTLSTAT.
    FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_START;
    // Wait for the programming to complete.
    while((FLCTL_IFG&FLCTL_IFG_PRGB) == 0){
                 // to do later: return if this takes too long
    }
    // Check for Burst Operation terminated due to attempted program of reserved memory.
    if(FLCTL_PRGBRST_CTLSTAT&FLCTL_PRGBRST_CTLSTAT_ADDR_ERR){
      // Clear all error flags in FLCTL_CLRIFG register.
      FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
      // Clear any past errors and set status back to "idle".
      FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
      // Recall lock status of the block in Flash Main Memory Bank 1.
      FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
      // It is possible that some data was correctly written if the mass write
      // straddles a reserved and a not reserved block.  This error response may
      // need to be changed depending on how the higher-level program intends to
      // use reserved memory blocks.
      return 0;
    }
    // Increment programming pulses used.
    numPrgPulses = numPrgPulses + 1;
    // All writes were successful unless an error was detected.
    writes = count;
    while((FLCTL_PRGBRST_CTLSTAT&FLCTL_PRGBRST_CTLSTAT_PRE_ERR) || (FLCTL_PRGBRST_CTLSTAT&FLCTL_PRGBRST_CTLSTAT_PST_ERR)){
      // Check for pre-program verify error.
      if(FLCTL_PRGBRST_CTLSTAT&FLCTL_PRGBRST_CTLSTAT_PRE_ERR){
        // Check if exceeded maximum number of programming pulses.
        if(numPrgPulses > MAX_PRG_PLS_TLV){
          // Clear all error flags in FLCTL_CLRIFG register.
          FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
          // Clear any past errors and set status back to "idle".
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
          // Recall lock status of the block in Flash Main Memory Bank 1.
          FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
          return writes;
        }
        // At least one bit was already 0 before programming started.
        // The flash to be written is in Bank 1.
        // Configure for 5 wait states (minimum for 48 MHz operation) and for read mode of Program Verify.
        FLCTL_BANK1_RDCTL = FLCTL_BANK1_RDCTL_WAIT_5|FLCTL_BANK1_RDCTL_RD_MODE_3;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_3){};
        for(i=0; i<count; i=i+1){
          existingData = *(volatile uint32_t *)(addr + 4*i);
          failBits[i] = ~(existingData|FLCTL_PRGBRST_DATAn_x[i]);
                                                    // see Page 382 of MSP432 Datasheet
          updatedData[i] = FLCTL_PRGBRST_DATAn_x[i]|failBits[i];
        }
        // Configure for read mode of Normal Read.
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_RD_MODE_M)|FLCTL_BANK1_RDCTL_RD_MODE_0;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0){};
        // Configure for 2 wait states (minimum for 48 MHz operation).
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_WAIT_M)|FLCTL_BANK1_RDCTL_WAIT_2;
        // Clear all error flags in FLCTL_CLRIFG and FLCTL_PRGBRST_CTLSTAT registers.
        FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
        FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
        // Check if some bits still need to be written.
        writes = 0;
        for(i=0; i<count; i=i+1){
          if(updatedData[i] == 0xFFFFFFFF){
            writes = writes + 1;
          }
        }
        if(writes != count){
          // Enable Post Verify option.
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_AUTO_PST;
          // Pre Verify not needed since failing bits already masked.
          FLCTL_PRGBRST_CTLSTAT &= ~FLCTL_PRGBRST_CTLSTAT_AUTO_PRE;
          // Rewrite the FLCTL_PRGBRST_DATAn_x registers with 'updatedData'.
          for(i=0; i<count; i=i+1){
            FLCTL_PRGBRST_DATAn_x[i] = updatedData[i];
          }
          // Re-start burst program operation by setting START bit in FLCTL_PRGBRST_CTLSTAT.
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_START;
          // Wait for the programming to complete.
          while((FLCTL_IFG&FLCTL_IFG_PRGB) == 0){
                 // to do later: return if this takes too long
          }
          // Increment programming pulses used.
          numPrgPulses = numPrgPulses + 1;
          // All writes were successful unless an error was detected.
          writes = count;
        }
      }
      // Check for post-program verify error.
      if(FLCTL_PRGBRST_CTLSTAT&FLCTL_PRGBRST_CTLSTAT_PST_ERR){
        // Check if exceeded maximum number of programming pulses.
        if(numPrgPulses > MAX_PRG_PLS_TLV){
          // Clear all error flags in FLCTL_CLRIFG register.
          FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
          // Clear any past errors and set status back to "idle".
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
          // Recall lock status of the block in Flash Main Memory Bank 1.
          FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
          return writes;
        }
        // At least one bit was still 1 after programming finished.
        // The flash to be written is in Bank 1.
        // Configure for 5 wait states (minimum for 48 MHz operation) and for read mode of Program Verify.
        FLCTL_BANK1_RDCTL = FLCTL_BANK1_RDCTL_WAIT_5|FLCTL_BANK1_RDCTL_RD_MODE_3;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_3){};
        for(i=0; i<count; i=i+1){
          actualData = *(volatile uint32_t *)(addr + 4*i);
          failBits[i] = (~FLCTL_PRGBRST_DATAn_x[i])&actualData;
          updatedData[i] = ~failBits[i];            // see Page 383 of MSP432 Datasheet
        }
        // Configure for read mode of Normal Read.
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_RD_MODE_M)|FLCTL_BANK1_RDCTL_RD_MODE_0;
        // Wait for the read mode change to be confirmed.
        while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0){};
        // Configure for 2 wait states (minimum for 48 MHz operation).
        FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_WAIT_M)|FLCTL_BANK1_RDCTL_WAIT_2;
        // Clear all error flags in FLCTL_CLRIFG and FLCTL_PRGBRST_CTLSTAT registers.
        FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
        FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
        // Check if some bits still need to be written.
        writes = 0;
        for(i=0; i<count; i=i+1){
          if(failBits[i] == 0x00000000){
            writes = writes + 1;
          }
        }
        if(writes != count){
          // Enable Post Verify option.
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_AUTO_PST;
          // Pre Verify not needed since failing bits already masked.
          FLCTL_PRGBRST_CTLSTAT &= ~FLCTL_PRGBRST_CTLSTAT_AUTO_PRE;
          // Rewrite the FLCTL_PRGBRST_DATAn_x registers with 'updatedData'.
          for(i=0; i<count; i=i+1){
            FLCTL_PRGBRST_DATAn_x[i] = updatedData[i];
          }
          // Re-start burst program operation by setting START bit in FLCTL_PRGBRST_CTLSTAT.
          FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_START;
          // Wait for the programming to complete.
          while((FLCTL_IFG&FLCTL_IFG_PRGB) == 0){
                 // to do later: return if this takes too long
          }
          // Increment programming pulses used.
          numPrgPulses = numPrgPulses + 1;
          // All writes were successful unless an error was detected.
          writes = count;
        }
      }
    }
    // Clear all error flags in FLCTL_CLRIFG register.
    FLCTL_CLRIFG = (FLCTL_CLRIFG_PRG_ERR|FLCTL_CLRIFG_PRGB|FLCTL_CLRIFG_AVPST|FLCTL_CLRIFG_AVPRE);
    // Clear any past errors and set status back to "idle".
    FLCTL_PRGBRST_CTLSTAT |= FLCTL_PRGBRST_CTLSTAT_CLR_STAT;
    // Recall lock status of the block in Flash Main Memory Bank 1.
    FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
  }
  return writes;
}

//------------Flash_Erase------------
// Erase 4 KB block of flash.  Parameter 'addr' must be in
// flash Bank 1, and this function must be in flash Bank 0.
// Input: addr 4-KB aligned flash memory address to erase
// Output: 'NOERROR' if successful, 'ERROR' if fail (defined in FlashProgram.h)
// Note: This function is not interrupt safe.
int Flash_Erase(uint32_t addr){
  uint32_t lockStatus, lockMask, numEraPulses;
  if((IsInBank0(addr)) || (IsInBank1((int)&Flash_Erase))){
    // This function and the flash to be erased are in the same bank.
    // Because we cannot change the read mode of the flash that contains
    // the currently running code, we need to either copy this function
    // to RAM or use one of the library functions in ROM.
                 // to do later: fix this
    return ERROR;
  }
  if(EraseAddrValid(addr)){
    // Clear pending ERASE interrupt flags.
    FLCTL_CLRIFG = FLCTL_CLRIFG_ERASE;
    // Clear any past reserved memory erase attempt errors and set status back to "idle".
    FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_CLR_STAT;
    // Unlock the block in Flash Main Memory Bank 1.
    lockMask = 1<<((addr - FLASH_BANK1_MIN)>>12);   // 0x00000001 to 0x80000000
    lockStatus = FLCTL_BANK1_MAIN_WEPROT&lockMask;  // save previous value
    FLCTL_BANK1_MAIN_WEPROT = (FLCTL_BANK1_MAIN_WEPROT&~lockMask);
    // Configure flash erase sector address.
    FLCTL_ERASE_SECTADDR = addr;
    // Configure for erase in Main Memory region.
    FLCTL_ERASE_CTLSTAT = (FLCTL_ERASE_CTLSTAT&~FLCTL_ERASE_CTLSTAT_TYPE_M)|FLCTL_ERASE_CTLSTAT_TYPE_0;
    // Configure for sector erase.
    FLCTL_ERASE_CTLSTAT &= ~FLCTL_ERASE_CTLSTAT_MODE;
    // Keep track of the number of erase pulses.
    numEraPulses = 0;
    // Initiate erase of the desired flash block.
    FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_START;
    // Wait for the erase to complete.
    while((FLCTL_IFG&FLCTL_IFG_ERASE) == 0){
                 // to do later: return ERROR if this takes too long
    }
    // Increment erase pulses used.
    numEraPulses = numEraPulses + 1;
    // Check for success of erase operation.
    do{
      // Check if exceeded maximum number of erase pulses.
      if(numEraPulses > MAX_ERA_PLS_TLV){
        // Clear pending ERASE and RDBRST interrupt flags.
        FLCTL_CLRIFG = FLCTL_CLRIFG_ERASE|FLCTL_CLRIFG_RDBRST;
        // Clear any past reserved memory erase attempt errors and set status back to "idle".
        FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_CLR_STAT;
        // Clear any past reserved memory access attempt errors, clear comparison errors, and set status back to "idle".
        FLCTL_RDBRST_CTLSTAT |= FLCTL_RDBRST_CTLSTAT_CLR_STAT;
        // Recall lock status of the block in Flash Main Memory Bank 1.
        FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
        return ERROR;
      }
      // Configure Burst Read/Compare hardware.
      // Clear any past reserved memory access attempt errors, clear comparison errors, and set status back to "idle".
      FLCTL_RDBRST_CTLSTAT |= FLCTL_RDBRST_CTLSTAT_CLR_STAT;
      // Configure starting sector address, defined as offset from start address of flash.
      FLCTL_RDBRST_STARTADDR = addr - FLASH_BANK0_MIN;
      // Configure length of read.
      FLCTL_RDBRST_LEN = 4096;                      // length of burst operation in bytes
      // Configure for comparison against all 1's, terminate on first mismatch, and read main memory.
      FLCTL_RDBRST_CTLSTAT = (FLCTL_RDBRST_CTLSTAT &
                             ~(FLCTL_RDBRST_CTLSTAT_TEST_EN|FLCTL_RDBRST_CTLSTAT_MEM_TYPE_M)) |
                             FLCTL_RDBRST_CTLSTAT_DATA_CMP |
                             FLCTL_RDBRST_CTLSTAT_STOP_FAIL |
                             FLCTL_RDBRST_CTLSTAT_MEM_TYPE_0;
      // Clear failure address and failure count registers.
      FLCTL_RDBRST_FAILADDR = 0;                    // may be interesting when debugging
      FLCTL_RDBRST_FAILCNT = 0;
      // Clear pending RDBRST interrupt flag.
      FLCTL_CLRIFG = FLCTL_CLRIFG_RDBRST;
      // The flash to be cleared is in Bank 1.
      // Configure for 5 wait states (minimum for 48 MHz operation) and for read mode of Erase Verify.
      FLCTL_BANK1_RDCTL = FLCTL_BANK1_RDCTL_WAIT_5|FLCTL_BANK1_RDCTL_RD_MODE_4;
      // Wait for the read mode change to be confirmed.
      while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_4){};
      // Initiate Read Burst/Compare operation.
      FLCTL_RDBRST_CTLSTAT |= FLCTL_RDBRST_CTLSTAT_START;
      // Wait for the read to complete.
      while((FLCTL_IFG&FLCTL_IFG_RDBRST) == 0){
                 // to do later: return ERROR if this takes too long
      }
      // Clear any past reserved memory access attempt errors, clear comparison errors, and set status back to "idle".
      FLCTL_RDBRST_CTLSTAT |= FLCTL_RDBRST_CTLSTAT_CLR_STAT;
      // Configure for read mode of Normal Read.
      FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_RD_MODE_M)|FLCTL_BANK1_RDCTL_RD_MODE_0;
      // Wait for the read mode change to be confirmed.
      while((FLCTL_BANK1_RDCTL&FLCTL_BANK1_RDCTL_RD_MODE_STATUS_M) != FLCTL_BANK1_RDCTL_RD_MODE_STATUS_0){};
      // Configure for 2 wait states (minimum for 48 MHz operation).
      FLCTL_BANK1_RDCTL = (FLCTL_BANK1_RDCTL&~FLCTL_BANK1_RDCTL_WAIT_M)|FLCTL_BANK1_RDCTL_WAIT_2;
      // Check if some bits still need to be cleared.
      // Look at the FLCTL_RDBRST_FAILCNT register because the bit in FLCTL_RDBRST_CTLSTAT is cleared when going back to idle.
      if(FLCTL_RDBRST_FAILCNT > 0){
        // Clear pending ERASE interrupt flags.
        FLCTL_CLRIFG = FLCTL_CLRIFG_ERASE;
        // Clear any past reserved memory erase attempt errors and set status back to "idle".
        FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_CLR_STAT;
        // Configure flash erase sector address.
        FLCTL_ERASE_SECTADDR = addr;
        // Configure for erase in Main Memory region.
        FLCTL_ERASE_CTLSTAT = (FLCTL_ERASE_CTLSTAT&~FLCTL_ERASE_CTLSTAT_TYPE_M)|FLCTL_ERASE_CTLSTAT_TYPE_0;
        // Configure for sector erase.
        FLCTL_ERASE_CTLSTAT &= ~FLCTL_ERASE_CTLSTAT_MODE;
        // Re-initiate erase of the desired flash block.
        FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_START;
        // Wait for the erase to complete.
        while((FLCTL_IFG&FLCTL_IFG_ERASE) == 0){
                 // to do later: return ERROR if this takes too long
        }
        // Increment erase pulses used.
        numEraPulses = numEraPulses + 1;
      }
    } while(FLCTL_RDBRST_FAILCNT > 0);
    // Clear pending ERASE and RDBRST interrupt flags.
    FLCTL_CLRIFG = FLCTL_CLRIFG_ERASE|FLCTL_CLRIFG_RDBRST;
    // Clear any past reserved memory erase attempt errors and set status back to "idle".
    FLCTL_ERASE_CTLSTAT |= FLCTL_ERASE_CTLSTAT_CLR_STAT;
    // Recall lock status of the block in Flash Main Memory Bank 1.
    FLCTL_BANK1_MAIN_WEPROT = FLCTL_BANK1_MAIN_WEPROT|lockStatus;
    return NOERROR;
  }
  return ERROR;
}
