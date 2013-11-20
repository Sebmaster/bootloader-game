ENTRY(_main)
OUTPUT_FORMAT(binary)

SECTIONS {
    . = 0x7C00;

    .text : {
        *(.text)

        . = 0x7CFD;
        BYTE(0x55);
        BYTE(0xAA);
    }
}
