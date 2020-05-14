//
// Created by johnm on 5/14/2020.
//

#ifndef DONGBOYADVANCE_ROM_PARSER_H
#define DONGBOYADVANCE_ROM_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _rom_info {
    char *name;
    int64_t rom_size;
    uint32_t rom_mask;
    char *file_path;
    FILE *file;
} Rom_Info;
uint8_t *rom_data_ptr;

void read_rom(Rom_Info *rom_info);
uint32_t to_pow2(uint32_t val);
#endif //DONGBOYADVANCE_ROM_PARSER_H
