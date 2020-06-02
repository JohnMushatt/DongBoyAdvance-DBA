//
// Created by johnm on 5/14/2020.
//

#ifndef DONGBOYADVANCE_ROM_PARSER_H
#define DONGBOYADVANCE_ROM_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cpu.h>

#define max_rom_sz  32 * 1024 * 1024

typedef struct _rom_info {
    char *name;
    int64_t rom_size;
    uint32_t rom_mask;
    char *file_path;
    FILE *file;
    uint8_t *rom;
    int32_t current_opcode;
} Rom_Info;
Rom_Info *rom_info;
typedef struct _bios {
    int64_t bios_size;
    char *bios_path;
    FILE *file;
    uint8_t *bios;
    int32_t current_opcode;
} Bios;
Bios *bios;
void read_rom();
void load_bios();
ARM_U_WORD fetch_opcode();
uint32_t to_pow2(uint32_t val);
void destroy_rom();
#endif //DONGBOYADVANCE_ROM_PARSER_H
