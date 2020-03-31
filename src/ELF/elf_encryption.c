//
// Created by silentvoid on 3/16/20.
// Copyright (c) 2020 SilentVoid. All rights reserved.
//

#include "elf_encryption.h"
#include "cipher_functions.h"
#include "elf_allocation.h"
#include "elf_functions.h"
#include "loader_functions.h"

#include "log.h"

int encrypt_elf(t_elf *elf, char *cipher) {
    int text_section_index = find_elf_section_index(elf, ".text");
    if(text_section_index == -1) {
        log_error("Couldn't find .text section in the ELF binary");
        return -1;
    }

    log_verbose("Got .text section index : %d", text_section_index);

    char *text_data;
    if(elf->s_type == ELF32) {
        text_data = ((t_elf32 *)elf)->section_data[text_section_index];

        // Setting global variables
        text_data_size = ((t_elf32 *)elf)->section_header[text_section_index].sh_size;
        text_entry_point = ((t_elf32 *)elf)->section_header[text_section_index].sh_addr;
    }
    else {
        text_data = ((t_elf64 *)elf)->section_data[text_section_index];

        // Setting global variables
        text_data_size = ((t_elf64 *)elf)->section_header[text_section_index].sh_size;
        text_entry_point = ((t_elf64 *)elf)->section_header[text_section_index].sh_addr;
    }

    log_verbose("Generating random key ...");
    cipher_key = generate_random_key();
    uint64_t temp_key = cipher_key;
    log_verbose("Random key : %x", cipher_key);

    if(strcmp(cipher, "xor") == 0) {
        xor_encrypt(text_data, text_data_size, temp_key);
    }
    else if(strcmp(cipher, "aes") == 0) {

    }

    return 1;
}
