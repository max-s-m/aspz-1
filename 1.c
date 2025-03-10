#include <stdio.h>
#include <stdint.h>

#define print_by_bit(X) _Generic((X), \
    uint8_t: bin_op_print((X), 8),\
    uint16_t: bin_op_print((X), 16),\
    uint32_t: bin_op_print((X), 32),\
    uint64_t: bin_op_print((X), 64)\
)

#define print_by_table(X) _Generic((X), \
    uint8_t: bin_table_print((X), 8),\
    uint16_t: bin_table_print((X), 16),\
    uint32_t: bin_table_print((X), 32),\
    uint64_t: bin_table_print((X), 64)\
)

void bin_op_print(uint64_t, int);
void bin_table_print(uint64_t, int);
void bin_text_print(const char *);

const char *bin_num_table[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

int main(){
    uint8_t num8 = 255; //2^8 - 1
    uint16_t num16 = 65535; //2^16 - 1
    uint32_t num32 = 4294967295; //2^32 - 1
    uint64_t num64 = 18446744073709551615; //2^64 - 1

    printf("8 bit num operations:\n");
    print_by_bit(num8);
    printf("8 bit num table:\n");
    print_by_table(num8);
    printf("16 bit num:\n");
    print_by_bit(num16);
    printf("32 bit num:\n");
    print_by_bit(num32);
    printf("64 bit num:\n");
    print_by_bit(num64);
    printf("Text binary:\n");
    bin_text_print("abc");
}

void bin_op_print(uint64_t num, int bits){
    for(int i = bits-1; i >= 0; i--){
        printf("%c", (num & ((uint64_t)1 << i)) ? '1' : '0');
        if(i % 4 == 0){
            printf(" ");
        }
    }
    printf("\n");
}

void bin_table_print(uint64_t num, int bits){
    for(int i=bits/4; i>=1; i--){
        printf("%s ", bin_num_table[num >> ((i-1) * 4) & 15]);
    }
    printf("\n");
}

void bin_text_print(const char *text){
    while(*text){
        print_by_bit((uint8_t)*text);
        text++;
    }
}