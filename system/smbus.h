#ifndef _SMBUS_H_
#define _SMBUS_H_
/**
 * SPDX-License-Identifier: GPL-2.0
 *
 * \file
 *
 * Provides functions for reading SPD via SMBUS
 *
 * Copyright (C) 2004-2022 Samuel Demeulemeester.
 */

/* i801 Hosts Addresses */
#define SMBHSTSTS   smbusbase
#define SMBHSTCNT   smbusbase + 2
#define SMBHSTCMD   smbusbase + 3
#define SMBHSTADD   smbusbase + 4
#define SMBHSTDAT0  smbusbase + 5
#define SMBHSTDAT1  smbusbase + 6
#define SMBBLKDAT   smbusbase + 7
#define SMBPEC      smbusbase + 8
#define SMBAUXSTS   smbusbase + 12
#define SMBAUXCTL   smbusbase + 12

/* i801 Hosts Status register bits */
#define SMBHSTSTS_BYTE_DONE     0x80
#define SMBHSTSTS_INUSE_STS     0x40
#define SMBHSTSTS_SMBALERT_STS  0x20
#define SMBHSTSTS_FAILED        0x10
#define SMBHSTSTS_BUS_ERR       0x08
#define SMBHSTSTS_DEV_ERR       0x04
#define SMBHSTSTS_INTR          0x02
#define SMBHSTSTS_HOST_BUSY     0x01

#define SMBHSTCNT_QUICK         0x00
#define SMBHSTCNT_BYTE          0x04
#define SMBHSTCNT_BYTE_DATA     0x08
#define SMBHSTCNT_WORD_DATA     0x0C
#define SMBHSTCNT_START         0x40

/* Platform Capabilities */
#define HAS_SDR  (1 << 1)
#define HAS_DDR  (1 << 2)
#define HAS_DDR2 (1 << 3)
#define HAS_DDR3 (1 << 4)
#define HAS_DDR4 (1 << 5)
#define HAS_DDR5 (1 << 6)

struct pci_smbus_controller{
    unsigned vendor;
    unsigned device;
    char *name;
    void (*get_adr)(uint8_t idx);
    uint8_t (*read_spd_byte)(uint8_t dimmadr, uint16_t bytenum);
    uint8_t cap;
};

typedef struct spd_infos {
    bool        isValid;
    uint32_t    module_size;
    uint8_t     slot_num;
    char        *type;
    uint16_t    jedec_code;
    char        sku[32];
    uint8_t     sku_len;
    uint16_t    freq;
    uint8_t     XMP;
    bool        hasECC;
    uint8_t     fab_year;
    uint8_t     fab_week;
} spd_info;

#define get_spd(smb_idx, slot_idx, spd_adr) \
    smbcontrollers[smb_idx].read_spd_byte(slot_idx, spd_adr)

/**
 * Print SMBUS Info
 */

void print_smbus_startup_info(void);

#endif // SMBUS_H