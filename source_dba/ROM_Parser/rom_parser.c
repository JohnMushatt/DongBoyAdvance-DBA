//
// Created by johnm on 5/14/2020.
//

#include "rom_parser.h"

void read_rom(Rom_Info *rom_info) {
    rom_info->file_path = "C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\roms\\Emerald\\Pokemon - Emerald Version (U).gba";
    rom_info->file = fopen(rom_info->file_path,"rb");
    fseek(rom_info->file,0,SEEK_END);
    rom_info->rom_size = ftell(rom_info->file);
    rom_info->rom_mask = to_pow2(rom_info->rom_size)-1;
}
uint32_t to_pow2(uint32_t val) {
    val--;

    val |= (val >>  1);
    val |= (val >>  2);
    val |= (val >>  4);
    val |= (val >>  8);
    val |= (val >> 16);

    return val + 1;
}