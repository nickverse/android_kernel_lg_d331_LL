/*****************************************************************************
 Copyright(c) 2012 FCI Inc. All Rights Reserved

 File name : fc8150_ppi.c

 Description : fc8150 host interface

*******************************************************************************/

#include "fci_types.h"
#include "fc8150_regs.h"
#include "fci_oal.h"

#define BBM_BASE_ADDR       0x00

#define PPI_BMODE           0x00
#define PPI_WMODE           0x10
#define PPI_LMODE           0x20
#define PPI_READ            0x40
#define PPI_WRITE           0x00
#define PPI_AINC            0x80

#define FC8150_PPI_REG      (*(volatile u8 *)(BBM_BASE_ADDR))

//static OAL_SEMAPHORE hBbmMutex;

int fc8150_ppi_init(HANDLE hDevice, u16 param1, u16 param2)
{
    //OAL_CREATE_SEMAPHORE(&hBbmMutex, "ppi", 1, OAL_FIFO);
    return BBM_OK;
}

int fc8150_ppi_byteread(HANDLE hDevice, u16 addr, u8 *data)
{
    u32 length = 1;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = PPI_READ | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    *data = FC8150_PPI_REG;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_wordread(HANDLE hDevice, u16 addr, u16 *data)
{
    u32 length = 2;
    u8 command = PPI_AINC | PPI_READ | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    *data = FC8150_PPI_REG;
    *data |= FC8150_PPI_REG << 8;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_longread(HANDLE hDevice, u16 addr, u32 *data)
{
    u32 length = 4;
    u8 command = PPI_AINC | PPI_READ | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    *data = FC8150_PPI_REG;
    *data |= FC8150_PPI_REG << 8;
    *data |= FC8150_PPI_REG << 16;
    *data |= FC8150_PPI_REG << 24;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);

    return BBM_OK;
}

int fc8150_ppi_bulkread(HANDLE hDevice, u16 addr, u8 *data, u16 length)
{
    int i;
    u8 command = PPI_AINC | PPI_READ | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    for(i=0; i<length; i++) {
        data[i] = FC8150_PPI_REG;
    }
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);

    return BBM_OK;
}

int fc8150_ppi_bytewrite(HANDLE hDevice, u16 addr, u8 data)
{
    u32 length = 1;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = PPI_WRITE | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    FC8150_PPI_REG = data;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_wordwrite(HANDLE hDevice, u16 addr, u16 data)
{
    u32 length = 2;
    u8 command = PPI_AINC | PPI_WRITE | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    FC8150_PPI_REG = data & 0xff;
    FC8150_PPI_REG = (data & 0xff00) >> 8;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_longwrite(HANDLE hDevice, u16 addr, u32 data)
{
    u32 length = 4;
    u8 command = PPI_AINC | PPI_WRITE | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    FC8150_PPI_REG = data &  0x000000ff;
    FC8150_PPI_REG = (data & 0x0000ff00) >> 8;
    FC8150_PPI_REG = (data & 0x00ff0000) >> 16;
    FC8150_PPI_REG = (data & 0xff000000) >> 24;
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_bulkwrite(HANDLE hDevice, u16 addr, u8* data, u16 length)
{
    int i;
    u8 command = PPI_AINC | PPI_WRITE | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    for(i=0; i<length; i++) {
        FC8150_PPI_REG = data[i];
    }
    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_dataread(HANDLE hDevice, u16 addr, u8* data, u32 length)
{
    int i;
    u8 command = PPI_READ | PPI_BMODE;

    //OAL_OBTAIN_SEMAPHORE(&hBbmMutex, OAL_SUSPEND);
    FC8150_PPI_REG = addr & 0xff;
    FC8150_PPI_REG = (addr & 0xff00) >> 8;
    FC8150_PPI_REG = command | ((length & 0x0f0000) >> 16);
    FC8150_PPI_REG = (length & 0xff00) >> 8;
    FC8150_PPI_REG = length & 0xff;

    for(i=0; i<length; i++) {
        data[i] = FC8150_PPI_REG;
    }

    //OAL_RELEASE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}

int fc8150_ppi_deinit(HANDLE hDevice)
{
    //OAL_DELETE_SEMAPHORE(&hBbmMutex);
    return BBM_OK;
}
