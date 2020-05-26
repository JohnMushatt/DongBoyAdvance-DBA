//
// Created by johnm on 5/14/2020.
//

#include "rom_parser.h"
#include <string.h>

void read_rom() {
    rom_info = (Rom_Info *) malloc(sizeof(Rom_Info));
    rom_info->name= (char *)malloc(sizeof(char) * 32);
    rom_info->file_path = (char *)malloc(sizeof(char)*256);
    printf("Running Pokemon Emerald\n");
    strcpy(rom_info->name,"Emerald");
    strcpy(rom_info->file_path,"C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\roms\\Emerald\\Pokemon - Emerald Version (U).gba");
    rom_info->file = fopen(rom_info->file_path, "rb");
    fseek(rom_info->file, 0, SEEK_END);
    rom_info->rom_size = ftell(rom_info->file);
    rom_info->rom_mask = to_pow2(rom_info->rom_size) - 1;

    if (rom_info->rom_size > max_rom_sz) {
        printf("Max rom size error\n");
        rom_info->rom_size = max_rom_sz;
    }
    fseek(rom_info->file, 0, SEEK_SET);
    rom_info->rom = (uint8_t *) malloc(sizeof(uint8_t) * rom_info->rom_size);
    fread(rom_info->rom, rom_info->rom_size, 1, rom_info->file);
    rom_info->current_opcode = 0;
    fclose(rom_info->file);
    printf("Bytes read from rom: %ld\n", rom_info->rom_size);
}

ARM_U_WORD fetch_opcode() {
    ARM_U_WORD opcode = rom_info->rom[rom_info->current_opcode] << 24;
    opcode |= rom_info->rom[rom_info->current_opcode + 1] << 16;
    opcode |= rom_info->rom[rom_info->current_opcode + 2] << 8;
    opcode |= rom_info->rom[rom_info->current_opcode + 3];
    rom_info->current_opcode += sizeof(ARM_U_WORD);
    return opcode;
}

void destroy_rom() {
    if (rom_info->rom!=NULL) {
        free(rom_info->rom);
    }
    if (rom_info->file!=NULL) {
        free(rom_info->file);
    }
    if(rom_info->file_path!=NULL) {
        free(rom_info->file_path);
    }
    if(rom_info->name!=NULL) {
        free(rom_info->name);
    }
    if(rom_info!=NULL) {
        free(rom_info);
    }
}

uint32_t to_pow2(uint32_t val) {
    val--;
    val |= (val >> 1);
    val |= (val >> 2);
    val |= (val >> 4);
    val |= (val >> 8);
    val |= (val >> 16);

    return val + 1;
}