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
    while(rom_info->current_opcode < rom_info->rom_size) {
        ARM_U_WORD current_address = 0x08000000 + rom_info->current_opcode;
        ARM_U_WORD current_opcode = fetch_opcode();
        write_memory(current_address,current_opcode,WORD);
        //rom_info->current_opcode+=4;
    }
    rom_info->current_opcode=0;
}
void load_bios() {
    bios = (Bios *) malloc(sizeof(Bios));
    bios->bios_path = (char *) malloc(sizeof(char) *256);
    strcpy(bios->bios_path,"C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\BIOS\\GBA.BIOS");
    bios->file = fopen(bios->bios_path,"rb");
    fseek(bios->file,0,SEEK_END);
    bios->bios_size = ftell(bios->file);
    printf("Bios size (bytes): %ld\n",bios->bios_size);
    bios->bios = (uint8_t *) malloc(sizeof(uint8_t) * bios->bios_size);
    fread(bios->bios,bios->bios_size,1,bios->file);
    bios->current_opcode = 0;
    fclose(bios->file);

}
ARM_U_WORD fetch_opcode() {
    ARM_U_WORD opcode = rom_info->rom[rom_info->current_opcode] << 0;
    opcode |= rom_info->rom[rom_info->current_opcode + 1] << 8;
    opcode |= rom_info->rom[rom_info->current_opcode + 2] << 16;
    opcode |= rom_info->rom[rom_info->current_opcode + 3] << 24;
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