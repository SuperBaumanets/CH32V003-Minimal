/* --------------------------------------------------------------------------
 * Большие переменные, которые НЕ попадают в small data (размер > 8 байт)
 * Будут в обычных .data / .bss / .rodata
 * -------------------------------------------------------------------------- */
__attribute__((used)) unsigned int big_data[8] = {
    0x11111111, 0x22222222, 0x33333333, 0x44444444,
    0x55555555, 0x66666666, 0x77777777, 0x88888888
};
__attribute__((used)) unsigned int big_bss[8];
__attribute__((used)) const unsigned int big_rodata[4] = {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD};

/* --------------------------------------------------------------------------
 * Маленькие переменные (размер ≤ 8 байт)
 * Попадут в .sdata/.sbss/.srodata
 * -------------------------------------------------------------------------- */
__attribute__((used)) unsigned int small_data   = 0xDEADBEEF;   // 4 байта → .sdata
__attribute__((used)) unsigned short small_data2  = 0xABCD;     // 2 байта → .sdata
__attribute__((used)) char  small_data3  = 0x55;                // 1 байт  → .sdata

__attribute__((used)) unsigned int small_bss;       // 4 байта → .sbss
__attribute__((used)) unsigned short small_bss2;    // 2 байта → .sbss
__attribute__((used)) char  small_bss3;             // 1 байт  → .sbss

__attribute__((used)) const unsigned int small_rodata = 0x12345678;     // 4 байта → .srodata
__attribute__((used)) const char ro_message[] = "Test gp optimization"; // строка >8 байт, останется в .rodata


int main(void) {
    volatile unsigned int tmp;

    // Доступ к большим данным
    tmp = big_data[0];
    big_bss[0] = tmp;
    tmp = big_rodata[0];

    // Доступ к маленьким данным
    tmp = small_data;
    small_data2 = (unsigned short)tmp;
    small_data3 = (char)(tmp >> 16);

    small_bss = small_rodata;
    small_bss2 = (unsigned short)small_rodata;
    small_bss3 = (char)(small_rodata >> 16);

    tmp = ro_message[0];

    while (1);
    return 0;
}