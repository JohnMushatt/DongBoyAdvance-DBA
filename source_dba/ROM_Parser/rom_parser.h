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
    ARM_U_WORD current_opcode;
} Rom_Info;
Rom_Info *rom_info;

void read_rom();
ARM_U_WORD fetch_opcode();
uint32_t to_pow2(uint32_t val);
#endif //DONGBOYADVANCE_ROM_PARSER_H
