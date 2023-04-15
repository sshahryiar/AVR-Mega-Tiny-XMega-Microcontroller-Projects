
_swap:

;st7735.c,4 :: 		void swap(signed int *a, signed int *b)
;st7735.c,6 :: 		signed int temp = 0x0000;
;st7735.c,8 :: 		temp = *b;
	MOVW       R30, R4
	LD         R16, Z+
	LD         R17, Z+
; temp start address is: 18 (R18)
	MOVW       R18, R16
;st7735.c,9 :: 		*b = *a;
	MOVW       R30, R2
	LD         R16, Z+
	LD         R17, Z+
	MOVW       R30, R4
	ST         Z+, R16
	ST         Z+, R17
;st7735.c,10 :: 		*a = temp;
	MOVW       R30, R2
	ST         Z+, R18
	ST         Z+, R19
; temp end address is: 18 (R18)
;st7735.c,11 :: 		}
L_end_swap:
	RET
; end of _swap

_setup_TFT_peripherals:

;st7735.c,14 :: 		void setup_TFT_peripherals()
;st7735.c,16 :: 		PORTC_DIR = 0xBE;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	LDI        R27, 190
	STS        PORTC_DIR+0, R27
;st7735.c,17 :: 		VPORT2_DIR = 0xBE;
	LDI        R27, 190
	OUT        VPORT2_DIR+0, R27
;st7735.c,18 :: 		delay_ms(100);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_setup_TFT_peripherals0:
	DEC        R16
	BRNE       L_setup_TFT_peripherals0
	DEC        R17
	BRNE       L_setup_TFT_peripherals0
	DEC        R18
	BRNE       L_setup_TFT_peripherals0
;st7735.c,20 :: 		SPIC_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV2, _SPI_CLK_HI_LEADING);
	LDI        R27, 8
	MOV        R4, R27
	LDI        R27, 4
	MOV        R3, R27
	LDI        R27, 16
	MOV        R2, R27
	CALL       _SPIC_Init_Advanced+0
;st7735.c,21 :: 		SPI_Set_Active(&SPIC_Read, &SPIC_Write);
	LDI        R27, #lo_addr(_SPIC_Write+0)
	MOV        R4, R27
	LDI        R27, hi_addr(_SPIC_Write+0)
	MOV        R5, R27
	LDI        R27, #lo_addr(_SPIC_Read+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_SPIC_Read+0)
	MOV        R3, R27
	CALL       _SPI_Set_Active+0
;st7735.c,22 :: 		delay_ms(10);
	LDI        R18, 2
	LDI        R17, 160
	LDI        R16, 147
L_setup_TFT_peripherals2:
	DEC        R16
	BRNE       L_setup_TFT_peripherals2
	DEC        R17
	BRNE       L_setup_TFT_peripherals2
	DEC        R18
	BRNE       L_setup_TFT_peripherals2
	NOP
;st7735.c,23 :: 		}
L_end_setup_TFT_peripherals:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	RET
; end of _setup_TFT_peripherals

_TFT_Write:

;st7735.c,26 :: 		void TFT_Write(unsigned char value, unsigned char mode)
;st7735.c,28 :: 		CS_pin = LOW;
	LDS        R27, PORTC_OUT+0
	CBR        R27, 16
	STS        PORTC_OUT+0, R27
;st7735.c,29 :: 		RS_pin = mode;
	BST        R3, 0
	LDS        R27, PORTC_OUT+0
	BLD        R27, 3
	STS        PORTC_OUT+0, R27
;st7735.c,30 :: 		SPIC_Write(value);
	CALL       _SPIC_Write+0
;st7735.c,31 :: 		CS_pin = HIGH;
	LDS        R27, PORTC_OUT+0
	SBR        R27, 16
	STS        PORTC_OUT+0, R27
;st7735.c,32 :: 		}
L_end_TFT_Write:
	RET
; end of _TFT_Write

_ST7735_Reset:

;st7735.c,35 :: 		void ST7735_Reset()
;st7735.c,37 :: 		RST_pin = LOW;
	LDS        R27, PORTC_OUT+0
	CBR        R27, 4
	STS        PORTC_OUT+0, R27
;st7735.c,38 :: 		delay_ms(2);
	LDI        R17, 84
	LDI        R16, 29
L_ST7735_Reset4:
	DEC        R16
	BRNE       L_ST7735_Reset4
	DEC        R17
	BRNE       L_ST7735_Reset4
;st7735.c,39 :: 		RST_pin = HIGH;
	LDS        R27, PORTC_OUT+0
	SBR        R27, 4
	STS        PORTC_OUT+0, R27
;st7735.c,40 :: 		delay_ms(2);
	LDI        R17, 84
	LDI        R16, 29
L_ST7735_Reset6:
	DEC        R16
	BRNE       L_ST7735_Reset6
	DEC        R17
	BRNE       L_ST7735_Reset6
;st7735.c,41 :: 		}
L_end_ST7735_Reset:
	RET
; end of _ST7735_Reset

_ST7735_init:

;st7735.c,44 :: 		void ST7735_init()
;st7735.c,46 :: 		setup_TFT_peripherals();
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	CALL       _setup_TFT_peripherals+0
;st7735.c,48 :: 		ST7735_Reset();
	CALL       _ST7735_Reset+0
;st7735.c,50 :: 		TFT_Write(ST7735_SWRESET, CMD);
	CLR        R3
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,51 :: 		delay_us(150);
	LDI        R17, 7
	LDI        R16, 59
L_ST7735_init8:
	DEC        R16
	BRNE       L_ST7735_init8
	DEC        R17
	BRNE       L_ST7735_init8
;st7735.c,52 :: 		TFT_Write(ST7735_SLPOUT, CMD);
	CLR        R3
	LDI        R27, 17
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,53 :: 		delay_us(150);
	LDI        R17, 7
	LDI        R16, 59
L_ST7735_init10:
	DEC        R16
	BRNE       L_ST7735_init10
	DEC        R17
	BRNE       L_ST7735_init10
;st7735.c,55 :: 		TFT_Write(ST7735_FRMCTR1, CMD);
	CLR        R3
	LDI        R27, 177
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,56 :: 		TFT_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,57 :: 		TFT_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,58 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,60 :: 		TFT_Write(ST7735_FRMCTR2, CMD);
	CLR        R3
	LDI        R27, 178
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,61 :: 		TFT_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,62 :: 		TFT_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,63 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,65 :: 		TFT_Write(ST7735_FRMCTR3, CMD);
	CLR        R3
	LDI        R27, 179
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,66 :: 		TFT_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,67 :: 		TFT_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,68 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,69 :: 		TFT_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,70 :: 		TFT_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,71 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,73 :: 		TFT_Write(ST7735_INVCTR, CMD);
	CLR        R3
	LDI        R27, 180
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,74 :: 		TFT_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,76 :: 		TFT_Write(ST7735_PWCTR1, CMD);
	CLR        R3
	LDI        R27, 192
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,77 :: 		TFT_Write(0xA2, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 162
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,78 :: 		TFT_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,79 :: 		TFT_Write(0x84, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 132
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,81 :: 		TFT_Write(ST7735_PWCTR1, CMD);
	CLR        R3
	LDI        R27, 192
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,82 :: 		TFT_Write(0xC5, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 197
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,84 :: 		TFT_Write(ST7735_PWCTR2, CMD);
	CLR        R3
	LDI        R27, 193
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,85 :: 		TFT_Write(0x0A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 10
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,86 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,88 :: 		TFT_Write(ST7735_PWCTR3, CMD);
	CLR        R3
	LDI        R27, 194
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,89 :: 		TFT_Write(0x8A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 138
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,90 :: 		TFT_Write(0x2A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 42
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,92 :: 		TFT_Write(ST7735_PWCTR4, CMD);
	CLR        R3
	LDI        R27, 195
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,93 :: 		TFT_Write(0x8A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 138
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,94 :: 		TFT_Write(0xEE, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 238
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,96 :: 		TFT_Write(ST7735_PWCTR5, CMD);
	CLR        R3
	LDI        R27, 196
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,97 :: 		TFT_Write(0x0E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 14
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,99 :: 		TFT_Write(ST7735_VMCTR1, CMD);
	CLR        R3
	LDI        R27, 197
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,100 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,102 :: 		TFT_Write(ST7735_COLMOD, CMD);
	CLR        R3
	LDI        R27, 58
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,103 :: 		TFT_Write(0x05, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 5
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,105 :: 		TFT_Write(ST7735_MADCTL, CMD);
	CLR        R3
	LDI        R27, 54
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,106 :: 		TFT_Write(0xC8, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 200
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,108 :: 		TFT_set_display_window(0x00, 0x00, 0x7F, 0x9F);
	LDI        R27, 159
	MOV        R5, R27
	LDI        R27, 127
	MOV        R4, R27
	CLR        R3
	CLR        R2
	CALL       _TFT_set_display_window+0
;st7735.c,110 :: 		TFT_Write(ST7735_GMCTRP1, CMD);
	CLR        R3
	LDI        R27, 224
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,111 :: 		TFT_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,112 :: 		TFT_Write(0x1C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 28
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,113 :: 		TFT_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,114 :: 		TFT_Write(0x12, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 18
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,115 :: 		TFT_Write(0x37, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 55
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,116 :: 		TFT_Write(0x32, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 50
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,117 :: 		TFT_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,118 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,119 :: 		TFT_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,120 :: 		TFT_Write(0x25, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 37
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,121 :: 		TFT_Write(0x2B, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 43
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,122 :: 		TFT_Write(0x39, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 57
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,123 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,124 :: 		TFT_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,125 :: 		TFT_Write(0x03, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 3
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,126 :: 		TFT_Write(0x10, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 16
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,128 :: 		TFT_Write(ST7735_GMCTRN1, CMD);
	CLR        R3
	LDI        R27, 225
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,129 :: 		TFT_Write(0x03, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 3
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,130 :: 		TFT_Write(0x1D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 29
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,131 :: 		TFT_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,132 :: 		TFT_Write(0x06, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 6
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,133 :: 		TFT_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,134 :: 		TFT_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,135 :: 		TFT_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,136 :: 		TFT_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,137 :: 		TFT_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,138 :: 		TFT_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,139 :: 		TFT_Write(0x37, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 55
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,140 :: 		TFT_Write(0x3F, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 63
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,141 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,142 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,143 :: 		TFT_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,144 :: 		TFT_Write(0x10, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 16
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,146 :: 		TFT_Write(ST7735_NORON, CMD);
	CLR        R3
	LDI        R27, 19
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,147 :: 		delay_ms(10);
	LDI        R18, 2
	LDI        R17, 160
	LDI        R16, 147
L_ST7735_init12:
	DEC        R16
	BRNE       L_ST7735_init12
	DEC        R17
	BRNE       L_ST7735_init12
	DEC        R18
	BRNE       L_ST7735_init12
	NOP
;st7735.c,149 :: 		TFT_Write(ST7735_DISPON, CMD);
	CLR        R3
	LDI        R27, 41
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,150 :: 		delay_ms(100);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_ST7735_init14:
	DEC        R16
	BRNE       L_ST7735_init14
	DEC        R17
	BRNE       L_ST7735_init14
	DEC        R18
	BRNE       L_ST7735_init14
;st7735.c,152 :: 		TFT_Write(ST7735_RAMWR, CMD);
	CLR        R3
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,153 :: 		delay_ms(100);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_ST7735_init16:
	DEC        R16
	BRNE       L_ST7735_init16
	DEC        R17
	BRNE       L_ST7735_init16
	DEC        R18
	BRNE       L_ST7735_init16
;st7735.c,154 :: 		}
L_end_ST7735_init:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	RET
; end of _ST7735_init

_TFT_write_word:

;st7735.c,157 :: 		void TFT_write_word(unsigned int value)
;st7735.c,159 :: 		TFT_Write((value >> 0x08), DAT);
	PUSH       R2
	PUSH       R3
	MOV        R16, R3
	LDI        R17, 0
	PUSH       R3
	PUSH       R2
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _TFT_Write+0
	POP        R2
	POP        R3
;st7735.c,160 :: 		TFT_Write((value & 0x00FF), DAT);
	MOV        R16, R2
	ANDI       R16, 255
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _TFT_Write+0
;st7735.c,161 :: 		}
L_end_TFT_write_word:
	POP        R3
	POP        R2
	RET
; end of _TFT_write_word

_TFT_set_display_window:

;st7735.c,164 :: 		void TFT_set_display_window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
;st7735.c,166 :: 		TFT_Write(ST7735_CASET, CMD);
	PUSH       R2
	PUSH       R3
	PUSH       R3
	PUSH       R2
	CLR        R3
	LDI        R27, 42
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,167 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
	POP        R2
;st7735.c,168 :: 		TFT_Write(xs, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CALL       _TFT_Write+0
;st7735.c,169 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,170 :: 		TFT_Write(xe, DAT);
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R4
	CALL       _TFT_Write+0
;st7735.c,172 :: 		TFT_Write(ST7735_RASET, CMD);
	CLR        R3
	LDI        R27, 43
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,173 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
	POP        R3
;st7735.c,174 :: 		TFT_Write(ys, DAT);
	MOV        R2, R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _TFT_Write+0
;st7735.c,175 :: 		TFT_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _TFT_Write+0
;st7735.c,176 :: 		TFT_Write(ye, DAT);
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R5
	CALL       _TFT_Write+0
;st7735.c,178 :: 		TFT_Write(ST7735_RAMWR, CMD);
	CLR        R3
	LDI        R27, 44
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,179 :: 		}
L_end_TFT_set_display_window:
	POP        R3
	POP        R2
	RET
; end of _TFT_set_display_window

_Invert_Display:

;st7735.c,182 :: 		void Invert_Display(unsigned char i)
;st7735.c,184 :: 		if(i == ST7735_INVON)
	PUSH       R2
	PUSH       R3
	LDI        R27, 33
	CP         R2, R27
	BREQ       L__Invert_Display285
	JMP        L_Invert_Display18
L__Invert_Display285:
;st7735.c,186 :: 		TFT_Write(ST7735_INVON, CMD);
	CLR        R3
	LDI        R27, 33
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,187 :: 		}
	JMP        L_Invert_Display19
L_Invert_Display18:
;st7735.c,190 :: 		TFT_Write(ST7735_INVOFF, CMD);
	CLR        R3
	LDI        R27, 32
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,191 :: 		}
L_Invert_Display19:
;st7735.c,192 :: 		}
L_end_Invert_Display:
	POP        R3
	POP        R2
	RET
; end of _Invert_Display

_Swap_Colour:

;st7735.c,195 :: 		unsigned int Swap_Colour(unsigned int colour)
;st7735.c,197 :: 		return ((colour << 0x000B) | (colour & 0x07E0) | (colour >> 0x000B));
	LDI        R27, 11
	MOVW       R18, R2
L__Swap_Colour287:
	LSL        R18
	ROL        R19
	DEC        R27
	BRNE       L__Swap_Colour287
L__Swap_Colour288:
	MOVW       R16, R2
	ANDI       R16, 224
	ANDI       R17, 7
	OR         R18, R16
	OR         R19, R17
	LDI        R27, 11
	MOVW       R16, R2
L__Swap_Colour289:
	LSR        R17
	ROR        R16
	DEC        R27
	BRNE       L__Swap_Colour289
L__Swap_Colour290:
	OR         R16, R18
	OR         R17, R19
;st7735.c,198 :: 		}
L_end_Swap_Colour:
	RET
; end of _Swap_Colour

_Color565:

;st7735.c,201 :: 		unsigned int Color565(unsigned char r, unsigned char g, unsigned char b)
;st7735.c,203 :: 		return (((r & 0xF8) << 0x08) | ((g & 0xFC) << 0x03) | (b >> 0x03));
	MOV        R16, R2
	ANDI       R16, 248
	MOV        R19, R16
	CLR        R18
	MOV        R16, R3
	ANDI       R16, 252
	LDI        R17, 0
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	OR         R18, R16
	OR         R19, R17
	MOV        R16, R4
	LSR        R16
	LSR        R16
	LSR        R16
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
;st7735.c,204 :: 		}
L_end_Color565:
	RET
; end of _Color565

_Set_Rotation:

;st7735.c,207 :: 		void Set_Rotation(unsigned char m)
;st7735.c,209 :: 		unsigned char rotation = 0x00;
	PUSH       R2
	PUSH       R3
;st7735.c,211 :: 		TFT_Write(ST7735_MADCTL, CMD);
	PUSH       R2
	CLR        R3
	LDI        R27, 54
	MOV        R2, R27
	CALL       _TFT_Write+0
	POP        R2
;st7735.c,212 :: 		rotation = (m % 4);
	MOV        R16, R2
	ANDI       R16, 3
; rotation start address is: 16 (R16)
;st7735.c,214 :: 		switch(rotation)
	JMP        L_Set_Rotation20
;st7735.c,216 :: 		case 0:
L_Set_Rotation22:
;st7735.c,218 :: 		TFT_Write((ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 200
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,219 :: 		break;
	JMP        L_Set_Rotation21
;st7735.c,221 :: 		case 1:
L_Set_Rotation23:
;st7735.c,223 :: 		TFT_Write((ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 168
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,224 :: 		break;
	JMP        L_Set_Rotation21
;st7735.c,226 :: 		case 2:
L_Set_Rotation24:
;st7735.c,228 :: 		TFT_Write((ST7735_MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 8
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,229 :: 		break;
	JMP        L_Set_Rotation21
;st7735.c,231 :: 		case 3:
L_Set_Rotation25:
;st7735.c,233 :: 		TFT_Write((ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 104
	MOV        R2, R27
	CALL       _TFT_Write+0
;st7735.c,234 :: 		break;
	JMP        L_Set_Rotation21
;st7735.c,236 :: 		}
L_Set_Rotation20:
	CPI        R16, 0
	BRNE       L__Set_Rotation293
	JMP        L_Set_Rotation22
L__Set_Rotation293:
	CPI        R16, 1
	BRNE       L__Set_Rotation294
	JMP        L_Set_Rotation23
L__Set_Rotation294:
	CPI        R16, 2
	BRNE       L__Set_Rotation295
	JMP        L_Set_Rotation24
L__Set_Rotation295:
	CPI        R16, 3
	BRNE       L__Set_Rotation296
	JMP        L_Set_Rotation25
L__Set_Rotation296:
L_Set_Rotation21:
;st7735.c,238 :: 		if((rotation == 0) || (rotation == 2))
	CPI        R16, 0
	BRNE       L__Set_Rotation297
	JMP        L__Set_Rotation238
L__Set_Rotation297:
	CPI        R16, 2
	BRNE       L__Set_Rotation298
	JMP        L__Set_Rotation237
L__Set_Rotation298:
	JMP        L_Set_Rotation28
L__Set_Rotation238:
L__Set_Rotation237:
;st7735.c,240 :: 		w = TFT_WIDTH;
	LDI        R27, 128
	STS        _w+0, R27
;st7735.c,241 :: 		l = TFT_LENGTH;
	LDI        R27, 160
	STS        _l+0, R27
;st7735.c,242 :: 		}
L_Set_Rotation28:
;st7735.c,243 :: 		if((rotation == 1) || (rotation == 3))
	CPI        R16, 1
	BRNE       L__Set_Rotation299
	JMP        L__Set_Rotation240
L__Set_Rotation299:
	CPI        R16, 3
	BRNE       L__Set_Rotation300
	JMP        L__Set_Rotation239
L__Set_Rotation300:
; rotation end address is: 16 (R16)
	JMP        L_Set_Rotation31
L__Set_Rotation240:
L__Set_Rotation239:
;st7735.c,245 :: 		w = TFT_LENGTH;
	LDI        R27, 160
	STS        _w+0, R27
;st7735.c,246 :: 		l = TFT_WIDTH;
	LDI        R27, 128
	STS        _l+0, R27
;st7735.c,247 :: 		}
L_Set_Rotation31:
;st7735.c,248 :: 		}
L_end_Set_Rotation:
	POP        R3
	POP        R2
	RET
; end of _Set_Rotation

_TFT_fill:

;st7735.c,251 :: 		void TFT_fill(unsigned int colour)
;st7735.c,253 :: 		unsigned int index = pixels;
	PUSH       R4
	PUSH       R5
; index start address is: 18 (R18)
	LDI        R18, 0
	LDI        R19, 80
;st7735.c,255 :: 		TFT_set_display_window(0, 0, (w - 1), (l - 1));
	LDS        R17, _l+0
	SUBI       R17, 1
	LDS        R16, _w+0
	SUBI       R16, 1
	PUSH       R3
	PUSH       R2
	MOV        R5, R17
	MOV        R4, R16
	CLR        R3
	CLR        R2
	CALL       _TFT_set_display_window+0
; index end address is: 18 (R18)
	POP        R2
	POP        R3
;st7735.c,257 :: 		while(index > 0)
L_TFT_fill32:
; index start address is: 18 (R18)
	LDI        R16, 0
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLO       L__TFT_fill302
	JMP        L_TFT_fill33
L__TFT_fill302:
;st7735.c,259 :: 		TFT_write_word(colour);
	CALL       _TFT_write_word+0
;st7735.c,260 :: 		index--;
	MOVW       R16, R18
	SUBI       R16, 1
	SBCI       R17, 0
	MOVW       R18, R16
;st7735.c,261 :: 		}
; index end address is: 18 (R18)
	JMP        L_TFT_fill32
L_TFT_fill33:
;st7735.c,262 :: 		}
L_end_TFT_fill:
	POP        R5
	POP        R4
	RET
; end of _TFT_fill

_TFT_fill_area:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,265 :: 		void TFT_fill_area(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
; colour start address is: 22 (R22)
	LDD        R22, Y+12
	LDD        R23, Y+13
	STD        Y+0, R6
	STD        Y+1, R7
	STD        Y+2, R2
	STD        Y+3, R3
	STD        Y+4, R8
	STD        Y+5, R9
	STD        Y+6, R4
	STD        Y+7, R5
;st7735.c,267 :: 		unsigned int index = 0x0000;
;st7735.c,269 :: 		if(x1 > x2)
	LDD        R18, Y+2
	LDD        R19, Y+3
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__TFT_fill_area304
	JMP        L_TFT_fill_area34
L__TFT_fill_area304:
;st7735.c,271 :: 		swap(&x1, &x2);
	MOVW       R18, R28
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,272 :: 		}
L_TFT_fill_area34:
;st7735.c,273 :: 		if(y1 > y2)
	LDD        R18, Y+6
	LDD        R19, Y+7
	LDD        R16, Y+4
	LDD        R17, Y+5
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__TFT_fill_area305
	JMP        L_TFT_fill_area35
L__TFT_fill_area305:
;st7735.c,275 :: 		swap(&y1, &y2);
	MOVW       R18, R28
	SUBI       R18, 252
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 250
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,276 :: 		}
L_TFT_fill_area35:
;st7735.c,278 :: 		index = (x2 - x1);
	LDD        R0, Y+2
	LDD        R1, Y+3
	LDD        R20, Y+0
	LDD        R21, Y+1
	SUB        R20, R0
	SBC        R21, R1
;st7735.c,279 :: 		index *= (y2 - y1);
	LDD        R0, Y+6
	LDD        R1, Y+7
	LDD        R16, Y+4
	LDD        R17, Y+5
	SUB        R16, R0
	SBC        R17, R1
	CALL       _HWMul_16x16+0
; index start address is: 18 (R18)
	MOVW       R18, R16
;st7735.c,281 :: 		TFT_set_display_window(x1, y1, (x2 - 1), (y2 - 1));
	LDD        R17, Y+4
	SUBI       R17, 1
	LDD        R16, Y+0
	SUBI       R16, 1
	MOV        R5, R17
	MOV        R4, R16
	LDD        R3, Y+6
	LDD        R2, Y+2
	CALL       _TFT_set_display_window+0
; colour end address is: 22 (R22)
; index end address is: 18 (R18)
	MOVW       R20, R18
	MOVW       R18, R22
;st7735.c,283 :: 		while(index)
L_TFT_fill_area36:
; index start address is: 20 (R20)
; colour start address is: 18 (R18)
; colour start address is: 18 (R18)
; colour end address is: 18 (R18)
	MOV        R27, R20
	OR         R27, R21
	BRNE       L__TFT_fill_area306
	JMP        L_TFT_fill_area37
L__TFT_fill_area306:
; colour end address is: 18 (R18)
;st7735.c,285 :: 		TFT_write_word(colour);
; colour start address is: 18 (R18)
	PUSH       R3
	PUSH       R2
	MOVW       R2, R18
	CALL       _TFT_write_word+0
	POP        R2
	POP        R3
;st7735.c,286 :: 		index--;
	MOVW       R16, R20
	SUBI       R16, 1
	SBCI       R17, 0
	MOVW       R20, R16
;st7735.c,287 :: 		};
; colour end address is: 18 (R18)
; index end address is: 20 (R20)
	JMP        L_TFT_fill_area36
L_TFT_fill_area37:
;st7735.c,288 :: 		}
L_end_TFT_fill_area:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _TFT_fill_area

_Draw_Pixel:

;st7735.c,291 :: 		void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour)
;st7735.c,293 :: 		unsigned int col = Swap_Colour(colour);
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R3
	PUSH       R2
	MOVW       R2, R4
	CALL       _Swap_Colour+0
	POP        R2
	POP        R3
; col start address is: 18 (R18)
	MOVW       R18, R16
;st7735.c,294 :: 		TFT_set_display_window(x_pos, y_pos, (1 + x_pos), (1 + y_pos));
	MOV        R17, R3
	SUBI       R17, 255
	MOV        R16, R2
	SUBI       R16, 255
	MOV        R5, R17
	MOV        R4, R16
	CALL       _TFT_set_display_window+0
;st7735.c,295 :: 		TFT_write_word(col);
	MOVW       R2, R18
; col end address is: 18 (R18)
	CALL       _TFT_write_word+0
;st7735.c,296 :: 		}
L_end_Draw_Pixel:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	RET
; end of _Draw_Pixel

_Draw_Point:

;st7735.c,299 :: 		void Draw_Point(unsigned int x_pos, unsigned int y_pos, unsigned char pen_width, unsigned int colour)
;st7735.c,301 :: 		Draw_Circle(x_pos, y_pos, pen_width, YES, colour);
	PUSH       R7
	PUSH       R8
	PUSH       R8
	PUSH       R7
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 0
	MOV        R7, R27
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,302 :: 		}
L_end_Draw_Point:
	POP        R8
	POP        R7
	RET
; end of _Draw_Point

_Draw_Line:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,305 :: 		void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
; colour start address is: 20 (R20)
	LDD        R20, Y+0
	LDD        R21, Y+1
;st7735.c,307 :: 		signed int dx = 0x0000;
;st7735.c,308 :: 		signed int dy = 0x0000;
;st7735.c,309 :: 		signed int stepx = 0x0000;
;st7735.c,310 :: 		signed int stepy = 0x0000;
;st7735.c,311 :: 		signed int fraction = 0x0000;
;st7735.c,313 :: 		dy = (y2 - y1);
	MOVW       R18, R8
	SUB        R18, R4
	SBC        R19, R5
; dy start address is: 12 (R12)
	MOVW       R12, R18
;st7735.c,314 :: 		dx = (x2 - x1);
	MOVW       R16, R6
	SUB        R16, R2
	SBC        R17, R3
; dx start address is: 22 (R22)
	MOVW       R22, R16
;st7735.c,316 :: 		if(dy < 0)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Line310
	JMP        L_Draw_Line38
L__Draw_Line310:
;st7735.c,318 :: 		dy = -dy;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R12
	SBC        R17, R13
	MOVW       R12, R16
;st7735.c,319 :: 		stepy = -1;
; stepy start address is: 18 (R18)
	LDI        R18, 255
	LDI        R19, 255
;st7735.c,320 :: 		}
; stepy end address is: 18 (R18)
	JMP        L_Draw_Line39
L_Draw_Line38:
;st7735.c,323 :: 		stepy = 1;
; stepy start address is: 18 (R18)
	LDI        R18, 1
	LDI        R19, 0
; stepy end address is: 18 (R18)
; dy end address is: 12 (R12)
;st7735.c,324 :: 		}
L_Draw_Line39:
;st7735.c,326 :: 		if(dx < 0)
; stepy start address is: 18 (R18)
; dy start address is: 12 (R12)
	LDI        R16, 0
	LDI        R17, 0
	CP         R22, R16
	CPC        R23, R17
	BRLT       L__Draw_Line311
	JMP        L_Draw_Line40
L__Draw_Line311:
;st7735.c,328 :: 		dx = -dx;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R22
	SBC        R17, R23
	MOVW       R22, R16
;st7735.c,329 :: 		stepx = -1;
; stepx start address is: 10 (R10)
	LDI        R27, 255
	MOV        R10, R27
	MOV        R11, R27
;st7735.c,330 :: 		}
; stepx end address is: 10 (R10)
	JMP        L_Draw_Line41
L_Draw_Line40:
;st7735.c,333 :: 		stepx = 1;
; stepx start address is: 10 (R10)
	LDI        R27, 1
	MOV        R10, R27
	LDI        R27, 0
	MOV        R11, R27
; stepx end address is: 10 (R10)
; dx end address is: 22 (R22)
;st7735.c,334 :: 		}
L_Draw_Line41:
;st7735.c,336 :: 		dx <<= 0x01;
; stepx start address is: 10 (R10)
; dx start address is: 22 (R22)
	MOVW       R16, R22
	LSL        R16
	ROL        R17
; dx end address is: 22 (R22)
; dx start address is: 24 (R24)
	MOVW       R24, R16
;st7735.c,337 :: 		dy <<= 0x01;
	MOVW       R16, R12
	LSL        R16
	ROL        R17
; dy end address is: 12 (R12)
; dy start address is: 22 (R22)
	MOVW       R22, R16
;st7735.c,339 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R19
	PUSH       R18
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R18
	POP        R19
;st7735.c,341 :: 		if(dx > dy)
	CP         R22, R24
	CPC        R23, R25
	BRLT       L__Draw_Line312
	JMP        L_Draw_Line42
L__Draw_Line312:
;st7735.c,343 :: 		fraction = (dy - (dx >> 1));
	MOVW       R16, R24
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOVW       R16, R22
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 12 (R12)
	MOVW       R12, R16
; stepy end address is: 18 (R18)
; fraction end address is: 12 (R12)
	MOVW       R14, R18
;st7735.c,344 :: 		while(x1 != x2)
L_Draw_Line43:
; fraction start address is: 12 (R12)
; stepy start address is: 14 (R14)
; dy start address is: 22 (R22)
; dy end address is: 22 (R22)
; dx start address is: 24 (R24)
; dx end address is: 24 (R24)
; stepx start address is: 10 (R10)
; stepx end address is: 10 (R10)
; stepy start address is: 14 (R14)
; stepy end address is: 14 (R14)
; colour start address is: 20 (R20)
; colour end address is: 20 (R20)
	CP         R2, R6
	CPC        R3, R7
	BRNE       L__Draw_Line313
	JMP        L_Draw_Line44
L__Draw_Line313:
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; stepy end address is: 14 (R14)
; colour end address is: 20 (R20)
;st7735.c,346 :: 		if(fraction >= 0)
; colour start address is: 20 (R20)
; stepy start address is: 14 (R14)
; stepx start address is: 10 (R10)
; dx start address is: 24 (R24)
; dy start address is: 22 (R22)
	LDI        R16, 0
	LDI        R17, 0
	CP         R12, R16
	CPC        R13, R17
	BRGE       L__Draw_Line314
	JMP        L__Draw_Line241
L__Draw_Line314:
;st7735.c,348 :: 		y1 += stepy;
	MOVW       R16, R14
	ADD        R16, R4
	ADC        R17, R5
	MOVW       R4, R16
;st7735.c,349 :: 		fraction -= dx;
	MOVW       R16, R12
	SUB        R16, R24
	SBC        R17, R25
	MOVW       R12, R16
; fraction end address is: 12 (R12)
;st7735.c,350 :: 		}
	JMP        L_Draw_Line45
L__Draw_Line241:
;st7735.c,346 :: 		if(fraction >= 0)
;st7735.c,350 :: 		}
L_Draw_Line45:
;st7735.c,351 :: 		x1 += stepx;
; fraction start address is: 12 (R12)
	MOVW       R18, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R2, R18
;st7735.c,352 :: 		fraction += dy;
	MOVW       R16, R22
	ADD        R16, R12
	ADC        R17, R13
	MOVW       R12, R16
;st7735.c,354 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	MOV        R2, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,355 :: 		}
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; stepy end address is: 14 (R14)
; colour end address is: 20 (R20)
; fraction end address is: 12 (R12)
	JMP        L_Draw_Line43
L_Draw_Line44:
;st7735.c,356 :: 		}
	JMP        L_Draw_Line46
L_Draw_Line42:
;st7735.c,359 :: 		fraction = (dx - (dy >> 1));
; colour start address is: 20 (R20)
; stepx start address is: 10 (R10)
; dx start address is: 24 (R24)
; dy start address is: 22 (R22)
; stepy start address is: 18 (R18)
	MOVW       R16, R22
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOVW       R16, R24
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 12 (R12)
	MOVW       R12, R16
; stepy end address is: 18 (R18)
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; colour end address is: 20 (R20)
; fraction end address is: 12 (R12)
	PUSH       R23
	PUSH       R22
	MOVW       R22, R24
	MOVW       R24, R10
	MOVW       R10, R18
	MOVW       R18, R12
	MOVW       R12, R20
	POP        R20
	POP        R21
;st7735.c,361 :: 		while(y1 != y2)
L_Draw_Line47:
; colour start address is: 12 (R12)
; stepy start address is: 10 (R10)
; stepx start address is: 24 (R24)
; dx start address is: 22 (R22)
; dy start address is: 20 (R20)
; fraction start address is: 18 (R18)
; dy start address is: 20 (R20)
; dy end address is: 20 (R20)
; dx start address is: 22 (R22)
; dx end address is: 22 (R22)
; stepx start address is: 24 (R24)
; stepx end address is: 24 (R24)
; stepy start address is: 10 (R10)
; stepy end address is: 10 (R10)
; colour start address is: 12 (R12)
; colour end address is: 12 (R12)
	CP         R4, R8
	CPC        R5, R9
	BRNE       L__Draw_Line315
	JMP        L_Draw_Line48
L__Draw_Line315:
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 12 (R12)
;st7735.c,363 :: 		if (fraction >= 0)
; colour start address is: 12 (R12)
; stepy start address is: 10 (R10)
; stepx start address is: 24 (R24)
; dx start address is: 22 (R22)
; dy start address is: 20 (R20)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRGE       L__Draw_Line316
	JMP        L__Draw_Line242
L__Draw_Line316:
;st7735.c,365 :: 		x1 += stepx;
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;st7735.c,366 :: 		fraction -= dy;
	MOVW       R16, R18
	SUB        R16, R20
	SBC        R17, R21
; fraction end address is: 18 (R18)
; fraction start address is: 14 (R14)
	MOVW       R14, R16
; fraction end address is: 14 (R14)
;st7735.c,367 :: 		}
	JMP        L_Draw_Line49
L__Draw_Line242:
;st7735.c,363 :: 		if (fraction >= 0)
	MOVW       R14, R18
;st7735.c,367 :: 		}
L_Draw_Line49:
;st7735.c,368 :: 		y1 += stepy;
; fraction start address is: 14 (R14)
	MOVW       R18, R10
	ADD        R18, R4
	ADC        R19, R5
	MOVW       R4, R18
;st7735.c,369 :: 		fraction += dx;
	MOVW       R16, R22
	ADD        R16, R14
	ADC        R17, R15
; fraction end address is: 14 (R14)
; fraction start address is: 16 (R16)
;st7735.c,370 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R17
	PUSH       R16
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R12
	MOV        R3, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R16
	POP        R17
;st7735.c,371 :: 		}
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 12 (R12)
; fraction end address is: 16 (R16)
	MOVW       R18, R16
	JMP        L_Draw_Line47
L_Draw_Line48:
;st7735.c,372 :: 		}
L_Draw_Line46:
;st7735.c,373 :: 		}
L_end_Draw_Line:
	POP        R29
	POP        R28
	RET
; end of _Draw_Line

_Draw_V_Line:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 4
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,376 :: 		void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour)
	PUSH       R4
	PUSH       R5
	STD        Y+0, R6
	STD        Y+1, R7
	STD        Y+2, R4
	STD        Y+3, R5
;st7735.c,378 :: 		signed int pos = 0;
;st7735.c,379 :: 		signed int temp = 0;
;st7735.c,381 :: 		if(y1 > y2)
	LDD        R18, Y+2
	LDD        R19, Y+3
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_V_Line318
	JMP        L_Draw_V_Line50
L__Draw_V_Line318:
;st7735.c,383 :: 		swap(&y1, &y2);
	MOVW       R18, R28
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	PUSH       R3
	PUSH       R2
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
	POP        R2
	POP        R3
;st7735.c,384 :: 		}
L_Draw_V_Line50:
;st7735.c,386 :: 		while(y2 > (y1 - 1))
L_Draw_V_Line51:
	LDD        R18, Y+2
	LDD        R19, Y+3
	SUBI       R18, 1
	SBCI       R19, 0
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_V_Line319
	JMP        L_Draw_V_Line52
L__Draw_V_Line319:
;st7735.c,388 :: 		Draw_Pixel(x1, y2, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R8
	LDD        R3, Y+0
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,389 :: 		y2--;
	LDD        R16, Y+0
	LDD        R17, Y+1
	SUBI       R16, 1
	SBCI       R17, 0
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,390 :: 		}
	JMP        L_Draw_V_Line51
L_Draw_V_Line52:
;st7735.c,391 :: 		}
L_end_Draw_V_Line:
	POP        R5
	POP        R4
	ADIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_V_Line

_Draw_H_Line:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 4
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,394 :: 		void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour)
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	STD        Y+0, R4
	STD        Y+1, R5
	STD        Y+2, R2
	STD        Y+3, R3
;st7735.c,396 :: 		signed int pos = 0;
;st7735.c,397 :: 		signed int temp = 0;
;st7735.c,399 :: 		if(x1 > x2)
	LDD        R18, Y+2
	LDD        R19, Y+3
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_H_Line321
	JMP        L_Draw_H_Line53
L__Draw_H_Line321:
;st7735.c,401 :: 		swap(&x1, &x2);
	MOVW       R18, R28
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,402 :: 		}
L_Draw_H_Line53:
;st7735.c,404 :: 		while(x2 > (x1 - 1))
L_Draw_H_Line54:
	LDD        R18, Y+2
	LDD        R19, Y+3
	SUBI       R18, 1
	SBCI       R19, 0
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_H_Line322
	JMP        L_Draw_H_Line55
L__Draw_H_Line322:
;st7735.c,406 :: 		Draw_Pixel(x2, y1, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R8
	MOV        R3, R6
	LDD        R2, Y+0
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,407 :: 		x2--;
	LDD        R16, Y+0
	LDD        R17, Y+1
	SUBI       R16, 1
	SBCI       R17, 0
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,408 :: 		}
	JMP        L_Draw_H_Line54
L_Draw_H_Line55:
;st7735.c,409 :: 		}
L_end_Draw_H_Line:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_H_Line

_Draw_Triangle:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 32
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,412 :: 		void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour)
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
	LDD        R16, Y+38
	LDD        R17, Y+39
	STD        Y+38, R16
	STD        Y+39, R17
; fill start address is: 18 (R18)
	LDD        R18, Y+40
	LDD        R16, Y+41
	LDD        R17, Y+42
	STD        Y+41, R16
	STD        Y+42, R17
	STD        Y+24, R8
	STD        Y+25, R9
	STD        Y+26, R4
	STD        Y+27, R5
	STD        Y+28, R6
	STD        Y+29, R7
	STD        Y+30, R2
	STD        Y+31, R3
;st7735.c,414 :: 		signed int a = 0;
	LDI        R27, 0
	STD        Y+0, R27
	STD        Y+1, R27
	LDI        R27, 0
	STD        Y+2, R27
	STD        Y+3, R27
;st7735.c,415 :: 		signed int b = 0;
;st7735.c,416 :: 		signed int sa = 0;
;st7735.c,417 :: 		signed int sb = 0;
;st7735.c,418 :: 		signed int yp = 0;
;st7735.c,419 :: 		signed int last = 0;
;st7735.c,420 :: 		signed int dx12 = 0;
;st7735.c,421 :: 		signed int dx23 = 0;
;st7735.c,422 :: 		signed int dx13 = 0;
;st7735.c,423 :: 		signed int dy12 = 0;
;st7735.c,424 :: 		signed int dy23 = 0;
;st7735.c,425 :: 		signed int dy13 = 0;
;st7735.c,427 :: 		switch(fill)
	JMP        L_Draw_Triangle56
; fill end address is: 18 (R18)
;st7735.c,429 :: 		case YES:
L_Draw_Triangle58:
;st7735.c,431 :: 		if(y1 > y2)
	LDD        R18, Y+26
	LDD        R19, Y+27
	LDD        R16, Y+24
	LDD        R17, Y+25
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Triangle324
	JMP        L_Draw_Triangle59
L__Draw_Triangle324:
;st7735.c,433 :: 		swap(&y1, &y2);
	MOVW       R18, R28
	SUBI       R18, 232
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 230
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,434 :: 		swap(&x1, &x2);
	MOVW       R18, R28
	SUBI       R18, 228
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 226
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,435 :: 		}
L_Draw_Triangle59:
;st7735.c,436 :: 		if(y2 > y3)
	LDD        R18, Y+24
	LDD        R19, Y+25
	LDD        R16, Y+38
	LDD        R17, Y+39
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Triangle325
	JMP        L_Draw_Triangle60
L__Draw_Triangle325:
;st7735.c,438 :: 		swap(&y3, &y2);
	MOVW       R18, R28
	SUBI       R18, 232
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 218
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,439 :: 		swap(&x3, &x2);
	MOVW       R18, R28
	SUBI       R18, 228
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 220
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,440 :: 		}
L_Draw_Triangle60:
;st7735.c,441 :: 		if(y1 > y2)
	LDD        R18, Y+26
	LDD        R19, Y+27
	LDD        R16, Y+24
	LDD        R17, Y+25
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Triangle326
	JMP        L_Draw_Triangle61
L__Draw_Triangle326:
;st7735.c,443 :: 		swap(&y1, &y2);
	MOVW       R18, R28
	SUBI       R18, 232
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 230
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,444 :: 		swap(&x1, &x2);
	MOVW       R18, R28
	SUBI       R18, 228
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 226
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,445 :: 		}
L_Draw_Triangle61:
;st7735.c,447 :: 		if(y1 == y3)
	LDD        R18, Y+26
	LDD        R19, Y+27
	LDD        R16, Y+38
	LDD        R17, Y+39
	CP         R18, R16
	CPC        R19, R17
	BREQ       L__Draw_Triangle327
	JMP        L_Draw_Triangle62
L__Draw_Triangle327:
;st7735.c,449 :: 		a = b = x1;
	LDD        R16, Y+30
	LDD        R17, Y+31
	STD        Y+2, R16
	STD        Y+3, R17
	LDD        R16, Y+30
	LDD        R17, Y+31
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,451 :: 		if(x2 < a)
	LDD        R18, Y+28
	LDD        R19, Y+29
	LDD        R16, Y+30
	LDD        R17, Y+31
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Triangle328
	JMP        L_Draw_Triangle63
L__Draw_Triangle328:
;st7735.c,453 :: 		a = x2;
	LDD        R16, Y+28
	LDD        R17, Y+29
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,454 :: 		}
	JMP        L_Draw_Triangle64
L_Draw_Triangle63:
;st7735.c,455 :: 		else if(x2 > b)
	LDD        R18, Y+28
	LDD        R19, Y+29
	LDD        R16, Y+2
	LDD        R17, Y+3
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Triangle329
	JMP        L_Draw_Triangle65
L__Draw_Triangle329:
;st7735.c,457 :: 		b = x2;
	LDD        R16, Y+28
	LDD        R17, Y+29
	STD        Y+2, R16
	STD        Y+3, R17
;st7735.c,458 :: 		}
L_Draw_Triangle65:
L_Draw_Triangle64:
;st7735.c,459 :: 		if(x2 < a)
	LDD        R18, Y+28
	LDD        R19, Y+29
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Triangle330
	JMP        L_Draw_Triangle66
L__Draw_Triangle330:
;st7735.c,461 :: 		a = x3;
	LDD        R16, Y+36
	LDD        R17, Y+37
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,462 :: 		}
	JMP        L_Draw_Triangle67
L_Draw_Triangle66:
;st7735.c,463 :: 		else if(x3 > b)
	LDD        R18, Y+36
	LDD        R19, Y+37
	LDD        R16, Y+2
	LDD        R17, Y+3
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Triangle331
	JMP        L_Draw_Triangle68
L__Draw_Triangle331:
;st7735.c,465 :: 		b = x3;
	LDD        R16, Y+36
	LDD        R17, Y+37
	STD        Y+2, R16
	STD        Y+3, R17
;st7735.c,466 :: 		}
L_Draw_Triangle68:
L_Draw_Triangle67:
;st7735.c,468 :: 		Draw_H_Line(a, (a + (b - (a + 1))), y1, colour);
	LDD        R18, Y+0
	LDD        R19, Y+1
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R0, R16
	LDD        R16, Y+2
	LDD        R17, Y+3
	SUB        R16, R0
	SBC        R17, R1
	ADD        R16, R18
	ADC        R17, R19
	LDD        R8, Y+41
	LDD        R9, Y+42
	LDD        R6, Y+26
	LDD        R7, Y+27
	MOVW       R4, R16
	LDD        R2, Y+0
	LDD        R3, Y+1
	CALL       _Draw_H_Line+0
;st7735.c,469 :: 		return;
	JMP        L_end_Draw_Triangle
;st7735.c,470 :: 		}
L_Draw_Triangle62:
;st7735.c,472 :: 		dx12 = (x2 - x1);
	LDD        R0, Y+30
	LDD        R1, Y+31
	LDD        R16, Y+28
	LDD        R17, Y+29
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+12, R16
	STD        Y+13, R17
;st7735.c,473 :: 		dy12 = (y2 - y1);
	LDD        R0, Y+26
	LDD        R1, Y+27
	LDD        R16, Y+24
	LDD        R17, Y+25
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+18, R16
	STD        Y+19, R17
;st7735.c,474 :: 		dx13 = (x3 - x1);
	LDD        R0, Y+30
	LDD        R1, Y+31
	LDD        R16, Y+36
	LDD        R17, Y+37
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+16, R16
	STD        Y+17, R17
;st7735.c,475 :: 		dy13 = (y3 - y1);
	LDD        R0, Y+26
	LDD        R1, Y+27
	LDD        R16, Y+38
	LDD        R17, Y+39
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+22, R16
	STD        Y+23, R17
;st7735.c,476 :: 		dx23 = (x3 - x2);
	LDD        R0, Y+28
	LDD        R1, Y+29
	LDD        R16, Y+36
	LDD        R17, Y+37
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+14, R16
	STD        Y+15, R17
;st7735.c,477 :: 		dy23 = (y3 - y2);
	LDD        R0, Y+24
	LDD        R1, Y+25
	LDD        R16, Y+38
	LDD        R17, Y+39
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+20, R16
	STD        Y+21, R17
;st7735.c,478 :: 		sa = 0,
	LDI        R27, 0
	STD        Y+4, R27
	STD        Y+5, R27
;st7735.c,479 :: 		sb = 0;
	LDI        R27, 0
	STD        Y+6, R27
	STD        Y+7, R27
;st7735.c,481 :: 		if(y2 == y3)
	LDD        R18, Y+24
	LDD        R19, Y+25
	LDD        R16, Y+38
	LDD        R17, Y+39
	CP         R18, R16
	CPC        R19, R17
	BREQ       L__Draw_Triangle332
	JMP        L_Draw_Triangle69
L__Draw_Triangle332:
;st7735.c,483 :: 		last = y2;
	LDD        R16, Y+24
	LDD        R17, Y+25
	STD        Y+10, R16
	STD        Y+11, R17
;st7735.c,484 :: 		}
	JMP        L_Draw_Triangle70
L_Draw_Triangle69:
;st7735.c,487 :: 		last = (y2 - 1);
	LDD        R16, Y+24
	LDD        R17, Y+25
	SUBI       R16, 1
	SBCI       R17, 0
	STD        Y+10, R16
	STD        Y+11, R17
;st7735.c,488 :: 		}
L_Draw_Triangle70:
;st7735.c,490 :: 		for(yp = y1; yp <= last; yp++)
	LDD        R16, Y+26
	LDD        R17, Y+27
	STD        Y+8, R16
	STD        Y+9, R17
L_Draw_Triangle71:
	LDD        R18, Y+8
	LDD        R19, Y+9
	LDD        R16, Y+10
	LDD        R17, Y+11
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__Draw_Triangle333
	JMP        L_Draw_Triangle72
L__Draw_Triangle333:
;st7735.c,492 :: 		a = (x1 + (sa / dy12));
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R20, Y+18
	LDD        R21, Y+19
	LDD        R16, Y+4
	LDD        R17, Y+5
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	LDD        R18, Y+30
	LDD        R19, Y+31
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,493 :: 		b = (x1 + (sb / dy13));
	LDD        R20, Y+22
	LDD        R21, Y+23
	LDD        R16, Y+6
	LDD        R17, Y+7
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	LDD        R18, Y+30
	LDD        R19, Y+31
	MOVW       R20, R16
	ADD        R20, R18
	ADC        R21, R19
	STD        Y+2, R20
	STD        Y+3, R21
;st7735.c,494 :: 		sa += dx12;
	LDD        R18, Y+4
	LDD        R19, Y+5
	LDD        R16, Y+12
	LDD        R17, Y+13
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+4, R16
	STD        Y+5, R17
;st7735.c,495 :: 		sb += dx13;
	LDD        R18, Y+6
	LDD        R19, Y+7
	LDD        R16, Y+16
	LDD        R17, Y+17
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+6, R16
	STD        Y+7, R17
;st7735.c,496 :: 		if(a > b)
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R20, R16
	CPC        R21, R17
	BRLT       L__Draw_Triangle334
	JMP        L_Draw_Triangle74
L__Draw_Triangle334:
;st7735.c,498 :: 		swap(&a, &b);
	MOVW       R18, R28
	SUBI       R18, 254
	SBCI       R19, 255
	MOVW       R16, R28
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,499 :: 		}
L_Draw_Triangle74:
;st7735.c,500 :: 		Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
	LDD        R18, Y+0
	LDD        R19, Y+1
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R0, R16
	LDD        R16, Y+2
	LDD        R17, Y+3
	SUB        R16, R0
	SBC        R17, R1
	ADD        R16, R18
	ADC        R17, R19
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R8, Y+41
	LDD        R9, Y+42
	LDD        R6, Y+8
	LDD        R7, Y+9
	MOVW       R4, R16
	LDD        R2, Y+0
	LDD        R3, Y+1
	CALL       _Draw_H_Line+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
;st7735.c,490 :: 		for(yp = y1; yp <= last; yp++)
	LDD        R16, Y+8
	LDD        R17, Y+9
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
;st7735.c,501 :: 		}
	JMP        L_Draw_Triangle71
L_Draw_Triangle72:
;st7735.c,503 :: 		sa = (dx23 * (yp - y2));
	LDD        R0, Y+24
	LDD        R1, Y+25
	LDD        R16, Y+8
	LDD        R17, Y+9
	SUB        R16, R0
	SBC        R17, R1
	LDD        R20, Y+14
	LDD        R21, Y+15
	CALL       _HWMul_16x16+0
	STD        Y+4, R16
	STD        Y+5, R17
;st7735.c,504 :: 		sb = (dx13 * (yp - y1));
	LDD        R0, Y+26
	LDD        R1, Y+27
	LDD        R16, Y+8
	LDD        R17, Y+9
	SUB        R16, R0
	SBC        R17, R1
	LDD        R20, Y+16
	LDD        R21, Y+17
	CALL       _HWMul_16x16+0
	STD        Y+6, R16
	STD        Y+7, R17
;st7735.c,505 :: 		for(; yp <= y3; yp++)
L_Draw_Triangle75:
	LDD        R18, Y+8
	LDD        R19, Y+9
	LDD        R16, Y+38
	LDD        R17, Y+39
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__Draw_Triangle335
	JMP        L_Draw_Triangle76
L__Draw_Triangle335:
;st7735.c,507 :: 		a = (x2 + (sa / dy23));
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R20, Y+20
	LDD        R21, Y+21
	LDD        R16, Y+4
	LDD        R17, Y+5
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	LDD        R18, Y+28
	LDD        R19, Y+29
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
;st7735.c,508 :: 		b = (x1 + (sb / dy13));
	LDD        R20, Y+22
	LDD        R21, Y+23
	LDD        R16, Y+6
	LDD        R17, Y+7
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	LDD        R18, Y+30
	LDD        R19, Y+31
	MOVW       R20, R16
	ADD        R20, R18
	ADC        R21, R19
	STD        Y+2, R20
	STD        Y+3, R21
;st7735.c,509 :: 		sa += dx23;
	LDD        R18, Y+4
	LDD        R19, Y+5
	LDD        R16, Y+14
	LDD        R17, Y+15
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+4, R16
	STD        Y+5, R17
;st7735.c,510 :: 		sb += dx13;
	LDD        R18, Y+6
	LDD        R19, Y+7
	LDD        R16, Y+16
	LDD        R17, Y+17
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+6, R16
	STD        Y+7, R17
;st7735.c,512 :: 		if(a > b)
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R20, R16
	CPC        R21, R17
	BRLT       L__Draw_Triangle336
	JMP        L_Draw_Triangle78
L__Draw_Triangle336:
;st7735.c,514 :: 		swap(&a, &b);
	MOVW       R18, R28
	SUBI       R18, 254
	SBCI       R19, 255
	MOVW       R16, R28
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,515 :: 		}
L_Draw_Triangle78:
;st7735.c,516 :: 		Draw_H_Line(a, (a + (b - (a + 1))), yp, colour);
	LDD        R18, Y+0
	LDD        R19, Y+1
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R0, R16
	LDD        R16, Y+2
	LDD        R17, Y+3
	SUB        R16, R0
	SBC        R17, R1
	ADD        R16, R18
	ADC        R17, R19
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R8, Y+41
	LDD        R9, Y+42
	LDD        R6, Y+8
	LDD        R7, Y+9
	MOVW       R4, R16
	LDD        R2, Y+0
	LDD        R3, Y+1
	CALL       _Draw_H_Line+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
;st7735.c,505 :: 		for(; yp <= y3; yp++)
	LDD        R16, Y+8
	LDD        R17, Y+9
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
;st7735.c,517 :: 		}
	JMP        L_Draw_Triangle75
L_Draw_Triangle76:
;st7735.c,520 :: 		break;
	JMP        L_Draw_Triangle57
;st7735.c,522 :: 		default:
L_Draw_Triangle79:
;st7735.c,524 :: 		Draw_Line(x1, y1, x2, y2, colour);
	LDD        R8, Y+24
	LDD        R9, Y+25
	LDD        R6, Y+28
	LDD        R7, Y+29
	LDD        R4, Y+26
	LDD        R5, Y+27
	LDD        R2, Y+30
	LDD        R3, Y+31
	LDD        R16, Y+41
	LDD        R17, Y+42
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,525 :: 		Draw_Line(x2, y2, x3, y3, colour);
	LDD        R8, Y+38
	LDD        R9, Y+39
	LDD        R6, Y+36
	LDD        R7, Y+37
	LDD        R4, Y+24
	LDD        R5, Y+25
	LDD        R2, Y+28
	LDD        R3, Y+29
	LDD        R16, Y+41
	LDD        R17, Y+42
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,526 :: 		Draw_Line(x3, y3, x1, y1, colour);
	LDD        R8, Y+26
	LDD        R9, Y+27
	LDD        R6, Y+30
	LDD        R7, Y+31
	LDD        R4, Y+38
	LDD        R5, Y+39
	LDD        R2, Y+36
	LDD        R3, Y+37
	LDD        R16, Y+41
	LDD        R17, Y+42
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,527 :: 		break;
	JMP        L_Draw_Triangle57
;st7735.c,529 :: 		}
L_Draw_Triangle56:
; fill start address is: 18 (R18)
	CPI        R18, 1
	BRNE       L__Draw_Triangle337
	JMP        L_Draw_Triangle58
L__Draw_Triangle337:
; fill end address is: 18 (R18)
	JMP        L_Draw_Triangle79
L_Draw_Triangle57:
;st7735.c,530 :: 		}
L_end_Draw_Triangle:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 31
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Triangle

_Draw_Rectangle:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 4
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,533 :: 		void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour)
; fill start address is: 18 (R18)
	LDD        R18, Y+8
	LDD        R16, Y+9
	STD        Y+9, R16
	LDD        R16, Y+10
	LDD        R17, Y+11
	STD        Y+10, R16
	STD        Y+11, R17
	LDD        R16, Y+12
	LDD        R17, Y+13
	STD        Y+12, R16
	STD        Y+13, R17
;st7735.c,535 :: 		signed int i = 0x0000;
;st7735.c,536 :: 		signed int xmin = 0x0000;
;st7735.c,537 :: 		signed int xmax = 0x0000;
;st7735.c,538 :: 		signed int ymin = 0x0000;
;st7735.c,539 :: 		signed int ymax = 0x0000;
;st7735.c,541 :: 		switch(fill)
	JMP        L_Draw_Rectangle80
; fill end address is: 18 (R18)
;st7735.c,543 :: 		case YES:
L_Draw_Rectangle82:
;st7735.c,545 :: 		if(x1 < x2)
	CP         R2, R6
	CPC        R3, R7
	BRLT       L__Draw_Rectangle339
	JMP        L_Draw_Rectangle83
L__Draw_Rectangle339:
;st7735.c,547 :: 		xmin = x1;
; xmin start address is: 16 (R16)
	MOVW       R16, R2
;st7735.c,548 :: 		xmax = x2;
; xmax start address is: 21 (R21)
	MOV        R21, R6
	MOV        R22, R7
;st7735.c,549 :: 		}
	MOVW       R12, R16
; xmin end address is: 16 (R16)
; xmax end address is: 21 (R21)
	MOV        R23, R21
	MOV        R24, R22
	JMP        L_Draw_Rectangle84
L_Draw_Rectangle83:
;st7735.c,552 :: 		xmin = x2;
; xmin start address is: 16 (R16)
	MOVW       R16, R6
;st7735.c,553 :: 		xmax = x1;
; xmax start address is: 21 (R21)
	MOV        R21, R2
	MOV        R22, R3
; xmin end address is: 16 (R16)
; xmax end address is: 21 (R21)
	MOVW       R12, R16
	MOV        R23, R21
	MOV        R24, R22
;st7735.c,554 :: 		}
L_Draw_Rectangle84:
;st7735.c,556 :: 		if(y1 < y2)
; xmax start address is: 23 (R23)
; xmin start address is: 12 (R12)
	CP         R4, R8
	CPC        R5, R9
	BRLT       L__Draw_Rectangle340
	JMP        L_Draw_Rectangle85
L__Draw_Rectangle340:
;st7735.c,558 :: 		ymin = y1;
	STD        Y+0, R4
	STD        Y+1, R5
;st7735.c,559 :: 		ymax = y2;
	STD        Y+2, R8
	STD        Y+3, R9
;st7735.c,560 :: 		}
	JMP        L_Draw_Rectangle86
L_Draw_Rectangle85:
;st7735.c,563 :: 		ymin = y2;
	STD        Y+0, R8
	STD        Y+1, R9
;st7735.c,564 :: 		ymax = y1;
	STD        Y+2, R4
	STD        Y+3, R5
;st7735.c,565 :: 		}
L_Draw_Rectangle86:
;st7735.c,567 :: 		for(; xmin <= xmax; ++xmin)
	MOV        R16, R23
	MOV        R17, R24
; xmax end address is: 23 (R23)
; xmin end address is: 12 (R12)
L_Draw_Rectangle87:
; xmin start address is: 12 (R12)
; xmax start address is: 16 (R16)
	CP         R16, R12
	CPC        R17, R13
	BRGE       L__Draw_Rectangle341
	JMP        L_Draw_Rectangle88
L__Draw_Rectangle341:
;st7735.c,569 :: 		for(i = ymin; i <= ymax; ++i)
; i start address is: 10 (R10)
	LDD        R10, Y+0
	LDD        R11, Y+1
; xmax end address is: 16 (R16)
; i end address is: 10 (R10)
; xmin end address is: 12 (R12)
	MOV        R23, R16
	MOV        R24, R17
	MOVW       R18, R10
L_Draw_Rectangle90:
; i start address is: 18 (R18)
; xmax start address is: 23 (R23)
; xmin start address is: 12 (R12)
	LDD        R16, Y+2
	LDD        R17, Y+3
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__Draw_Rectangle342
	JMP        L_Draw_Rectangle91
L__Draw_Rectangle342:
;st7735.c,571 :: 		Draw_Pixel(xmin, i, colour);
	PUSH       R19
	PUSH       R18
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R4, Y+10
	LDD        R5, Y+11
	MOV        R3, R18
	MOV        R2, R12
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R18
	POP        R19
;st7735.c,569 :: 		for(i = ymin; i <= ymax; ++i)
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
; i end address is: 18 (R18)
; i start address is: 10 (R10)
	MOVW       R10, R16
;st7735.c,572 :: 		}
; i end address is: 10 (R10)
	MOVW       R18, R10
	JMP        L_Draw_Rectangle90
L_Draw_Rectangle91:
;st7735.c,567 :: 		for(; xmin <= xmax; ++xmin)
	MOVW       R16, R12
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R12, R16
;st7735.c,573 :: 		}
	MOV        R16, R23
	MOV        R17, R24
; xmax end address is: 23 (R23)
; xmin end address is: 12 (R12)
	JMP        L_Draw_Rectangle87
L_Draw_Rectangle88:
;st7735.c,575 :: 		break;
	JMP        L_Draw_Rectangle81
;st7735.c,577 :: 		default:
L_Draw_Rectangle93:
;st7735.c,579 :: 		Draw_V_Line(x1, y1, y2, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	MOVW       R6, R8
	LDD        R8, Y+10
	LDD        R9, Y+11
	CALL       _Draw_V_Line+0
	POP        R6
	POP        R7
	POP        R8
	POP        R9
;st7735.c,580 :: 		Draw_V_Line(x2, y1, y2, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R3
	PUSH       R2
	MOVW       R2, R6
	MOVW       R6, R8
	LDD        R8, Y+10
	LDD        R9, Y+11
	CALL       _Draw_V_Line+0
	POP        R2
	POP        R3
	POP        R6
	POP        R7
;st7735.c,581 :: 		Draw_H_Line(x1, x2, y1, colour);
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R7
	PUSH       R6
	LDD        R8, Y+10
	LDD        R9, Y+11
	MOVW       R6, R4
	POP        R4
	POP        R5
	CALL       _Draw_H_Line+0
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
;st7735.c,582 :: 		Draw_H_Line(x1, x2, y2, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	MOVW       R4, R6
	MOVW       R6, R8
	LDD        R8, Y+10
	LDD        R9, Y+11
	CALL       _Draw_H_Line+0
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
;st7735.c,583 :: 		break;
	JMP        L_Draw_Rectangle81
;st7735.c,585 :: 		}
L_Draw_Rectangle80:
; fill start address is: 18 (R18)
	CPI        R18, 1
	BRNE       L__Draw_Rectangle343
	JMP        L_Draw_Rectangle82
L__Draw_Rectangle343:
; fill end address is: 18 (R18)
	JMP        L_Draw_Rectangle93
L_Draw_Rectangle81:
;st7735.c,587 :: 		if(type != SQUARE)
	LDD        R16, Y+9
	CPI        R16, 0
	BRNE       L__Draw_Rectangle344
	JMP        L_Draw_Rectangle94
L__Draw_Rectangle344:
;st7735.c,589 :: 		Draw_Pixel(x1, y1, back_colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	LDD        R4, Y+12
	LDD        R5, Y+13
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
;st7735.c,590 :: 		Draw_Pixel(x1, y2, back_colour);
	PUSH       R3
	PUSH       R2
	LDD        R4, Y+12
	LDD        R5, Y+13
	MOV        R3, R8
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,591 :: 		Draw_Pixel(x2, y1, back_colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	LDD        R4, Y+12
	LDD        R5, Y+13
	MOV        R2, R6
	CALL       _Draw_Pixel+0
;st7735.c,592 :: 		Draw_Pixel(x2, y2, back_colour);
	LDD        R4, Y+12
	LDD        R5, Y+13
	MOV        R3, R8
	MOV        R2, R6
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,593 :: 		}
L_Draw_Rectangle94:
;st7735.c,594 :: 		}
L_end_Draw_Rectangle:
	ADIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Rectangle

_Draw_H_Bar:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,597 :: 		void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
; bar_value start address is: 24 (R24)
	LDD        R24, Y+0
	LDD        R25, Y+1
; border_colour start address is: 10 (R10)
	LDD        R10, Y+2
	LDD        R11, Y+3
; bar_colour start address is: 12 (R12)
	LDD        R12, Y+4
	LDD        R13, Y+5
; back_colour start address is: 14 (R14)
	LDD        R14, Y+6
	LDD        R15, Y+7
; border start address is: 16 (R16)
	LDD        R16, Y+8
;st7735.c,599 :: 		switch(border)
	JMP        L_Draw_H_Bar95
; border end address is: 16 (R16)
;st7735.c,601 :: 		case YES:
L_Draw_H_Bar97:
;st7735.c,603 :: 		Draw_Rectangle((x1 + 1), (y1 + 1), (x1 + bar_value), (y1 + bar_width - 1), YES, SQUARE, bar_colour, back_colour);
	MOVW       R16, R8
	ADD        R16, R6
	ADC        R17, R7
	MOVW       R22, R16
	SUBI       R22, 1
	SBCI       R23, 0
	MOVW       R20, R24
	ADD        R20, R2
	ADC        R21, R3
	MOVW       R18, R6
	SUBI       R18, 255
	SBCI       R19, 255
	MOVW       R16, R2
	SUBI       R16, 255
	SBCI       R17, 255
	PUSH       R11
	PUSH       R10
	PUSH       R25
	PUSH       R24
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R22
	MOVW       R6, R20
	MOVW       R4, R18
	MOVW       R2, R16
	PUSH       R15
	PUSH       R14
	PUSH       R13
	PUSH       R12
; bar_colour end address is: 12 (R12)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R24
	POP        R25
;st7735.c,604 :: 		Draw_Rectangle((x2 - 1), (y1 + 1), (x1 + bar_value + 1), (y1 + bar_width - 1), YES, SQUARE, back_colour, back_colour);
	MOVW       R16, R8
	ADD        R16, R6
	ADC        R17, R7
	MOVW       R22, R16
	SUBI       R22, 1
	SBCI       R23, 0
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
; bar_value end address is: 24 (R24)
	MOVW       R20, R16
	SUBI       R20, 255
	SBCI       R21, 255
	MOVW       R18, R6
	SUBI       R18, 255
	SBCI       R19, 255
	MOVW       R16, R4
	SUBI       R16, 1
	SBCI       R17, 0
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R22
	MOVW       R6, R20
	MOVW       R4, R18
	MOVW       R2, R16
	PUSH       R15
	PUSH       R14
	PUSH       R15
	PUSH       R14
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R10
	POP        R11
;st7735.c,605 :: 		Draw_Rectangle(x1, y1, x2, (y1 + bar_width), NO, SQUARE, border_colour, back_colour);
	MOVW       R16, R8
	ADD        R16, R6
	ADC        R17, R7
	PUSH       R7
	PUSH       R6
	MOVW       R8, R16
	MOVW       R6, R4
	POP        R4
	POP        R5
	PUSH       R15
	PUSH       R14
; back_colour end address is: 14 (R14)
	PUSH       R11
	PUSH       R10
; border_colour end address is: 10 (R10)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,606 :: 		break;
	JMP        L_Draw_H_Bar96
;st7735.c,608 :: 		default:
L_Draw_H_Bar98:
;st7735.c,610 :: 		Draw_Rectangle(x1, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, bar_colour, back_colour);
; back_colour start address is: 14 (R14)
; bar_colour start address is: 12 (R12)
; bar_value start address is: 24 (R24)
	MOVW       R18, R8
	ADD        R18, R6
	ADC        R19, R7
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
	PUSH       R25
	PUSH       R24
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	MOVW       R8, R18
	MOVW       R4, R6
	MOVW       R6, R16
	PUSH       R15
	PUSH       R14
	PUSH       R13
	PUSH       R12
; bar_colour end address is: 12 (R12)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R24
	POP        R25
;st7735.c,611 :: 		Draw_Rectangle(x2, y1, (x1 + bar_value), (y1 + bar_width), YES, SQUARE, back_colour, back_colour);
	MOVW       R18, R8
	ADD        R18, R6
	ADC        R19, R7
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
; bar_value end address is: 24 (R24)
	MOVW       R8, R18
	MOVW       R2, R4
	MOVW       R4, R6
	MOVW       R6, R16
	PUSH       R15
	PUSH       R14
	PUSH       R15
	PUSH       R14
; back_colour end address is: 14 (R14)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,612 :: 		break;
	JMP        L_Draw_H_Bar96
;st7735.c,614 :: 		}
L_Draw_H_Bar95:
; border start address is: 16 (R16)
; back_colour start address is: 14 (R14)
; bar_colour start address is: 12 (R12)
; border_colour start address is: 10 (R10)
; bar_value start address is: 24 (R24)
	CPI        R16, 1
	BRNE       L__Draw_H_Bar346
	JMP        L_Draw_H_Bar97
L__Draw_H_Bar346:
; border_colour end address is: 10 (R10)
; border end address is: 16 (R16)
	JMP        L_Draw_H_Bar98
; bar_value end address is: 24 (R24)
; bar_colour end address is: 12 (R12)
; back_colour end address is: 14 (R14)
L_Draw_H_Bar96:
;st7735.c,615 :: 		}
L_end_Draw_H_Bar:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	POP        R29
	POP        R28
	RET
; end of _Draw_H_Bar

_Draw_V_Bar:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,618 :: 		void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border)
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
; bar_value start address is: 24 (R24)
	LDD        R24, Y+0
	LDD        R25, Y+1
; border_colour start address is: 10 (R10)
	LDD        R10, Y+2
	LDD        R11, Y+3
; bar_colour start address is: 12 (R12)
	LDD        R12, Y+4
	LDD        R13, Y+5
; back_colour start address is: 14 (R14)
	LDD        R14, Y+6
	LDD        R15, Y+7
; border start address is: 16 (R16)
	LDD        R16, Y+8
;st7735.c,620 :: 		switch(border)
	JMP        L_Draw_V_Bar99
; border end address is: 16 (R16)
;st7735.c,622 :: 		case YES:
L_Draw_V_Bar101:
;st7735.c,624 :: 		Draw_Rectangle((x1 + 1), (y2 - 1), (x1 + bar_width - 1), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
	MOVW       R22, R6
	SUB        R22, R24
	SBC        R23, R25
	MOVW       R16, R8
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R20, R16
	SUBI       R20, 1
	SBCI       R21, 0
	MOVW       R18, R6
	SUBI       R18, 1
	SBCI       R19, 0
	MOVW       R16, R2
	SUBI       R16, 255
	SBCI       R17, 255
	PUSH       R11
	PUSH       R10
	PUSH       R25
	PUSH       R24
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R22
	MOVW       R6, R20
	MOVW       R4, R18
	MOVW       R2, R16
	PUSH       R15
	PUSH       R14
	PUSH       R13
	PUSH       R12
; bar_colour end address is: 12 (R12)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R24
	POP        R25
;st7735.c,625 :: 		Draw_Rectangle((x1 + 1), (y2 - bar_value - 1), (x1 + bar_width - 1), (y1 + 1), YES, SQUARE, back_colour, back_colour);
	MOVW       R22, R4
	SUBI       R22, 255
	SBCI       R23, 255
	MOVW       R16, R8
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R20, R16
	SUBI       R20, 1
	SBCI       R21, 0
	MOVW       R16, R6
	SUB        R16, R24
	SBC        R17, R25
; bar_value end address is: 24 (R24)
	MOVW       R18, R16
	SUBI       R18, 1
	SBCI       R19, 0
	MOVW       R16, R2
	SUBI       R16, 255
	SBCI       R17, 255
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R22
	MOVW       R6, R20
	MOVW       R4, R18
	MOVW       R2, R16
	PUSH       R15
	PUSH       R14
	PUSH       R15
	PUSH       R14
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R10
	POP        R11
;st7735.c,626 :: 		Draw_Rectangle(x1, y1, (x1 + bar_width), y2, NO, SQUARE, border_colour, back_colour);
	MOVW       R16, R8
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R8, R6
	MOVW       R6, R16
	PUSH       R15
	PUSH       R14
; back_colour end address is: 14 (R14)
	PUSH       R11
	PUSH       R10
; border_colour end address is: 10 (R10)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,627 :: 		break;
	JMP        L_Draw_V_Bar100
;st7735.c,629 :: 		default:
L_Draw_V_Bar102:
;st7735.c,631 :: 		Draw_Rectangle(x1, y2, (x1 + bar_width), (y2 - bar_value), YES, SQUARE, bar_colour, back_colour);
; back_colour start address is: 14 (R14)
; bar_colour start address is: 12 (R12)
; bar_value start address is: 24 (R24)
	MOVW       R18, R6
	SUB        R18, R24
	SBC        R19, R25
	MOVW       R16, R8
	ADD        R16, R2
	ADC        R17, R3
	PUSH       R25
	PUSH       R24
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	MOVW       R8, R18
	MOVW       R4, R6
	MOVW       R6, R16
	PUSH       R15
	PUSH       R14
	PUSH       R13
	PUSH       R12
; bar_colour end address is: 12 (R12)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R24
	POP        R25
;st7735.c,632 :: 		Draw_Rectangle(x1, (y2 - bar_value), (x1 + bar_width), y1, YES, SQUARE, back_colour, back_colour);
	MOVW       R18, R8
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R6
	SUB        R16, R24
	SBC        R17, R25
; bar_value end address is: 24 (R24)
	MOVW       R8, R4
	MOVW       R6, R18
	MOVW       R4, R16
	PUSH       R15
	PUSH       R14
	PUSH       R15
	PUSH       R14
; back_colour end address is: 14 (R14)
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,633 :: 		break;
	JMP        L_Draw_V_Bar100
;st7735.c,635 :: 		}
L_Draw_V_Bar99:
; border start address is: 16 (R16)
; back_colour start address is: 14 (R14)
; bar_colour start address is: 12 (R12)
; border_colour start address is: 10 (R10)
; bar_value start address is: 24 (R24)
	CPI        R16, 1
	BRNE       L__Draw_V_Bar348
	JMP        L_Draw_V_Bar101
L__Draw_V_Bar348:
; border_colour end address is: 10 (R10)
; border end address is: 16 (R16)
	JMP        L_Draw_V_Bar102
; bar_value end address is: 24 (R24)
; bar_colour end address is: 12 (R12)
; back_colour end address is: 14 (R14)
L_Draw_V_Bar100:
;st7735.c,636 :: 		}
L_end_Draw_V_Bar:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R29
	POP        R28
	RET
; end of _Draw_V_Bar

_Draw_Circle:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,639 :: 		void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour)
	PUSH       R9
; colour start address is: 18 (R18)
	LDD        R18, Y+6
	LDD        R19, Y+7
;st7735.c,641 :: 		signed int a = 0x0000;
; a start address is: 11 (R11)
	CLR        R11
	CLR        R12
;st7735.c,642 :: 		signed int b = 0x0000;
;st7735.c,643 :: 		signed int p = 0x0000;
;st7735.c,645 :: 		b = radius;
; b start address is: 24 (R24)
	MOVW       R24, R6
;st7735.c,646 :: 		p = (1 - b);
	LDI        R16, 1
	LDI        R17, 0
	SUB        R16, R6
	SBC        R17, R7
	STD        Y+0, R16
	STD        Y+1, R17
; colour end address is: 18 (R18)
; b end address is: 24 (R24)
; a end address is: 11 (R11)
	MOVW       R22, R24
	MOVW       R24, R18
	MOV        R9, R11
	MOV        R10, R12
;st7735.c,648 :: 		do
	JMP        L_Draw_Circle103
L__Draw_Circle243:
;st7735.c,682 :: 		}while(a <= b);
	MOV        R9, R11
	MOV        R10, R12
;st7735.c,648 :: 		do
L_Draw_Circle103:
;st7735.c,650 :: 		switch(fill)
; colour start address is: 24 (R24)
; b start address is: 22 (R22)
; a start address is: 9 (R9)
; colour start address is: 24 (R24)
; colour end address is: 24 (R24)
	JMP        L_Draw_Circle106
; colour end address is: 24 (R24)
;st7735.c,652 :: 		case YES:
L_Draw_Circle108:
;st7735.c,654 :: 		Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
; colour start address is: 24 (R24)
	MOVW       R20, R22
	ADD        R20, R4
	ADC        R21, R5
	MOV        R18, R9
	MOV        R19, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R9
	SBC        R17, R10
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,655 :: 		Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
	MOVW       R20, R4
	SUB        R20, R22
	SBC        R21, R23
	MOV        R18, R9
	MOV        R19, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R9
	SBC        R17, R10
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,656 :: 		Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
	MOV        R20, R9
	MOV        R21, R10
	ADD        R20, R4
	ADC        R21, R5
	MOVW       R18, R22
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R22
	SBC        R17, R23
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,657 :: 		Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
	MOVW       R20, R4
	SUB        R20, R9
	SBC        R21, R10
	MOVW       R18, R22
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R22
	SBC        R17, R23
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,658 :: 		break;
	JMP        L_Draw_Circle107
;st7735.c,660 :: 		default:
L_Draw_Circle109:
;st7735.c,662 :: 		Draw_Pixel((xc + a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	ADD        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,663 :: 		Draw_Pixel((xc + b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R9
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,664 :: 		Draw_Pixel((xc - a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	SUB        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,665 :: 		Draw_Pixel((xc - b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R9
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,666 :: 		Draw_Pixel((xc + b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R9
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,667 :: 		Draw_Pixel((xc + a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	ADD        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,668 :: 		Draw_Pixel((xc - a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	SUB        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,669 :: 		Draw_Pixel((xc - b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R9
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,670 :: 		break;
	JMP        L_Draw_Circle107
;st7735.c,672 :: 		}
L_Draw_Circle106:
	LDI        R27, 1
	CP         R8, R27
	BRNE       L__Draw_Circle350
	JMP        L_Draw_Circle108
L__Draw_Circle350:
	JMP        L_Draw_Circle109
L_Draw_Circle107:
;st7735.c,674 :: 		if(p < 0)
	LDD        R18, Y+0
	LDD        R19, Y+1
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Circle351
	JMP        L_Draw_Circle110
L__Draw_Circle351:
;st7735.c,676 :: 		p += (0x03 + (0x02 * a++));
	MOV        R16, R9
	MOV        R17, R10
	LSL        R16
	ROL        R17
	MOVW       R18, R16
	SUBI       R18, 253
	SBCI       R19, 255
	LDD        R16, Y+0
	LDD        R17, Y+1
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
	MOV        R16, R9
	MOV        R17, R10
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 9 (R9)
; a start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
;st7735.c,677 :: 		}
; a end address is: 11 (R11)
	JMP        L_Draw_Circle111
L_Draw_Circle110:
;st7735.c,680 :: 		p += (0x05 + (0x02 * ((a++) - (b--))));
; a start address is: 9 (R9)
	MOV        R16, R9
	MOV        R17, R10
	SUB        R16, R22
	SBC        R17, R23
	LSL        R16
	ROL        R17
	MOVW       R18, R16
	SUBI       R18, 251
	SBCI       R19, 255
	LDD        R16, Y+0
	LDD        R17, Y+1
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
	MOV        R16, R9
	MOV        R17, R10
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 9 (R9)
; a start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
	MOVW       R16, R22
	SUBI       R16, 1
	SBCI       R17, 0
	MOVW       R22, R16
; b end address is: 22 (R22)
; a end address is: 11 (R11)
;st7735.c,681 :: 		}
L_Draw_Circle111:
;st7735.c,682 :: 		}while(a <= b);
; b start address is: 22 (R22)
; a start address is: 11 (R11)
	CP         R22, R11
	CPC        R23, R12
	BRLT       L__Draw_Circle352
	JMP        L__Draw_Circle243
L__Draw_Circle352:
; colour end address is: 24 (R24)
; b end address is: 22 (R22)
; a end address is: 11 (R11)
;st7735.c,683 :: 		}
L_end_Draw_Circle:
	POP        R9
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Circle

_Draw_Font_Pixel:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,686 :: 		void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size)
;st7735.c,688 :: 		unsigned char i = (pixel_size * pixel_size);
	PUSH       R4
	PUSH       R5
	MUL        R6, R6
	MOVW       R16, R0
	STD        Y+0, R16
;st7735.c,689 :: 		unsigned int col = Swap_Colour(colour);
	PUSH       R3
	PUSH       R2
	MOVW       R2, R4
	CALL       _Swap_Colour+0
	POP        R2
	POP        R3
	STD        Y+1, R16
	STD        Y+2, R17
;st7735.c,691 :: 		TFT_set_display_window(x_pos, y_pos, (x_pos + pixel_size - 1), (y_pos + pixel_size - 1));
	MOV        R16, R3
	ADD        R16, R6
	MOV        R17, R16
	SUBI       R17, 1
	MOV        R16, R2
	ADD        R16, R6
	SUBI       R16, 1
	MOV        R5, R17
	MOV        R4, R16
	CALL       _TFT_set_display_window+0
;st7735.c,693 :: 		while(i > 0)
L_Draw_Font_Pixel112:
	LDD        R17, Y+0
	LDI        R16, 0
	CP         R16, R17
	BRLO       L__Draw_Font_Pixel354
	JMP        L_Draw_Font_Pixel113
L__Draw_Font_Pixel354:
;st7735.c,695 :: 		TFT_write_word(col);
	PUSH       R3
	PUSH       R2
	LDD        R2, Y+1
	LDD        R3, Y+2
	CALL       _TFT_write_word+0
	POP        R2
	POP        R3
;st7735.c,696 :: 		i--;
	LDD        R16, Y+0
	SUBI       R16, 1
	STD        Y+0, R16
;st7735.c,697 :: 		};
	JMP        L_Draw_Font_Pixel112
L_Draw_Font_Pixel113:
;st7735.c,698 :: 		}
L_end_Draw_Font_Pixel:
	POP        R5
	POP        R4
	ADIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Font_Pixel

_print_char:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,701 :: 		void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
; back_colour start address is: 17 (R17)
	LDD        R17, Y+0
	LDD        R18, Y+1
;st7735.c,703 :: 		unsigned char i = 0x00;
;st7735.c,704 :: 		unsigned char j = 0x00;
;st7735.c,705 :: 		unsigned char value = 0x00;
;st7735.c,707 :: 		if(font_size <= 0)
	LDI        R16, 0
	CP         R16, R6
	BRSH       L__print_char356
	JMP        L_print_char114
L__print_char356:
;st7735.c,709 :: 		font_size = 1;
	LDI        R27, 1
	MOV        R6, R27
;st7735.c,710 :: 		}
L_print_char114:
;st7735.c,712 :: 		if(x_pos < font_size)
	CP         R2, R6
	LDI        R27, 0
	CPC        R3, R27
	BRLO       L__print_char357
	JMP        L_print_char115
L__print_char357:
;st7735.c,714 :: 		x_pos = font_size;
	MOV        R2, R6
	LDI        R27, 0
	MOV        R3, R27
;st7735.c,715 :: 		}
L_print_char115:
;st7735.c,717 :: 		for(i = 0x00; i < 0x05; i++)
; i start address is: 22 (R22)
	LDI        R22, 0
; back_colour end address is: 17 (R17)
; i end address is: 22 (R22)
	MOV        R20, R17
	MOV        R21, R18
L_print_char116:
; i start address is: 22 (R22)
; back_colour start address is: 20 (R20)
	CPI        R22, 5
	BRLO       L__print_char358
	JMP        L_print_char117
L__print_char358:
;st7735.c,719 :: 		for(j = 0x00; j < 0x08; j++)
; j start address is: 23 (R23)
	LDI        R23, 0
; back_colour end address is: 20 (R20)
; j end address is: 23 (R23)
; i end address is: 22 (R22)
L_print_char119:
; j start address is: 23 (R23)
; back_colour start address is: 20 (R20)
; i start address is: 22 (R22)
	CPI        R23, 8
	BRLO       L__print_char359
	JMP        L_print_char120
L__print_char359:
;st7735.c,722 :: 		value = ((font[((unsigned char)ch) - 0x20][i]));
	MOV        R16, R9
	LDI        R17, 0
	SUBI       R16, 32
	SBCI       R17, 0
	PUSH       R21
	PUSH       R20
	LDI        R20, 5
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	POP        R21
	LDI        R18, #lo_addr(comms_demo_font+0)
	LDI        R19, hi_addr(comms_demo_font+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R22
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
;st7735.c,724 :: 		if(((value >> j) & 0x01) != 0x00)
	MOV        R27, R23
	TST        R27
	BREQ       L__print_char361
L__print_char360:
	LSR        R16
	DEC        R27
	BRNE       L__print_char360
L__print_char361:
	ANDI       R16, 1
	CPI        R16, 0
	BRNE       L__print_char362
	JMP        L_print_char122
L__print_char362:
;st7735.c,726 :: 		Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOV        R4, R7
	MOV        R5, R8
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,727 :: 		}
	JMP        L_print_char123
L_print_char122:
;st7735.c,730 :: 		Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,731 :: 		}
L_print_char123:
;st7735.c,733 :: 		y_pos += font_size;
	MOV        R16, R6
	LDI        R17, 0
	ADD        R16, R4
	ADC        R17, R5
	MOVW       R4, R16
;st7735.c,719 :: 		for(j = 0x00; j < 0x08; j++)
	MOV        R16, R23
	SUBI       R16, 255
	MOV        R23, R16
;st7735.c,734 :: 		}
; j end address is: 23 (R23)
	JMP        L_print_char119
L_print_char120:
;st7735.c,736 :: 		y_pos -= (font_size << 0x03);
	MOV        R16, R6
	LDI        R17, 0
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	MOVW       R0, R16
	MOVW       R16, R4
	SUB        R16, R0
	SBC        R17, R1
	MOVW       R4, R16
;st7735.c,737 :: 		x_pos += font_size;
	MOV        R16, R6
	LDI        R17, 0
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;st7735.c,717 :: 		for(i = 0x00; i < 0x05; i++)
	MOV        R16, R22
	SUBI       R16, 255
	MOV        R22, R16
;st7735.c,738 :: 		}
; back_colour end address is: 20 (R20)
; i end address is: 22 (R22)
	JMP        L_print_char116
L_print_char117:
;st7735.c,739 :: 		}
L_end_print_char:
	POP        R29
	POP        R28
	RET
; end of _print_char

_print_str:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,742 :: 		void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch)
	PUSH       R9
; back_colour start address is: 20 (R20)
	LDD        R20, Y+0
	LDD        R21, Y+1
; ch start address is: 22 (R22)
; ch start address is: 22 (R22)
	LDD        R22, Y+2
	LDD        R23, Y+3
; back_colour end address is: 20 (R20)
; ch end address is: 22 (R22)
;st7735.c,744 :: 		do
L_print_str124:
;st7735.c,746 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, *ch++);
; ch start address is: 22 (R22)
; back_colour start address is: 20 (R20)
	MOVW       R30, R22
	LD         R16, Z
	PUSH       R21
	PUSH       R20
	PUSH       R23
	PUSH       R22
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R9, R16
	PUSH       R21
	PUSH       R20
	CALL       _print_char+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R22
	POP        R23
	POP        R20
	POP        R21
	MOVW       R18, R22
	SUBI       R18, 255
	SBCI       R19, 255
	MOVW       R22, R18
; ch end address is: 22 (R22)
;st7735.c,747 :: 		x_pos += (font_size * 0x06);
	LDI        R16, 6
	MUL        R6, R16
	MOVW       R16, R0
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;st7735.c,748 :: 		}while((*ch >= 0x20) && (*ch <= 0x7F));
	MOVW       R30, R18
	LD         R16, Z
	CPI        R16, 32
	BRSH       L__print_str364
	JMP        L__print_str246
L__print_str364:
; ch end address is: 22 (R22)
; ch start address is: 22 (R22)
	MOVW       R30, R22
	LD         R17, Z
	LDI        R16, 127
	CP         R16, R17
	BRSH       L__print_str365
	JMP        L__print_str245
L__print_str365:
; ch end address is: 22 (R22)
	JMP        L_print_str124
L__print_str246:
L__print_str245:
;st7735.c,750 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R27, 32
	MOV        R9, R27
	PUSH       R21
	PUSH       R20
; back_colour end address is: 20 (R20)
	CALL       _print_char+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
;st7735.c,751 :: 		}
L_end_print_str:
	POP        R9
	POP        R29
	POP        R28
	RET
; end of _print_str

_print_C:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 10
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,754 :: 		void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
	LDD        R16, Y+14
	LDD        R17, Y+15
	STD        Y+14, R16
	STD        Y+15, R17
; value start address is: 21 (R21)
	LDD        R21, Y+16
	LDD        R22, Y+17
;st7735.c,756 :: 		unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
	LDI        R27, 32
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
	LDI        R27, 32
	STD        Y+4, R27
	LDI        R27, 32
	STD        Y+5, R27
;st7735.c,758 :: 		if(value < 0x00)
	LDI        R16, 0
	LDI        R17, 0
	CP         R21, R16
	CPC        R22, R17
	BRLT       L__print_C367
	JMP        L_print_C129
L__print_C367:
;st7735.c,760 :: 		ch[0] = 0x2D;
	MOVW       R30, R28
	LDI        R27, 45
	ST         Z, R27
;st7735.c,761 :: 		value = -value;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R21
	SBC        R17, R22
; value end address is: 21 (R21)
; value start address is: 16 (R16)
;st7735.c,762 :: 		}
	MOV        R19, R16
	MOV        R20, R17
; value end address is: 16 (R16)
	JMP        L_print_C130
L_print_C129:
;st7735.c,765 :: 		ch[0] = 0x20;
; value start address is: 21 (R21)
	MOVW       R30, R28
	LDI        R27, 32
	ST         Z, R27
; value end address is: 21 (R21)
	MOV        R19, R21
	MOV        R20, R22
;st7735.c,766 :: 		}
L_print_C130:
;st7735.c,768 :: 		if((value > 99) && (value <= 999))
; value start address is: 19 (R19)
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRLT       L__print_C368
	JMP        L__print_C251
L__print_C368:
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C369
	JMP        L__print_C250
L__print_C369:
L__print_C249:
;st7735.c,770 :: 		ch[1] = ((value / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,771 :: 		ch[2] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,772 :: 		ch[3] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,773 :: 		}
	JMP        L_print_C134
;st7735.c,768 :: 		if((value > 99) && (value <= 999))
L__print_C251:
; value start address is: 19 (R19)
L__print_C250:
;st7735.c,774 :: 		else if((value > 9) && (value <= 99))
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRLT       L__print_C370
	JMP        L__print_C253
L__print_C370:
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C371
	JMP        L__print_C252
L__print_C371:
L__print_C248:
;st7735.c,776 :: 		ch[1] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,777 :: 		ch[2] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,778 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,779 :: 		}
	JMP        L_print_C138
;st7735.c,774 :: 		else if((value > 9) && (value <= 99))
L__print_C253:
; value start address is: 19 (R19)
L__print_C252:
;st7735.c,780 :: 		else if((value >= 0) && (value <= 9))
	LDI        R16, 0
	LDI        R17, 0
	CP         R19, R16
	CPC        R20, R17
	BRGE       L__print_C372
	JMP        L__print_C255
L__print_C372:
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C373
	JMP        L__print_C254
L__print_C373:
L__print_C247:
;st7735.c,782 :: 		ch[1] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,783 :: 		ch[2] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 2
	LDI        R27, 32
	ST         Z, R27
;st7735.c,784 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,780 :: 		else if((value >= 0) && (value <= 9))
L__print_C255:
L__print_C254:
;st7735.c,785 :: 		}
L_print_C138:
L_print_C134:
;st7735.c,787 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+14
	LDD        R17, Y+15
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,788 :: 		}
L_end_print_C:
	ADIW       R28, 9
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_C

_print_I:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 10
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,791 :: 		void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
	LDD        R16, Y+14
	LDD        R17, Y+15
	STD        Y+14, R16
	STD        Y+15, R17
	LDD        R16, Y+16
	LDD        R17, Y+17
	STD        Y+16, R16
	STD        Y+17, R17
;st7735.c,793 :: 		unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
	LDI        R27, 32
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
	LDI        R27, 32
	STD        Y+4, R27
	LDI        R27, 32
	STD        Y+5, R27
;st7735.c,795 :: 		if(value < 0)
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__print_I375
	JMP        L_print_I142
L__print_I375:
;st7735.c,797 :: 		ch[0] = 0x2D;
	MOVW       R30, R28
	LDI        R27, 45
	ST         Z, R27
;st7735.c,798 :: 		value = -value;
	LDD        R0, Y+16
	LDD        R1, Y+17
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+16, R16
	STD        Y+17, R17
;st7735.c,799 :: 		}
	JMP        L_print_I143
L_print_I142:
;st7735.c,802 :: 		ch[0] = 0x20;
	MOVW       R30, R28
	LDI        R27, 32
	ST         Z, R27
;st7735.c,803 :: 		}
L_print_I143:
;st7735.c,805 :: 		if(value > 9999)
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 15
	LDI        R17, 39
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I376
	JMP        L_print_I144
L__print_I376:
;st7735.c,807 :: 		ch[1] = ((value / 10000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,808 :: 		ch[2] = (((value % 10000)/ 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 232
	LDI        R21, 3
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,809 :: 		ch[3] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,810 :: 		ch[4] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,811 :: 		ch[5] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 251
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,812 :: 		}
	JMP        L_print_I145
L_print_I144:
;st7735.c,814 :: 		else if((value > 999) && (value <= 9999))
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I377
	JMP        L__print_I260
L__print_I377:
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 15
	LDI        R17, 39
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I378
	JMP        L__print_I259
L__print_I378:
L__print_I258:
;st7735.c,816 :: 		ch[1] = (((value % 10000)/ 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 232
	LDI        R21, 3
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,817 :: 		ch[2] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,818 :: 		ch[3] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,819 :: 		ch[4] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,820 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,821 :: 		}
	JMP        L_print_I149
;st7735.c,814 :: 		else if((value > 999) && (value <= 9999))
L__print_I260:
L__print_I259:
;st7735.c,822 :: 		else if((value > 99) && (value <= 999))
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I379
	JMP        L__print_I262
L__print_I379:
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I380
	JMP        L__print_I261
L__print_I380:
L__print_I257:
;st7735.c,824 :: 		ch[1] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,825 :: 		ch[2] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,826 :: 		ch[3] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,827 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,828 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,829 :: 		}
	JMP        L_print_I153
;st7735.c,822 :: 		else if((value > 99) && (value <= 999))
L__print_I262:
L__print_I261:
;st7735.c,830 :: 		else if((value > 9) && (value <= 99))
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I381
	JMP        L__print_I264
L__print_I381:
	LDD        R18, Y+16
	LDD        R19, Y+17
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I382
	JMP        L__print_I263
L__print_I382:
L__print_I256:
;st7735.c,832 :: 		ch[1] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,833 :: 		ch[2] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,834 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,835 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,836 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,837 :: 		}
	JMP        L_print_I157
;st7735.c,830 :: 		else if((value > 9) && (value <= 99))
L__print_I264:
L__print_I263:
;st7735.c,840 :: 		ch[1] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+16
	LDD        R17, Y+17
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,841 :: 		ch[2] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 2
	LDI        R27, 32
	ST         Z, R27
;st7735.c,842 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,843 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,844 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,845 :: 		}
L_print_I157:
L_print_I153:
L_print_I149:
L_print_I145:
;st7735.c,847 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+14
	LDD        R17, Y+15
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,848 :: 		}
L_end_print_I:
	ADIW       R28, 9
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_I

_print_D:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,851 :: 		void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points)
	LDD        R16, Y+12
	LDD        R17, Y+13
	STD        Y+12, R16
	STD        Y+13, R17
	LDD        R16, Y+14
	LDD        R17, Y+15
	STD        Y+14, R16
	STD        Y+15, R17
;st7735.c,853 :: 		unsigned char ch[4] = {0x2E, 0x20, 0x20, 0x20};
	LDI        R27, 46
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
;st7735.c,855 :: 		ch[1] = ((value / 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,857 :: 		if(points > 1)
	LDI        R16, 1
	CP         R16, R9
	BRLO       L__print_D384
	JMP        L_print_D158
L__print_D384:
;st7735.c,859 :: 		ch[2] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,861 :: 		if(points > 2)
	LDI        R16, 2
	CP         R16, R9
	BRLO       L__print_D385
	JMP        L_print_D159
L__print_D385:
;st7735.c,863 :: 		ch[3] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,865 :: 		if(points > 3)
	LDI        R16, 3
	CP         R16, R9
	BRLO       L__print_D386
	JMP        L_print_D160
L__print_D386:
;st7735.c,867 :: 		ch[4] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,868 :: 		}
L_print_D160:
;st7735.c,869 :: 		}
L_print_D159:
;st7735.c,870 :: 		}
L_print_D158:
;st7735.c,872 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,873 :: 		}
L_end_print_D:
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_D

_print_F:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,876 :: 		void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points)
	PUSH       R2
	PUSH       R3
	PUSH       R9
	LDD        R16, Y+12
	LDD        R17, Y+13
	STD        Y+12, R16
	STD        Y+13, R17
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	STD        Y+14, R16
	STD        Y+15, R17
	STD        Y+16, R18
	STD        Y+17, R19
;st7735.c,878 :: 		signed long tmp = 0x0000;
;st7735.c,880 :: 		tmp = value;
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,881 :: 		print_I(x_pos, y_pos, font_size, colour, back_colour, tmp);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_I+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
;st7735.c,882 :: 		tmp = ((value - tmp) * 10000);
	LDD        R16, Y+0
	LDD        R17, Y+1
	LDD        R18, Y+2
	LDD        R19, Y+3
	CALL       _float_slong2fp+0
	STD        Y+4, R16
	STD        Y+5, R17
	STD        Y+6, R18
	STD        Y+7, R19
	PUSH       R3
	PUSH       R2
	LDD        R20, Y+4
	LDD        R21, Y+5
	LDD        R22, Y+6
	LDD        R23, Y+7
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_fpsub1+0
	LDI        R20, 0
	LDI        R21, 64
	LDI        R22, 28
	LDI        R23, 70
	CALL       _float_fpmul1+0
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,884 :: 		if(tmp < 0)
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CP         R16, R20
	CPC        R17, R21
	CPC        R18, R22
	CPC        R19, R23
	BRLT       L__print_F388
	JMP        L_print_F161
L__print_F388:
;st7735.c,886 :: 		tmp = -tmp;
	LDD        R0, Y+0
	LDD        R1, Y+1
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R0
	SBC        R17, R1
	LDD        R0, Y+2
	LDD        R1, Y+3
	LDI        R18, 0
	LDI        R19, 0
	SBC        R18, R0
	SBC        R19, R1
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,887 :: 		}
L_print_F161:
;st7735.c,889 :: 		if((value >= 10000) && (value < 100000))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 64
	LDI        R22, 28
	LDI        R23, 70
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F389
	LDI        R16, 1
L__print_F389:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F390
	JMP        L__print_F270
L__print_F390:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 80
	LDI        R22, 195
	LDI        R23, 71
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F391
	LDI        R16, 1
L__print_F391:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F392
	JMP        L__print_F269
L__print_F392:
L__print_F268:
;st7735.c,891 :: 		print_D((x_pos + 36), y_pos, font_size, colour, back_colour, tmp, points);
	MOVW       R16, R2
	SUBI       R16, 220
	SBCI       R17, 255
	MOVW       R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,892 :: 		}
	JMP        L_print_F165
;st7735.c,889 :: 		if((value >= 10000) && (value < 100000))
L__print_F270:
L__print_F269:
;st7735.c,893 :: 		else if((value >= 1000) && (value < 10000))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 122
	LDI        R23, 68
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F393
	LDI        R16, 1
L__print_F393:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F394
	JMP        L__print_F272
L__print_F394:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 64
	LDI        R22, 28
	LDI        R23, 70
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F395
	LDI        R16, 1
L__print_F395:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F396
	JMP        L__print_F271
L__print_F396:
L__print_F267:
;st7735.c,895 :: 		print_D((x_pos + 30), y_pos, font_size, colour, back_colour, tmp, points);
	MOVW       R16, R2
	SUBI       R16, 226
	SBCI       R17, 255
	MOVW       R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,896 :: 		}
	JMP        L_print_F169
;st7735.c,893 :: 		else if((value >= 1000) && (value < 10000))
L__print_F272:
L__print_F271:
;st7735.c,897 :: 		else if((value >= 100) && (value < 1000))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 200
	LDI        R23, 66
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F397
	LDI        R16, 1
L__print_F397:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F398
	JMP        L__print_F274
L__print_F398:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 122
	LDI        R23, 68
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F399
	LDI        R16, 1
L__print_F399:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F400
	JMP        L__print_F273
L__print_F400:
L__print_F266:
;st7735.c,899 :: 		print_D((x_pos + 24), y_pos, font_size, colour, back_colour, tmp, points);
	MOVW       R16, R2
	SUBI       R16, 232
	SBCI       R17, 255
	MOVW       R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,900 :: 		}
	JMP        L_print_F173
;st7735.c,897 :: 		else if((value >= 100) && (value < 1000))
L__print_F274:
L__print_F273:
;st7735.c,901 :: 		else if((value >= 10) && (value < 100))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 32
	LDI        R23, 65
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F401
	LDI        R16, 1
L__print_F401:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F402
	JMP        L__print_F276
L__print_F402:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 200
	LDI        R23, 66
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F403
	LDI        R16, 1
L__print_F403:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F404
	JMP        L__print_F275
L__print_F404:
L__print_F265:
;st7735.c,903 :: 		print_D((x_pos + 18), y_pos, font_size, colour, back_colour, tmp, points);
	MOVW       R16, R2
	SUBI       R16, 238
	SBCI       R17, 255
	MOVW       R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,904 :: 		}
	JMP        L_print_F177
;st7735.c,901 :: 		else if((value >= 10) && (value < 100))
L__print_F276:
L__print_F275:
;st7735.c,905 :: 		else if(value < 10)
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 32
	LDI        R23, 65
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F405
	LDI        R16, 1
L__print_F405:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F406
	JMP        L_print_F178
L__print_F406:
;st7735.c,907 :: 		print_D((x_pos + 12), y_pos, font_size, colour, back_colour, tmp, points);
	MOVW       R16, R2
	SUBI       R16, 244
	SBCI       R17, 255
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
;st7735.c,909 :: 		if((value) < 0)
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	LDD        R18, Y+16
	LDD        R19, Y+17
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F407
	LDI        R16, 1
L__print_F407:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	TST        R16
	BRNE       L__print_F408
	JMP        L_print_F179
L__print_F408:
;st7735.c,911 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, 0x2D);
	LDI        R27, 45
	MOV        R9, R27
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_char+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,912 :: 		}
	JMP        L_print_F180
L_print_F179:
;st7735.c,915 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
	LDI        R27, 32
	MOV        R9, R27
	LDD        R16, Y+12
	LDD        R17, Y+13
	PUSH       R17
	PUSH       R16
	CALL       _print_char+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,916 :: 		}
L_print_F180:
;st7735.c,917 :: 		}
L_print_F178:
L_print_F177:
L_print_F173:
L_print_F169:
L_print_F165:
;st7735.c,918 :: 		}
L_end_print_F:
	POP        R9
	POP        R3
	POP        R2
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_F

_Draw_BMP:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,921 :: 		void Draw_BMP(signed int x_pos1, signed int y_pos1, signed int x_pos2, signed int y_pos2, unsigned char *bitmap)
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
; bitmap start address is: 22 (R22)
	LDD        R22, Y+12
	LDD        R23, Y+13
	STD        Y+0, R6
	STD        Y+1, R7
	STD        Y+2, R2
	STD        Y+3, R3
	STD        Y+4, R8
	STD        Y+5, R9
	STD        Y+6, R4
	STD        Y+7, R5
;st7735.c,923 :: 		unsigned int size = 0x0000;
;st7735.c,924 :: 		unsigned int index = 0x0000;
;st7735.c,926 :: 		if(x_pos1 > x_pos2)
	LDD        R18, Y+2
	LDD        R19, Y+3
	LDD        R16, Y+0
	LDD        R17, Y+1
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_BMP410
	JMP        L_Draw_BMP181
L__Draw_BMP410:
;st7735.c,928 :: 		swap(&x_pos1, &x_pos2);
	MOVW       R18, R28
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,929 :: 		}
L_Draw_BMP181:
;st7735.c,931 :: 		if(y_pos1 > y_pos2)
	LDD        R18, Y+6
	LDD        R19, Y+7
	LDD        R16, Y+4
	LDD        R17, Y+5
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_BMP411
	JMP        L_Draw_BMP182
L__Draw_BMP411:
;st7735.c,933 :: 		swap(&y_pos1, &y_pos2);
	MOVW       R18, R28
	SUBI       R18, 252
	SBCI       R19, 255
	MOVW       R16, R28
	SUBI       R16, 250
	SBCI       R17, 255
	MOVW       R4, R18
	MOVW       R2, R16
	CALL       _swap+0
;st7735.c,934 :: 		}
L_Draw_BMP182:
;st7735.c,936 :: 		size = (y_pos2 - y_pos1);
	LDD        R0, Y+6
	LDD        R1, Y+7
	LDD        R20, Y+4
	LDD        R21, Y+5
	SUB        R20, R0
	SBC        R21, R1
;st7735.c,937 :: 		size *= (x_pos2 - x_pos1);
	LDD        R0, Y+2
	LDD        R1, Y+3
	LDD        R16, Y+0
	LDD        R17, Y+1
	SUB        R16, R0
	SBC        R17, R1
	CALL       _HWMul_16x16+0
;st7735.c,938 :: 		size <<= 1;
	LSL        R16
	ROL        R17
; size start address is: 18 (R18)
	MOVW       R18, R16
;st7735.c,940 :: 		TFT_set_display_window(x_pos1, y_pos1, (x_pos2 - 1), (y_pos2 - 1));
	LDD        R17, Y+4
	SUBI       R17, 1
	LDD        R16, Y+0
	SUBI       R16, 1
	MOV        R5, R17
	MOV        R4, R16
	LDD        R3, Y+6
	LDD        R2, Y+2
	CALL       _TFT_set_display_window+0
;st7735.c,942 :: 		for(index = 0; index < size; index++)
; index start address is: 20 (R20)
	LDI        R20, 0
	LDI        R21, 0
; size end address is: 18 (R18)
; bitmap end address is: 22 (R22)
; index end address is: 20 (R20)
L_Draw_BMP183:
; index start address is: 20 (R20)
; size start address is: 18 (R18)
; bitmap start address is: 22 (R22)
	CP         R20, R18
	CPC        R21, R19
	BRLO       L__Draw_BMP412
	JMP        L_Draw_BMP184
L__Draw_BMP412:
;st7735.c,944 :: 		TFT_write(*bitmap++, DAT);
	MOVW       R30, R22
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _TFT_Write+0
	POP        R2
	POP        R3
	MOVW       R16, R22
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R22, R16
;st7735.c,942 :: 		for(index = 0; index < size; index++)
	MOVW       R16, R20
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R20, R16
;st7735.c,945 :: 		}
; size end address is: 18 (R18)
; bitmap end address is: 22 (R22)
; index end address is: 20 (R20)
	JMP        L_Draw_BMP183
L_Draw_BMP184:
;st7735.c,946 :: 		}
L_end_Draw_BMP:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_BMP

_BMP180_init:

;bmp180.c,4 :: 		void BMP180_init()
;bmp180.c,6 :: 		TWIC_Init(100000);
	LDI        R27, 155
	STS        TWIC_MASTER_BAUD+0, R27
	CALL       _TWIC_Init+0
;bmp180.c,7 :: 		delay_ms(100);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_BMP180_init186:
	DEC        R16
	BRNE       L_BMP180_init186
	DEC        R17
	BRNE       L_BMP180_init186
	DEC        R18
	BRNE       L_BMP180_init186
;bmp180.c,9 :: 		BMP180_Calibration();
	CALL       _BMP180_Calibration+0
;bmp180.c,10 :: 		}
L_end_BMP180_init:
	RET
; end of _BMP180_init

_BMP180_read_byte:

;bmp180.c,13 :: 		signed char BMP180_read_byte(unsigned char address)
;bmp180.c,15 :: 		unsigned char temp = 0;
	PUSH       R2
;bmp180.c,17 :: 		TWIC_Start();
	CALL       _TWIC_Start+0
;bmp180.c,18 :: 		TWIC_Write(BMP180_Address);
	PUSH       R2
	LDI        R27, 238
	MOV        R2, R27
	CALL       _TWIC_Write+0
	POP        R2
;bmp180.c,19 :: 		TWIC_Write(address);
	CALL       _TWIC_Write+0
;bmp180.c,20 :: 		TWIC_Start();
	CALL       _TWIC_Start+0
;bmp180.c,21 :: 		TWIC_Write(BMP180_Address | 1);
	LDI        R27, 239
	MOV        R2, R27
	CALL       _TWIC_Write+0
;bmp180.c,22 :: 		temp = TWIC_Read(0);
	CLR        R2
	CALL       _TWIC_Read+0
; temp start address is: 17 (R17)
	MOV        R17, R16
;bmp180.c,23 :: 		TWIC_Stop();
	CALL       _TWIC_Stop+0
;bmp180.c,25 :: 		return temp;
	MOV        R16, R17
; temp end address is: 17 (R17)
;bmp180.c,26 :: 		}
;bmp180.c,25 :: 		return temp;
;bmp180.c,26 :: 		}
L_end_BMP180_read_byte:
	POP        R2
	RET
; end of _BMP180_read_byte

_BMP180_read_word:

;bmp180.c,29 :: 		signed int BMP180_read_word(unsigned char address)
;bmp180.c,31 :: 		unsigned char hb = 0;
	PUSH       R2
;bmp180.c,32 :: 		unsigned char lb = 0;
;bmp180.c,34 :: 		signed int temp = 0;
;bmp180.c,36 :: 		TWIC_Start();
	CALL       _TWIC_Start+0
;bmp180.c,37 :: 		TWIC_Write(BMP180_Address);
	PUSH       R2
	LDI        R27, 238
	MOV        R2, R27
	CALL       _TWIC_Write+0
	POP        R2
;bmp180.c,38 :: 		TWIC_Write(address);
	CALL       _TWIC_Write+0
;bmp180.c,39 :: 		TWIC_Start();
	CALL       _TWIC_Start+0
;bmp180.c,40 :: 		TWIC_Write(BMP180_Address | 1);
	LDI        R27, 239
	MOV        R2, R27
	CALL       _TWIC_Write+0
;bmp180.c,41 :: 		hb = TWIC_Read(1);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _TWIC_Read+0
; hb start address is: 18 (R18)
	MOV        R18, R16
;bmp180.c,42 :: 		lb = TWIC_Read(0);
	CLR        R2
	CALL       _TWIC_Read+0
; lb start address is: 19 (R19)
	MOV        R19, R16
;bmp180.c,43 :: 		TWIC_Stop();
	CALL       _TWIC_Stop+0
;bmp180.c,44 :: 		temp = ((hb << 8) | lb);
	MOV        R17, R18
	CLR        R16
; hb end address is: 18 (R18)
	OR         R16, R19
	ORI        R17, 0
; lb end address is: 19 (R19)
;bmp180.c,46 :: 		return temp;
;bmp180.c,47 :: 		}
;bmp180.c,46 :: 		return temp;
;bmp180.c,47 :: 		}
L_end_BMP180_read_word:
	POP        R2
	RET
; end of _BMP180_read_word

_BMP180_write:

;bmp180.c,50 :: 		void BMP180_write(unsigned char address, unsigned char value)
;bmp180.c,52 :: 		TWIC_Start();
	PUSH       R2
	CALL       _TWIC_Start+0
;bmp180.c,53 :: 		TWIC_Write(BMP180_Address);
	PUSH       R2
	LDI        R27, 238
	MOV        R2, R27
	CALL       _TWIC_Write+0
	POP        R2
;bmp180.c,54 :: 		TWIC_Write(address);
	CALL       _TWIC_Write+0
;bmp180.c,55 :: 		TWIC_Write(value);
	MOV        R2, R3
	CALL       _TWIC_Write+0
;bmp180.c,56 :: 		TWIC_Stop();
	CALL       _TWIC_Stop+0
;bmp180.c,57 :: 		}
L_end_BMP180_write:
	POP        R2
	RET
; end of _BMP180_write

_BMP180_Calibration:

;bmp180.c,60 :: 		void BMP180_Calibration()
;bmp180.c,62 :: 		_b1 = BMP180_read_word(B1_reg);
	PUSH       R2
	LDI        R27, 182
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        __b1+0, R16
	STS        __b1+1, R17
;bmp180.c,63 :: 		_b2 = BMP180_read_word(B2_reg);
	LDI        R27, 184
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        __b2+0, R16
	STS        __b2+1, R17
;bmp180.c,64 :: 		mb = BMP180_read_word(MB_reg);
	LDI        R27, 186
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _mb+0, R16
	STS        _mb+1, R17
;bmp180.c,65 :: 		mc = BMP180_read_word(MC_reg);
	LDI        R27, 188
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _mc+0, R16
	STS        _mc+1, R17
;bmp180.c,66 :: 		md = BMP180_read_word(MD_reg);
	LDI        R27, 190
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _md+0, R16
	STS        _md+1, R17
;bmp180.c,67 :: 		ac1 = BMP180_read_word(AC1_reg);
	LDI        R27, 170
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac1+0, R16
	STS        _ac1+1, R17
;bmp180.c,68 :: 		ac2 = BMP180_read_word(AC2_reg);
	LDI        R27, 172
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac2+0, R16
	STS        _ac2+1, R17
;bmp180.c,69 :: 		ac3 = BMP180_read_word(AC3_reg);
	LDI        R27, 174
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac3+0, R16
	STS        _ac3+1, R17
;bmp180.c,70 :: 		ac4 = BMP180_read_word(AC4_reg);
	LDI        R27, 176
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac4+0, R16
	STS        _ac4+1, R17
;bmp180.c,71 :: 		ac5 = BMP180_read_word(AC5_reg);
	LDI        R27, 178
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac5+0, R16
	STS        _ac5+1, R17
;bmp180.c,72 :: 		ac6 = BMP180_read_word(AC6_reg);
	LDI        R27, 180
	MOV        R2, R27
	CALL       _BMP180_read_word+0
	STS        _ac6+0, R16
	STS        _ac6+1, R17
;bmp180.c,73 :: 		}
L_end_BMP180_Calibration:
	POP        R2
	RET
; end of _BMP180_Calibration

_read_uncompensated_temperature:

;bmp180.c,76 :: 		unsigned int read_uncompensated_temperature()
;bmp180.c,78 :: 		unsigned int ut = 0;
	PUSH       R2
	PUSH       R3
;bmp180.c,80 :: 		BMP180_write(control_reg, temp_conv_cmd);
	LDI        R27, 46
	MOV        R3, R27
	LDI        R27, 244
	MOV        R2, R27
	CALL       _BMP180_write+0
;bmp180.c,81 :: 		delay_ms(5);
	LDI        R17, 208
	LDI        R16, 202
L_read_uncompensated_temperature188:
	DEC        R16
	BRNE       L_read_uncompensated_temperature188
	DEC        R17
	BRNE       L_read_uncompensated_temperature188
	NOP
;bmp180.c,82 :: 		ut = BMP180_read_word(MSB);
	LDI        R27, 246
	MOV        R2, R27
	CALL       _BMP180_read_word+0
;bmp180.c,84 :: 		return ut;
;bmp180.c,85 :: 		}
;bmp180.c,84 :: 		return ut;
;bmp180.c,85 :: 		}
L_end_read_uncompensated_temperature:
	POP        R3
	POP        R2
	RET
; end of _read_uncompensated_temperature

_read_uncompensated_pressure:

;bmp180.c,88 :: 		unsigned long read_uncompensated_pressure(unsigned char OSS)
;bmp180.c,90 :: 		unsigned char msb_value = 0;
	PUSH       R3
;bmp180.c,91 :: 		unsigned char lsb_value = 0;
;bmp180.c,92 :: 		unsigned char xlsb_value = 0;
;bmp180.c,94 :: 		unsigned long up = 0;
;bmp180.c,96 :: 		BMP180_write(control_reg, (0x34 + (OSS << 6)));
	LDI        R27, 6
	MOV        R16, R2
L__read_uncompensated_pressure420:
	LSL        R16
	DEC        R27
	BRNE       L__read_uncompensated_pressure420
L__read_uncompensated_pressure421:
	SUBI       R16, 204
	PUSH       R2
	MOV        R3, R16
	LDI        R27, 244
	MOV        R2, R27
	CALL       _BMP180_write+0
	POP        R2
;bmp180.c,97 :: 		switch(OSS)
	JMP        L_read_uncompensated_pressure190
;bmp180.c,99 :: 		case 1:
L_read_uncompensated_pressure192:
;bmp180.c,101 :: 		delay_ms(8);
	LDI        R18, 2
	LDI        R17, 77
	LDI        R16, 117
L_read_uncompensated_pressure193:
	DEC        R16
	BRNE       L_read_uncompensated_pressure193
	DEC        R17
	BRNE       L_read_uncompensated_pressure193
	DEC        R18
	BRNE       L_read_uncompensated_pressure193
	NOP
;bmp180.c,102 :: 		break;
	JMP        L_read_uncompensated_pressure191
;bmp180.c,104 :: 		case 2:
L_read_uncompensated_pressure195:
;bmp180.c,106 :: 		delay_ms(14);
	LDI        R18, 3
	LDI        R17, 70
	LDI        R16, 206
L_read_uncompensated_pressure196:
	DEC        R16
	BRNE       L_read_uncompensated_pressure196
	DEC        R17
	BRNE       L_read_uncompensated_pressure196
	DEC        R18
	BRNE       L_read_uncompensated_pressure196
	NOP
	NOP
;bmp180.c,107 :: 		break;
	JMP        L_read_uncompensated_pressure191
;bmp180.c,109 :: 		case 3:
L_read_uncompensated_pressure198:
;bmp180.c,111 :: 		delay_ms(26);
	LDI        R18, 5
	LDI        R17, 57
	LDI        R16, 128
L_read_uncompensated_pressure199:
	DEC        R16
	BRNE       L_read_uncompensated_pressure199
	DEC        R17
	BRNE       L_read_uncompensated_pressure199
	DEC        R18
	BRNE       L_read_uncompensated_pressure199
	NOP
	NOP
;bmp180.c,112 :: 		break;
	JMP        L_read_uncompensated_pressure191
;bmp180.c,114 :: 		default:
L_read_uncompensated_pressure201:
;bmp180.c,116 :: 		delay_ms(5);
	LDI        R17, 208
	LDI        R16, 202
L_read_uncompensated_pressure202:
	DEC        R16
	BRNE       L_read_uncompensated_pressure202
	DEC        R17
	BRNE       L_read_uncompensated_pressure202
	NOP
;bmp180.c,117 :: 		break;
	JMP        L_read_uncompensated_pressure191
;bmp180.c,119 :: 		}
L_read_uncompensated_pressure190:
	LDI        R27, 1
	CP         R2, R27
	BRNE       L__read_uncompensated_pressure422
	JMP        L_read_uncompensated_pressure192
L__read_uncompensated_pressure422:
	LDI        R27, 2
	CP         R2, R27
	BRNE       L__read_uncompensated_pressure423
	JMP        L_read_uncompensated_pressure195
L__read_uncompensated_pressure423:
	LDI        R27, 3
	CP         R2, R27
	BRNE       L__read_uncompensated_pressure424
	JMP        L_read_uncompensated_pressure198
L__read_uncompensated_pressure424:
	JMP        L_read_uncompensated_pressure201
L_read_uncompensated_pressure191:
;bmp180.c,121 :: 		msb_value = BMP180_read_byte(MSB);
	PUSH       R2
	LDI        R27, 246
	MOV        R2, R27
	CALL       _BMP180_read_byte+0
; msb_value start address is: 22 (R22)
	MOV        R22, R16
;bmp180.c,122 :: 		lsb_value = BMP180_read_byte(LSB);
	LDI        R27, 247
	MOV        R2, R27
	CALL       _BMP180_read_byte+0
; lsb_value start address is: 21 (R21)
	MOV        R21, R16
;bmp180.c,123 :: 		xlsb_value = BMP180_read_byte(XLSB);
	LDI        R27, 248
	MOV        R2, R27
	CALL       _BMP180_read_byte+0
	POP        R2
;bmp180.c,125 :: 		up = ((((unsigned long)msb_value << 16) | ((unsigned long)lsb_value << 8) | (unsigned long)xlsb_value) >> (8 - OSS));
	MOV        R17, R22
	LDI        R18, 0
	MOV        R19, R18
	MOV        R20, R18
; msb_value end address is: 22 (R22)
	MOV        R10, R18
	MOV        R9, R17
	CLR        R7
	CLR        R8
	MOV        R17, R21
	LDI        R18, 0
	MOV        R19, R18
	MOV        R20, R18
; lsb_value end address is: 21 (R21)
	MOV        R6, R19
	MOV        R5, R18
	MOV        R4, R17
	CLR        R3
	MOV        R20, R7
	MOV        R21, R8
	MOV        R22, R9
	MOV        R23, R10
	OR         R20, R3
	OR         R21, R4
	OR         R22, R5
	OR         R23, R6
	LDI        R17, 0
	MOV        R18, R17
	MOV        R19, R17
	OR         R20, R16
	OR         R21, R17
	OR         R22, R18
	OR         R23, R19
	LDI        R16, 8
	LDI        R17, 0
	SUB        R16, R2
	LDI        R27, 0
	SBC        R17, R27
	MOV        R27, R16
	MOVW       R16, R20
	MOVW       R18, R22
	TST        R27
	BREQ       L__read_uncompensated_pressure426
L__read_uncompensated_pressure425:
	LSR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__read_uncompensated_pressure425
L__read_uncompensated_pressure426:
;bmp180.c,127 :: 		return up;
;bmp180.c,128 :: 		}
;bmp180.c,127 :: 		return up;
;bmp180.c,128 :: 		}
L_end_read_uncompensated_pressure:
	POP        R3
	RET
; end of _read_uncompensated_pressure

_get_temperature:

;bmp180.c,131 :: 		float get_temperature(unsigned int UT)
;bmp180.c,133 :: 		float tmp = 0;
;bmp180.c,135 :: 		signed long x1 = 0;
;bmp180.c,136 :: 		signed long x2 = 0;
;bmp180.c,138 :: 		x1 = ((((signed long)UT - (signed long)ac6) * (signed long)ac5) >> 15);
	MOVW       R20, R2
	LDI        R22, 0
	MOV        R23, R22
	LDS        R16, _ac6+0
	LDS        R17, _ac6+1
	LDI        R18, 0
	MOV        R19, R18
	SUB        R20, R16
	SBC        R21, R17
	SBC        R22, R18
	SBC        R23, R19
	LDS        R16, _ac5+0
	LDS        R17, _ac5+1
	LDI        R18, 0
	MOV        R19, R18
	CALL       _HWMul_32x32+0
	LDI        R27, 15
	MOVW       R20, R16
	MOVW       R22, R18
L__get_temperature428:
	ASR        R23
	ROR        R22
	ROR        R21
	ROR        R20
	DEC        R27
	BRNE       L__get_temperature428
L__get_temperature429:
; x1 start address is: 8 (R8)
	MOVW       R8, R20
	MOVW       R10, R22
;bmp180.c,139 :: 		x2 = (((signed long)mc << 11) / (x1 + md));
	LDS        R16, _mc+0
	LDS        R17, _mc+1
	LDI        R18, 0
	SBRC       R17, 7
	LDI        R18, 255
	MOV        R19, R18
	LDI        R27, 11
	MOVW       R4, R16
	MOVW       R6, R18
L__get_temperature430:
	LSL        R4
	ROL        R5
	ROL        R6
	ROL        R7
	DEC        R27
	BRNE       L__get_temperature430
L__get_temperature431:
	LDS        R16, _md+0
	LDS        R17, _md+1
	ADD        R20, R16
	ADC        R21, R17
	LDI        R27, 0
	SBRC       R17, 7
	LDI        R27, 255
	ADC        R22, R27
	ADC        R23, R27
	PUSH       R11
	PUSH       R10
	PUSH       R9
	PUSH       R8
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R8
	POP        R9
	POP        R10
	POP        R11
;bmp180.c,140 :: 		_b5 = (x1 + x2);
	ADD        R16, R8
	ADC        R17, R9
	ADC        R18, R10
	ADC        R19, R11
; x1 end address is: 8 (R8)
	STS        __b5+0, R16
	STS        __b5+1, R17
	STS        __b5+2, R18
	STS        __b5+3, R19
;bmp180.c,141 :: 		tmp = ((_b5 + 8) >> 4);
	SUBI       R16, 248
	SBCI       R17, 255
	SBCI       R18, 255
	SBCI       R19, 255
	LDI        R27, 4
L__get_temperature432:
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_temperature432
L__get_temperature433:
	CALL       _float_slong2fp+0
;bmp180.c,142 :: 		tmp *= 0.1;
	LDI        R20, 205
	LDI        R21, 204
	LDI        R22, 204
	LDI        R23, 61
	CALL       _float_fpmul1+0
;bmp180.c,144 :: 		return tmp;
;bmp180.c,145 :: 		}
L_end_get_temperature:
	RET
; end of _get_temperature

_get_pressure:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;bmp180.c,148 :: 		signed long get_pressure(unsigned long UP, unsigned char OSS)
;bmp180.c,150 :: 		signed long p = 0;
;bmp180.c,151 :: 		signed long x1 = 0;
;bmp180.c,152 :: 		signed long x2 = 0;
;bmp180.c,153 :: 		signed long x3 = 0;
;bmp180.c,154 :: 		signed long _b3 = 0;
;bmp180.c,155 :: 		signed long _b6 = 0;
;bmp180.c,157 :: 		unsigned long _b4 = 0;
;bmp180.c,158 :: 		unsigned long _b7 = 0;
;bmp180.c,160 :: 		_b6 = (_b5 - 4000);
	LDS        R16, __b5+0
	LDS        R17, __b5+1
	LDS        R18, __b5+2
	LDS        R19, __b5+3
	SUBI       R16, 160
	SBCI       R17, 15
	SBCI       R18, 0
	SBCI       R19, 0
; _b6 start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
	MOV        R13, R18
	MOV        R14, R19
;bmp180.c,162 :: 		x1 = ((_b2 * (_b6 * _b6) >> 12) >> 11);
	MOVW       R20, R16
	MOVW       R22, R18
	CALL       _HWMul_32x32+0
	LDS        R20, __b2+0
	LDS        R21, __b2+1
	LDI        R22, 0
	SBRC       R21, 7
	LDI        R22, 255
	MOV        R23, R22
	CALL       _HWMul_32x32+0
	LDI        R27, 12
L__get_pressure435:
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure435
L__get_pressure436:
	LDI        R27, 11
L__get_pressure437:
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure437
L__get_pressure438:
	STD        Y+4, R16
	STD        Y+5, R17
	STD        Y+6, R18
	STD        Y+7, R19
;bmp180.c,163 :: 		x2 = ((ac2 * _b6) >> 11);
	LDS        R16, _ac2+0
	LDS        R17, _ac2+1
	LDI        R18, 0
	SBRC       R17, 7
	LDI        R18, 255
	MOV        R19, R18
	MOV        R20, R11
	MOV        R21, R12
	MOV        R22, R13
	MOV        R23, R14
	CALL       _HWMul_32x32+0
	LDI        R27, 11
	MOVW       R20, R16
	MOVW       R22, R18
L__get_pressure439:
	ASR        R23
	ROR        R22
	ROR        R21
	ROR        R20
	DEC        R27
	BRNE       L__get_pressure439
L__get_pressure440:
;bmp180.c,164 :: 		x3 = (x1 + x2);
	LDD        R16, Y+4
	LDD        R17, Y+5
	LDD        R18, Y+6
	LDD        R19, Y+7
	ADD        R20, R16
	ADC        R21, R17
	ADC        R22, R18
	ADC        R23, R19
;bmp180.c,165 :: 		_b3 = (((((((signed long)ac1) << 2) + x3) << OSS) + 2) >> 2);
	LDS        R16, _ac1+0
	LDS        R17, _ac1+1
	LDI        R18, 0
	SBRC       R17, 7
	LDI        R18, 255
	MOV        R19, R18
	LSL        R16
	ROL        R17
	ROL        R18
	ROL        R19
	LSL        R16
	ROL        R17
	ROL        R18
	ROL        R19
	ADD        R16, R20
	ADC        R17, R21
	ADC        R18, R22
	ADC        R19, R23
	MOV        R27, R6
	TST        R27
	BREQ       L__get_pressure442
L__get_pressure441:
	LSL        R16
	ROL        R17
	ROL        R18
	ROL        R19
	DEC        R27
	BRNE       L__get_pressure441
L__get_pressure442:
	SUBI       R16, 254
	SBCI       R17, 255
	SBCI       R18, 255
	SBCI       R19, 255
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
; _b3 start address is: 7 (R7)
	MOV        R7, R16
	MOV        R8, R17
	MOV        R9, R18
	MOV        R10, R19
;bmp180.c,166 :: 		x1 = ((ac3 * _b6) >> 13);
	LDS        R16, _ac3+0
	LDS        R17, _ac3+1
	LDI        R18, 0
	SBRC       R17, 7
	LDI        R18, 255
	MOV        R19, R18
	MOV        R20, R11
	MOV        R21, R12
	MOV        R22, R13
	MOV        R23, R14
	CALL       _HWMul_32x32+0
	LDI        R27, 13
L__get_pressure443:
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure443
L__get_pressure444:
	STD        Y+4, R16
	STD        Y+5, R17
	STD        Y+6, R18
	STD        Y+7, R19
;bmp180.c,167 :: 		x2 = ((_b1 * ((_b6 * _b6) >> 12)) >> 16);
	MOV        R16, R11
	MOV        R17, R12
	MOV        R18, R13
	MOV        R19, R14
	MOV        R20, R11
	MOV        R21, R12
	MOV        R22, R13
	MOV        R23, R14
	CALL       _HWMul_32x32+0
; _b6 end address is: 11 (R11)
	LDI        R27, 12
L__get_pressure445:
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure445
L__get_pressure446:
	LDS        R20, __b1+0
	LDS        R21, __b1+1
	LDI        R22, 0
	SBRC       R21, 7
	LDI        R22, 255
	MOV        R23, R22
	CALL       _HWMul_32x32+0
	MOV        R20, R18
	MOV        R21, R19
	LDI        R22, 0
	SBRC       R21, 7
	LDI        R22, 255
	MOV        R23, R22
;bmp180.c,168 :: 		x3 = (((x1 + x2) + 2) >> 2);
	LDD        R16, Y+4
	LDD        R17, Y+5
	LDD        R18, Y+6
	LDD        R19, Y+7
	ADD        R16, R20
	ADC        R17, R21
	ADC        R18, R22
	ADC        R19, R23
	SUBI       R16, 254
	SBCI       R17, 255
	SBCI       R18, 255
	SBCI       R19, 255
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	ASR        R19
	ROR        R18
	ROR        R17
	ROR        R16
;bmp180.c,169 :: 		_b4 = ((ac4 * (unsigned long)(x3 + 32768)) >> 15);
	SUBI       R16, 0
	SBCI       R17, 128
	SBCI       R18, 255
	SBCI       R19, 255
	LDS        R20, _ac4+0
	LDS        R21, _ac4+1
	LDI        R22, 0
	MOV        R23, R22
	CALL       _HWMul_32x32+0
	LDI        R27, 15
L__get_pressure447:
	LSR        R19
	ROR        R18
	ROR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure447
L__get_pressure448:
; _b4 start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
	MOV        R13, R18
	MOV        R14, R19
;bmp180.c,170 :: 		_b7 = ((unsigned long)(UP - _b3) * (50000 >> OSS));
	MOVW       R20, R2
	MOVW       R22, R4
	SUB        R20, R7
	SBC        R21, R8
	SBC        R22, R9
	SBC        R23, R10
; _b3 end address is: 7 (R7)
	MOV        R27, R6
	LDI        R16, 80
	LDI        R17, 195
	TST        R27
	BREQ       L__get_pressure450
L__get_pressure449:
	LSR        R17
	ROR        R16
	DEC        R27
	BRNE       L__get_pressure449
L__get_pressure450:
	LDI        R18, 0
	MOV        R19, R18
	CALL       _HWMul_32x32+0
; _b7 start address is: 20 (R20)
	MOVW       R20, R16
	MOVW       R22, R18
;bmp180.c,172 :: 		if(_b7 < 0x80000000)
	CPI        R19, 128
	BRNE       L__get_pressure451
	CPI        R18, 0
	BRNE       L__get_pressure451
	CPI        R17, 0
	BRNE       L__get_pressure451
	CPI        R16, 0
L__get_pressure451:
	BRLO       L__get_pressure452
	JMP        L_get_pressure204
L__get_pressure452:
;bmp180.c,174 :: 		p = ((_b7 << 1) / _b4);
	MOVW       R16, R20
	MOVW       R18, R22
	LSL        R16
	ROL        R17
	ROL        R18
	ROL        R19
; _b7 end address is: 20 (R20)
	MOV        R20, R11
	MOV        R21, R12
	MOV        R22, R13
	MOV        R23, R14
	CALL       _Div_32x32_U+0
	MOVW       R16, R22
	MOVW       R18, R24
; _b4 end address is: 11 (R11)
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;bmp180.c,175 :: 		}
	JMP        L_get_pressure205
L_get_pressure204:
;bmp180.c,178 :: 		p = ((_b7 / _b4) << 1);
; _b7 start address is: 20 (R20)
; _b4 start address is: 11 (R11)
	MOVW       R16, R20
	MOVW       R18, R22
	MOV        R20, R11
	MOV        R21, R12
	MOV        R22, R13
	MOV        R23, R14
	CALL       _Div_32x32_U+0
	MOVW       R16, R22
	MOVW       R18, R24
; _b4 end address is: 11 (R11)
; _b7 end address is: 20 (R20)
	LSL        R16
	ROL        R17
	ROL        R18
	ROL        R19
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;bmp180.c,179 :: 		}
L_get_pressure205:
;bmp180.c,181 :: 		x1 = ((p >> 8) * (p >> 8));
	LDD        R16, Y+0
	LDD        R17, Y+1
	LDD        R18, Y+2
	LDD        R19, Y+3
	MOV        R16, R17
	MOV        R17, R18
	MOV        R18, R19
	LDI        R19, 0
	SBRC       R18, 7
	LDI        R19, 255
	MOVW       R20, R16
	MOVW       R22, R18
	CALL       _HWMul_32x32+0
;bmp180.c,182 :: 		x1 = ((x1 * 3038) >> 16);
	LDI        R20, 222
	LDI        R21, 11
	LDI        R22, 0
	LDI        R23, 0
	CALL       _HWMul_32x32+0
	MOV        R16, R18
	MOV        R17, R19
	LDI        R18, 0
	SBRC       R17, 7
	LDI        R18, 255
	MOV        R19, R18
	STD        Y+4, R16
	STD        Y+5, R17
	STD        Y+6, R18
	STD        Y+7, R19
;bmp180.c,183 :: 		x2 = ((-7357 * p) >> 16);
	LDI        R16, 67
	LDI        R17, 227
	LDI        R18, 255
	LDI        R19, 255
	LDD        R20, Y+0
	LDD        R21, Y+1
	LDD        R22, Y+2
	LDD        R23, Y+3
	CALL       _HWMul_32x32+0
	MOV        R20, R18
	MOV        R21, R19
	LDI        R22, 0
	SBRC       R21, 7
	LDI        R22, 255
	MOV        R23, R22
;bmp180.c,184 :: 		p += ((x1 + x2 + 3791) >> 4);
	LDD        R16, Y+4
	LDD        R17, Y+5
	LDD        R18, Y+6
	LDD        R19, Y+7
	ADD        R16, R20
	ADC        R17, R21
	ADC        R18, R22
	ADC        R19, R23
	SUBI       R16, 49
	SBCI       R17, 241
	SBCI       R18, 255
	SBCI       R19, 255
	LDI        R27, 4
	MOVW       R20, R16
	MOVW       R22, R18
L__get_pressure453:
	ASR        R23
	ROR        R22
	ROR        R21
	ROR        R20
	DEC        R27
	BRNE       L__get_pressure453
L__get_pressure454:
	LDD        R16, Y+0
	LDD        R17, Y+1
	LDD        R18, Y+2
	LDD        R19, Y+3
	ADD        R16, R20
	ADC        R17, R21
	ADC        R18, R22
	ADC        R19, R23
;bmp180.c,186 :: 		return (signed long)p;
;bmp180.c,187 :: 		}
L_end_get_pressure:
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _get_pressure

_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 24
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;comms_demo.c,19 :: 		void main()
;comms_demo.c,21 :: 		unsigned char sample = 0;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
	LDI        R27, 0
	STD        Y+13, R27
;comms_demo.c,22 :: 		unsigned char tp = 0;
;comms_demo.c,23 :: 		unsigned char pp = 0;
;comms_demo.c,25 :: 		float T = 0.0;
;comms_demo.c,26 :: 		float P = 0.0;
;comms_demo.c,28 :: 		setup();
	CALL       _setup+0
;comms_demo.c,29 :: 		draw_background();
	CALL       _draw_background+0
;comms_demo.c,31 :: 		while(1)
L_main206:
;comms_demo.c,33 :: 		T = read_uncompensated_temperature();
	CALL       _read_uncompensated_temperature+0
	LDI        R18, 0
	MOV        R19, R18
	CALL       _float_ulong2fp+0
;comms_demo.c,34 :: 		T = get_temperature(T);
	CALL       _float_fpint+0
	MOVW       R2, R16
	CALL       _get_temperature+0
	STD        Y+16, R16
	STD        Y+17, R17
	STD        Y+18, R18
	STD        Y+19, R19
;comms_demo.c,35 :: 		P = read_uncompensated_pressure(OSS_value);
	LDI        R27, 3
	MOV        R2, R27
	CALL       _read_uncompensated_pressure+0
	CALL       _float_ulong2fp+0
;comms_demo.c,36 :: 		P = get_pressure(P, OSS_value);
	CALL       _float_fpint+0
	LDI        R27, 3
	MOV        R6, R27
	MOVW       R2, R16
	MOVW       R4, R18
	CALL       _get_pressure+0
	CALL       _float_slong2fp+0
;comms_demo.c,37 :: 		P *= 0.001;
	LDI        R20, 111
	LDI        R21, 18
	LDI        R22, 131
	LDI        R23, 58
	CALL       _float_fpmul1+0
	STD        Y+20, R16
	STD        Y+21, R17
	STD        Y+22, R18
	STD        Y+23, R19
;comms_demo.c,39 :: 		print_str(1, 120, 1, Red, Black, "T/ C:");
	LDI        R27, 84
	STD        Y+0, R27
	LDI        R27, 47
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 67
	STD        Y+3, R27
	LDI        R27, 58
	STD        Y+4, R27
	LDI        R27, 0
	STD        Y+5, R27
	MOVW       R16, R28
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 120
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 1
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,40 :: 		print_symbol(13, 120, 1, Red, Black, 0);
	CLR        R9
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 120
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 13
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_symbol+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,41 :: 		print_F(36, 120, 1, Red, Black, T, 2);
	LDI        R27, 2
	MOV        R9, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 120
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 36
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDD        R16, Y+16
	LDD        R17, Y+17
	LDD        R18, Y+18
	LDD        R19, Y+19
	PUSH       R19
	PUSH       R18
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_F+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,43 :: 		print_str(80, 120, 1, Green, Black, "P/kPa:");
	LDI        R27, 80
	STD        Y+6, R27
	LDI        R27, 47
	STD        Y+7, R27
	LDI        R27, 107
	STD        Y+8, R27
	LDI        R27, 80
	STD        Y+9, R27
	LDI        R27, 97
	STD        Y+10, R27
	LDI        R27, 58
	STD        Y+11, R27
	LDI        R27, 0
	STD        Y+12, R27
	MOVW       R16, R28
	SUBI       R16, 250
	SBCI       R17, 255
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 120
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 80
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,44 :: 		print_F(116, 120, 1, Green, Black, P, 2);
	LDI        R27, 2
	MOV        R9, R27
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 120
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 116
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDD        R16, Y+20
	LDD        R17, Y+21
	LDD        R18, Y+22
	LDD        R19, Y+23
	PUSH       R19
	PUSH       R18
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_F+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,46 :: 		tp = map(T, 0, 100, 10, 110);
	CLR        R6
	CLR        R7
	CLR        R8
	CLR        R9
	LDD        R2, Y+16
	LDD        R3, Y+17
	LDD        R4, Y+18
	LDD        R5, Y+19
	LDI        R27, 66
	PUSH       R27
	LDI        R27, 220
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	LDI        R27, 65
	PUSH       R27
	LDI        R27, 32
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	LDI        R27, 66
	PUSH       R27
	LDI        R27, 200
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _map+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 12
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	CALL       _float_fpint+0
;comms_demo.c,47 :: 		tp = constrain(tp, 10, 110);
	LDI        R17, 0
	MOV        R18, R17
	MOV        R19, R17
	CALL       _float_ulong2fp+0
	LDI        R27, 0
	MOV        R6, R27
	MOV        R7, R27
	LDI        R27, 32
	MOV        R8, R27
	LDI        R27, 65
	MOV        R9, R27
	MOVW       R2, R16
	MOVW       R4, R18
	LDI        R27, 66
	PUSH       R27
	LDI        R27, 220
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _constrain+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	CALL       _float_fpint+0
	STD        Y+14, R16
;comms_demo.c,48 :: 		pp = map(P, 50, 150, 10, 110);
	LDI        R27, 0
	MOV        R6, R27
	MOV        R7, R27
	LDI        R27, 72
	MOV        R8, R27
	LDI        R27, 66
	MOV        R9, R27
	LDD        R2, Y+20
	LDD        R3, Y+21
	LDD        R4, Y+22
	LDD        R5, Y+23
	LDI        R27, 66
	PUSH       R27
	LDI        R27, 220
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	LDI        R27, 65
	PUSH       R27
	LDI        R27, 32
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	LDI        R27, 67
	PUSH       R27
	LDI        R27, 22
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _map+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 12
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	CALL       _float_fpint+0
;comms_demo.c,49 :: 		pp = constrain(pp, 10, 110);
	LDI        R17, 0
	MOV        R18, R17
	MOV        R19, R17
	CALL       _float_ulong2fp+0
	LDI        R27, 0
	MOV        R6, R27
	MOV        R7, R27
	LDI        R27, 32
	MOV        R8, R27
	LDI        R27, 65
	MOV        R9, R27
	MOVW       R2, R16
	MOVW       R4, R18
	LDI        R27, 66
	PUSH       R27
	LDI        R27, 220
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _constrain+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	CALL       _float_fpint+0
	STD        Y+15, R16
;comms_demo.c,51 :: 		Draw_V_Line((58 + sample), 10, 110, Black);
	LDD        R16, Y+13
	LDI        R17, 0
	SUBI       R16, 198
	SBCI       R17, 255
	CLR        R8
	CLR        R9
	LDI        R27, 110
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 10
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	MOVW       R2, R16
	CALL       _Draw_V_Line+0
;comms_demo.c,53 :: 		Draw_Pixel((sample + 58), (120 - tp), Red);
	LDD        R0, Y+14
	LDI        R17, 120
	SUB        R17, R0
	LDD        R16, Y+13
	SUBI       R16, 198
	LDI        R27, 0
	MOV        R4, R27
	LDI        R27, 248
	MOV        R5, R27
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
;comms_demo.c,54 :: 		Draw_Pixel((sample + 58), (120 - pp), Green);
	LDD        R0, Y+15
	LDI        R17, 120
	SUB        R17, R0
	LDD        R16, Y+13
	SUBI       R16, 198
	LDI        R27, 224
	MOV        R4, R27
	LDI        R27, 7
	MOV        R5, R27
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
;comms_demo.c,55 :: 		sample++;
	LDD        R16, Y+13
	MOV        R17, R16
	SUBI       R17, 255
	STD        Y+13, R17
;comms_demo.c,57 :: 		if(sample > 99)
	LDI        R16, 99
	CP         R16, R17
	BRLO       L__main456
	JMP        L_main208
L__main456:
;comms_demo.c,59 :: 		sample = 0;
	LDI        R27, 0
	STD        Y+13, R27
;comms_demo.c,60 :: 		}
L_main208:
;comms_demo.c,62 :: 		PORTE_OUT.B2 ^= 1;
	LDS        R0, PORTE_OUT+0
	LDI        R27, 4
	EOR        R0, R27
	STS        PORTE_OUT+0, R0
;comms_demo.c,63 :: 		delay_ms(400);
	LDI        R18, 65
	LDI        R17, 240
	LDI        R16, 52
L_main209:
	DEC        R16
	BRNE       L_main209
	DEC        R17
	BRNE       L_main209
	DEC        R18
	BRNE       L_main209
;comms_demo.c,64 :: 		};
	JMP        L_main206
;comms_demo.c,65 :: 		}
L_end_main:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main

_setup:

;comms_demo.c,68 :: 		void setup()
;comms_demo.c,70 :: 		clock_setup();
	PUSH       R2
	PUSH       R3
	CALL       _clock_setup+0
;comms_demo.c,71 :: 		GPIO_setup();
	CALL       _GPIO_setup+0
;comms_demo.c,72 :: 		BMP180_init();
	CALL       _BMP180_init+0
;comms_demo.c,73 :: 		ST7735_init();
	CALL       _ST7735_init+0
;comms_demo.c,74 :: 		Set_Rotation(0x03);
	LDI        R27, 3
	MOV        R2, R27
	CALL       _Set_Rotation+0
;comms_demo.c,75 :: 		TFT_fill(Swap_Colour(Black));
	CLR        R2
	CLR        R3
	CALL       _Swap_Colour+0
	MOVW       R2, R16
	CALL       _TFT_fill+0
;comms_demo.c,76 :: 		}
L_end_setup:
	POP        R3
	POP        R2
	RET
; end of _setup

_clock_setup:

;comms_demo.c,79 :: 		void clock_setup()
;comms_demo.c,81 :: 		OSC_CTRL |= OSC_RC32KEN_bm;
	LDS        R27, OSC_CTRL+0
	SBR        R27, 4
	STS        OSC_CTRL+0, R27
;comms_demo.c,82 :: 		while(!(OSC_STATUS & OSC_RC32KRDY_bm));
L_clock_setup211:
	LDS        R16, OSC_STATUS+0
	SBRC       R16, 2
	JMP        L_clock_setup212
	JMP        L_clock_setup211
L_clock_setup212:
;comms_demo.c,83 :: 		OSC_CTRL |= OSC_RC32MEN_bm;
	LDS        R16, OSC_CTRL+0
	ORI        R16, 2
	STS        OSC_CTRL+0, R16
;comms_demo.c,84 :: 		CPU_CCP = CCP_IOREG_gc;
	LDI        R27, 216
	OUT        CPU_CCP+0, R27
;comms_demo.c,86 :: 		| CLK_PSBCDIV0_bm))) | CLK_PSADIV_1_gc | CLK_PSBCDIV_2_2_gc);
	LDS        R16, CLK_PSCTRL+0
	ANDI       R16, 128
	ORI        R16, 3
	STS        CLK_PSCTRL+0, R16
;comms_demo.c,87 :: 		OSC_DFLLCTRL = ((OSC_DFLLCTRL & (~(OSC_RC32MCREF_gm | OSC_RC2MCREF_bm))) |
	LDS        R16, OSC_DFLLCTRL+0
	ANDI       R16, 248
;comms_demo.c,88 :: 		OSC_RC32MCREF_RC32K_gc);
	STS        OSC_DFLLCTRL+0, R16
;comms_demo.c,89 :: 		DFLLRC32M_CTRL |= DFLL_ENABLE_bm;
	LDS        R16, DFLLRC32M_CTRL+0
	ORI        R16, 1
	STS        DFLLRC32M_CTRL+0, R16
;comms_demo.c,90 :: 		while(!(OSC_STATUS & OSC_RC32MRDY_bm));
L_clock_setup213:
	LDS        R16, OSC_STATUS+0
	SBRC       R16, 1
	JMP        L_clock_setup214
	JMP        L_clock_setup213
L_clock_setup214:
;comms_demo.c,91 :: 		CPU_CCP = CCP_IOREG_gc;
	LDI        R27, 216
	OUT        CPU_CCP+0, R27
;comms_demo.c,92 :: 		CLK_CTRL = ((CLK_CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC32M_gc);
	LDS        R16, CLK_CTRL+0
	ANDI       R16, 248
	ORI        R16, 1
	STS        CLK_CTRL+0, R16
;comms_demo.c,93 :: 		OSC_CTRL &= (~(OSC_RC2MEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm));
	LDS        R16, OSC_CTRL+0
	ANDI       R16, 230
	STS        OSC_CTRL+0, R16
;comms_demo.c,94 :: 		PORTCFG_CLKEVOUT = 0x00;
	LDI        R27, 0
	STS        PORTCFG_CLKEVOUT+0, R27
;comms_demo.c,95 :: 		}
L_end_clock_setup:
	RET
; end of _clock_setup

_GPIO_setup:

;comms_demo.c,98 :: 		void GPIO_setup()
;comms_demo.c,100 :: 		PORTA_OUT = 0x00;
	LDI        R27, 0
	STS        PORTA_OUT+0, R27
;comms_demo.c,101 :: 		PORTA_DIR = 0x00;
	LDI        R27, 0
	STS        PORTA_DIR+0, R27
;comms_demo.c,102 :: 		PORTCFG_MPCMASK = 0xFF;
	LDI        R27, 255
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,103 :: 		PORTA_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 0
	STS        PORTA_PIN0CTRL+0, R27
;comms_demo.c,104 :: 		PORTA_INTCTRL = ((PORTA_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTA_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,105 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTA_INTCTRL+0, R16
;comms_demo.c,106 :: 		PORTA_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTA_INT0MASK+0, R27
;comms_demo.c,107 :: 		PORTA_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTA_INT1MASK+0, R27
;comms_demo.c,109 :: 		PORTB_OUT = 0x00;
	LDI        R27, 0
	STS        PORTB_OUT+0, R27
;comms_demo.c,110 :: 		PORTB_DIR = 0x00;
	LDI        R27, 0
	STS        PORTB_DIR+0, R27
;comms_demo.c,111 :: 		PORTCFG_MPCMASK = 0x0F;
	LDI        R27, 15
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,112 :: 		PORTB_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 0
	STS        PORTB_PIN0CTRL+0, R27
;comms_demo.c,113 :: 		PORTB_INTCTRL = ((PORTB_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTB_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,114 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTB_INTCTRL+0, R16
;comms_demo.c,115 :: 		PORTB_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTB_INT0MASK+0, R27
;comms_demo.c,116 :: 		PORTB_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTB_INT1MASK+0, R27
;comms_demo.c,119 :: 		PORTC_OUT = 0x00;
	LDI        R27, 0
	STS        PORTC_OUT+0, R27
;comms_demo.c,120 :: 		PORTC_DIR = 0xBE;
	LDI        R27, 190
	STS        PORTC_DIR+0, R27
;comms_demo.c,121 :: 		PORTCFG_MPCMASK = 0xFF;
	LDI        R27, 255
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,122 :: 		PORTC_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 0
	STS        PORTC_PIN0CTRL+0, R27
;comms_demo.c,123 :: 		PORTC_REMAP = ((0 << PORT_SPI_bp) | (0 << PORT_USART0_bp) | (0 << PORT_TC0D_bp) | (0 << PORT_TC0C_bp) | (0 << PORT_TC0B_bp) | (0 << PORT_TC0A_bp));
	LDI        R27, 0
	STS        PORTC_REMAP+0, R27
;comms_demo.c,124 :: 		PORTC_INTCTRL = ((PORTC_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTC_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,125 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTC_INTCTRL+0, R16
;comms_demo.c,126 :: 		PORTC_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTC_INT0MASK+0, R27
;comms_demo.c,127 :: 		PORTC_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTC_INT1MASK+0, R27
;comms_demo.c,129 :: 		PORTD_OUT = 0x00;
	LDI        R27, 0
	STS        PORTD_OUT+0, R27
;comms_demo.c,130 :: 		PORTD_DIR = 0x00;
	LDI        R27, 0
	STS        PORTD_DIR+0, R27
;comms_demo.c,131 :: 		PORTCFG_MPCMASK = 0xFF;
	LDI        R27, 255
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,132 :: 		PORTD_PIN0CTRL = (PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 24
	STS        PORTD_PIN0CTRL+0, R27
;comms_demo.c,133 :: 		PORTD_INTCTRL = ((PORTD_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTD_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,134 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTD_INTCTRL+0, R16
;comms_demo.c,135 :: 		PORTD_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTD_INT0MASK+0, R27
;comms_demo.c,136 :: 		PORTD_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTD_INT1MASK+0, R27
;comms_demo.c,138 :: 		PORTE_OUT = 0x0C;
	LDI        R27, 12
	STS        PORTE_OUT+0, R27
;comms_demo.c,139 :: 		PORTE_DIR = 0x0C;
	LDI        R27, 12
	STS        PORTE_DIR+0, R27
;comms_demo.c,140 :: 		PORTCFG_MPCMASK = 0x0F;
	LDI        R27, 15
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,141 :: 		PORTE_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 0
	STS        PORTE_PIN0CTRL+0, R27
;comms_demo.c,142 :: 		PORTE_INTCTRL = ((PORTE_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTE_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,143 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTE_INTCTRL+0, R16
;comms_demo.c,144 :: 		PORTE_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTE_INT0MASK+0, R27
;comms_demo.c,145 :: 		PORTE_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTE_INT1MASK+0, R27
;comms_demo.c,147 :: 		PORTR_OUT = 0x00;
	LDI        R27, 0
	STS        PORTR_OUT+0, R27
;comms_demo.c,148 :: 		PORTR_DIR = 0x00;
	LDI        R27, 0
	STS        PORTR_DIR+0, R27
;comms_demo.c,149 :: 		PORTCFG_MPCMASK = 0x03;
	LDI        R27, 3
	STS        PORTCFG_MPCMASK+0, R27
;comms_demo.c,150 :: 		PORTR_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
	LDI        R27, 0
	STS        PORTR_PIN0CTRL+0, R27
;comms_demo.c,151 :: 		PORTR_INTCTRL = ((PORTR_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	LDS        R16, PORTR_INTCTRL+0
	ANDI       R16, 240
;comms_demo.c,152 :: 		PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
	STS        PORTR_INTCTRL+0, R16
;comms_demo.c,153 :: 		PORTR_INT0MASK = 0x00;
	LDI        R27, 0
	STS        PORTR_INT0MASK+0, R27
;comms_demo.c,154 :: 		PORTR_INT1MASK = 0x00;
	LDI        R27, 0
	STS        PORTR_INT1MASK+0, R27
;comms_demo.c,156 :: 		PORTCFG_VPCTRLA = (PORTCFG_VP13MAP_PORTB_gc | PORTCFG_VP02MAP_PORTA_gc);
	LDI        R27, 16
	STS        PORTCFG_VPCTRLA+0, R27
;comms_demo.c,157 :: 		PORTCFG_VPCTRLB = (PORTCFG_VP13MAP_PORTD_gc | PORTCFG_VP02MAP_PORTC_gc);
	LDI        R27, 50
	STS        PORTCFG_VPCTRLB+0, R27
;comms_demo.c,158 :: 		}
L_end_GPIO_setup:
	RET
; end of _GPIO_setup

_draw_background:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 40
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;comms_demo.c,161 :: 		void draw_background()
;comms_demo.c,163 :: 		unsigned char points = 0x00;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
;comms_demo.c,165 :: 		print_str(60, 1, 1, Light_Blue, Black, "BMP180 + XMega");
	LDI        R30, #lo_addr(?ICS?lstr3_comms_demo+0)
	LDI        R31, hi_addr(?ICS?lstr3_comms_demo+0)
	MOVW       R26, R28
	LDI        R24, 15
	LDI        R25, 0
	CALL       ___CC2DW+0
	MOVW       R16, R28
	LDI        R27, 31
	MOV        R7, R27
	LDI        R27, 5
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 60
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,167 :: 		Draw_Rectangle(57, 9, 158, 111, NO, SQUARE, White, Black);
	LDI        R27, 111
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 158
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 9
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 57
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	LDI        R27, 255
	PUSH       R27
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,169 :: 		Draw_V_Line(50, 110, 10, Red);
	LDI        R27, 0
	MOV        R8, R27
	LDI        R27, 248
	MOV        R9, R27
	LDI        R27, 10
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 110
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 50
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_V_Line+0
;comms_demo.c,170 :: 		Draw_V_Line(25, 110, 10, Green);
	LDI        R27, 224
	MOV        R8, R27
	LDI        R27, 7
	MOV        R9, R27
	LDI        R27, 10
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 110
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 25
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_V_Line+0
;comms_demo.c,172 :: 		for(points = 0; points <= 100; points += 10)
; points start address is: 18 (R18)
	LDI        R18, 0
; points end address is: 18 (R18)
L_draw_background215:
; points start address is: 18 (R18)
	LDI        R16, 100
	CP         R16, R18
	BRSH       L__draw_background464
	JMP        L_draw_background216
L__draw_background464:
;comms_demo.c,174 :: 		Draw_H_Line(23, 27, (10 + points), Green);
	MOV        R16, R18
	LDI        R17, 0
	SUBI       R16, 246
	SBCI       R17, 255
	PUSH       R18
	LDI        R27, 224
	MOV        R8, R27
	LDI        R27, 7
	MOV        R9, R27
	MOVW       R6, R16
	LDI        R27, 27
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 23
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_H_Line+0
	POP        R18
;comms_demo.c,175 :: 		Draw_H_Line(48, 52, (10 + points), Red);
	MOV        R16, R18
	LDI        R17, 0
	SUBI       R16, 246
	SBCI       R17, 255
	PUSH       R18
	LDI        R27, 0
	MOV        R8, R27
	LDI        R27, 248
	MOV        R9, R27
	MOVW       R6, R16
	LDI        R27, 52
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 48
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_H_Line+0
	POP        R18
;comms_demo.c,172 :: 		for(points = 0; points <= 100; points += 10)
	MOV        R16, R18
	SUBI       R16, 246
	MOV        R18, R16
;comms_demo.c,176 :: 		}
; points end address is: 18 (R18)
	JMP        L_draw_background215
L_draw_background216:
;comms_demo.c,178 :: 		for(points = 0; points <= 95; points += 10)
; points start address is: 18 (R18)
	LDI        R18, 0
; points end address is: 18 (R18)
L_draw_background218:
; points start address is: 18 (R18)
	LDI        R16, 95
	CP         R16, R18
	BRSH       L__draw_background465
	JMP        L_draw_background219
L__draw_background465:
;comms_demo.c,180 :: 		Draw_H_Line(24, 26, (15 + points), Green);
	MOV        R16, R18
	LDI        R17, 0
	SUBI       R16, 241
	SBCI       R17, 255
	PUSH       R18
	LDI        R27, 224
	MOV        R8, R27
	LDI        R27, 7
	MOV        R9, R27
	MOVW       R6, R16
	LDI        R27, 26
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 24
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_H_Line+0
	POP        R18
;comms_demo.c,181 :: 		Draw_H_Line(49, 51, (15 + points), Red);
	MOV        R16, R18
	LDI        R17, 0
	SUBI       R16, 241
	SBCI       R17, 255
	PUSH       R18
	LDI        R27, 0
	MOV        R8, R27
	LDI        R27, 248
	MOV        R9, R27
	MOVW       R6, R16
	LDI        R27, 51
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 49
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_H_Line+0
	POP        R18
;comms_demo.c,178 :: 		for(points = 0; points <= 95; points += 10)
	MOV        R16, R18
	SUBI       R16, 246
	MOV        R18, R16
;comms_demo.c,182 :: 		}
; points end address is: 18 (R18)
	JMP        L_draw_background218
L_draw_background219:
;comms_demo.c,184 :: 		print_str(0, 1, 1, Green, Black, "kPa");
	LDI        R27, 107
	STD        Y+15, R27
	LDI        R27, 80
	STD        Y+16, R27
	LDI        R27, 97
	STD        Y+17, R27
	LDI        R27, 0
	STD        Y+18, R27
	MOVW       R16, R28
	SUBI       R16, 241
	SBCI       R17, 255
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,185 :: 		print_symbol(40, 1, 1, Red, Black, 0);
	CLR        R9
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 40
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_symbol+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,186 :: 		print_str(46, 1, 1, Red, Black, "C");
	LDI        R27, 67
	STD        Y+19, R27
	LDI        R27, 0
	STD        Y+20, R27
	MOVW       R16, R28
	SUBI       R16, 237
	SBCI       R17, 255
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 46
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,188 :: 		print_str(0, 10, 1, Green, Black, "150");
	LDI        R27, 49
	STD        Y+21, R27
	LDI        R27, 53
	STD        Y+22, R27
	LDI        R27, 48
	STD        Y+23, R27
	LDI        R27, 0
	STD        Y+24, R27
	MOVW       R16, R28
	SUBI       R16, 235
	SBCI       R17, 255
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 10
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,189 :: 		print_str(31, 20, 1, Red, Black, "90");
	LDI        R27, 57
	STD        Y+25, R27
	LDI        R27, 48
	STD        Y+26, R27
	LDI        R27, 0
	STD        Y+27, R27
	MOVW       R16, R28
	SUBI       R16, 231
	SBCI       R17, 255
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 20
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 31
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,191 :: 		print_str(0, 60, 1, Green, Black, "100");
	LDI        R27, 49
	STD        Y+28, R27
	LDI        R27, 48
	STD        Y+29, R27
	LDI        R27, 48
	STD        Y+30, R27
	LDI        R27, 0
	STD        Y+31, R27
	MOVW       R16, R28
	SUBI       R16, 228
	SBCI       R17, 255
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 60
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,192 :: 		print_str(31, 60, 1, Red, Black, "50");
	LDI        R27, 53
	STD        Y+32, R27
	LDI        R27, 48
	STD        Y+33, R27
	LDI        R27, 0
	STD        Y+34, R27
	MOVW       R16, R28
	SUBI       R16, 224
	SBCI       R17, 255
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 60
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 31
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,194 :: 		print_str(0, 106, 1, Green, Black, "50");
	LDI        R27, 53
	STD        Y+35, R27
	LDI        R27, 48
	STD        Y+36, R27
	LDI        R27, 0
	STD        Y+37, R27
	MOVW       R16, R28
	SUBI       R16, 221
	SBCI       R17, 255
	LDI        R27, 224
	MOV        R7, R27
	LDI        R27, 7
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 106
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,195 :: 		print_str(31, 106, 1, Red, Black, "0");
	LDI        R27, 48
	STD        Y+38, R27
	LDI        R27, 0
	STD        Y+39, R27
	MOVW       R16, R28
	SUBI       R16, 218
	SBCI       R17, 255
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 248
	MOV        R8, R27
	LDI        R27, 1
	MOV        R6, R27
	LDI        R27, 106
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 31
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	LDI        R27, 0
	PUSH       R27
	PUSH       R27
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;comms_demo.c,196 :: 		}
L_end_draw_background:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 39
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _draw_background

_map:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 16
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;comms_demo.c,199 :: 		float map(float value, float x_min, float x_max, float y_min, float y_max)
	LDD        R16, Y+20
	LDD        R17, Y+21
	LDD        R18, Y+22
	LDD        R19, Y+23
	STD        Y+20, R16
	STD        Y+21, R17
	STD        Y+22, R18
	STD        Y+23, R19
	LDD        R16, Y+24
	LDD        R17, Y+25
	LDD        R18, Y+26
	LDD        R19, Y+27
	STD        Y+24, R16
	STD        Y+25, R17
	STD        Y+26, R18
	STD        Y+27, R19
	LDD        R16, Y+28
	LDD        R17, Y+29
	LDD        R18, Y+30
	LDD        R19, Y+31
	STD        Y+28, R16
	STD        Y+29, R17
	STD        Y+30, R18
	STD        Y+31, R19
;comms_demo.c,201 :: 		return (y_min + (((y_max - y_min) / ((x_max - x_min)) * (value - x_min))));
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R20, Y+24
	LDD        R21, Y+25
	LDD        R22, Y+26
	LDD        R23, Y+27
	LDD        R16, Y+28
	LDD        R17, Y+29
	LDD        R18, Y+30
	LDD        R19, Y+31
	CALL       _float_fpsub1+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	STD        Y+12, R16
	STD        Y+13, R17
	STD        Y+14, R18
	STD        Y+15, R19
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R20, R6
	MOVW       R22, R8
	LDD        R16, Y+20
	LDD        R17, Y+21
	LDD        R18, Y+22
	LDD        R19, Y+23
	CALL       _float_fpsub1+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDD        R20, Y+0
	LDD        R21, Y+1
	LDD        R22, Y+2
	LDD        R23, Y+3
	CALL       _float_fpdiv1+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	STD        Y+12, R16
	STD        Y+13, R17
	STD        Y+14, R18
	STD        Y+15, R19
	MOVW       R20, R6
	MOVW       R22, R8
	MOVW       R16, R2
	MOVW       R18, R4
	CALL       _float_fpsub1+0
	LDD        R20, Y+12
	LDD        R21, Y+13
	LDD        R22, Y+14
	LDD        R23, Y+15
	CALL       _float_fpmul1+0
	LDD        R20, Y+24
	LDD        R21, Y+25
	LDD        R22, Y+26
	LDD        R23, Y+27
	CALL       _float_fpadd1+0
;comms_demo.c,202 :: 		}
L_end_map:
	ADIW       R28, 15
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _map

_constrain:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;comms_demo.c,205 :: 		float constrain(float value, float value_min, float value_max)
; value_max start address is: 20 (R20)
	LDD        R20, Y+0
	LDD        R21, Y+1
	LDD        R22, Y+2
	LDD        R23, Y+3
;comms_demo.c,207 :: 		if(value >= value_max)
	PUSH       R23
	PUSH       R22
	PUSH       R21
	PUSH       R20
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R16, R2
	MOVW       R18, R4
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__constrain468
	LDI        R16, 1
L__constrain468:
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R20
	POP        R21
	POP        R22
	POP        R23
	TST        R16
	BRNE       L__constrain469
	JMP        L_constrain221
L__constrain469:
;comms_demo.c,209 :: 		return value_max;
	MOVW       R16, R20
	MOVW       R18, R22
; value_max end address is: 20 (R20)
	JMP        L_end_constrain
;comms_demo.c,210 :: 		}
L_constrain221:
;comms_demo.c,211 :: 		else if(value <= value_min)
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R20, R6
	MOVW       R22, R8
	MOVW       R16, R2
	MOVW       R18, R4
	CALL       _float_op_lequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__constrain470
	LDI        R16, 1
L__constrain470:
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__constrain471
	JMP        L_constrain223
L__constrain471:
;comms_demo.c,213 :: 		return value_min;
	MOVW       R16, R6
	MOVW       R18, R8
	JMP        L_end_constrain
;comms_demo.c,214 :: 		}
L_constrain223:
;comms_demo.c,217 :: 		return value;
	MOVW       R16, R2
	MOVW       R18, R4
;comms_demo.c,219 :: 		}
L_end_constrain:
	POP        R29
	POP        R28
	RET
; end of _constrain

_print_symbol:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;comms_demo.c,222 :: 		void print_symbol(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
; back_colour start address is: 17 (R17)
	LDD        R17, Y+0
	LDD        R18, Y+1
;comms_demo.c,224 :: 		unsigned char i = 0x00;
;comms_demo.c,225 :: 		unsigned char j = 0x00;
;comms_demo.c,226 :: 		unsigned char value = 0x00;
;comms_demo.c,228 :: 		if(font_size <= 0)
	LDI        R16, 0
	CP         R16, R6
	BRSH       L__print_symbol473
	JMP        L_print_symbol225
L__print_symbol473:
;comms_demo.c,230 :: 		font_size = 1;
	LDI        R27, 1
	MOV        R6, R27
;comms_demo.c,231 :: 		}
L_print_symbol225:
;comms_demo.c,233 :: 		if(x_pos < font_size)
	CP         R2, R6
	LDI        R27, 0
	CPC        R3, R27
	BRLO       L__print_symbol474
	JMP        L_print_symbol226
L__print_symbol474:
;comms_demo.c,235 :: 		x_pos = font_size;
	MOV        R2, R6
	LDI        R27, 0
	MOV        R3, R27
;comms_demo.c,236 :: 		}
L_print_symbol226:
;comms_demo.c,238 :: 		for(i = 0x00; i < 0x05; i++)
; i start address is: 22 (R22)
	LDI        R22, 0
; back_colour end address is: 17 (R17)
; i end address is: 22 (R22)
	MOV        R20, R17
	MOV        R21, R18
L_print_symbol227:
; i start address is: 22 (R22)
; back_colour start address is: 20 (R20)
	CPI        R22, 5
	BRLO       L__print_symbol475
	JMP        L_print_symbol228
L__print_symbol475:
;comms_demo.c,240 :: 		for(j = 0x00; j < 0x08; j++)
; j start address is: 23 (R23)
	LDI        R23, 0
; back_colour end address is: 20 (R20)
; j end address is: 23 (R23)
; i end address is: 22 (R22)
L_print_symbol230:
; j start address is: 23 (R23)
; back_colour start address is: 20 (R20)
; i start address is: 22 (R22)
	CPI        R23, 8
	BRLO       L__print_symbol476
	JMP        L_print_symbol231
L__print_symbol476:
;comms_demo.c,243 :: 		value = ((symbol[((unsigned char)ch)][i]));
	PUSH       R21
	PUSH       R20
	LDI        R16, 5
	LDI        R17, 0
	MOV        R20, R9
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	POP        R21
	LDI        R18, #lo_addr(_symbol+0)
	LDI        R19, hi_addr(_symbol+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R22
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
;comms_demo.c,245 :: 		if(((value >> j) & 0x01) != 0x00)
	MOV        R27, R23
	TST        R27
	BREQ       L__print_symbol478
L__print_symbol477:
	LSR        R16
	DEC        R27
	BRNE       L__print_symbol477
L__print_symbol478:
	ANDI       R16, 1
	CPI        R16, 0
	BRNE       L__print_symbol479
	JMP        L_print_symbol233
L__print_symbol479:
;comms_demo.c,247 :: 		Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOV        R4, R7
	MOV        R5, R8
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;comms_demo.c,248 :: 		}
	JMP        L_print_symbol234
L_print_symbol233:
;comms_demo.c,251 :: 		Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;comms_demo.c,252 :: 		}
L_print_symbol234:
;comms_demo.c,254 :: 		y_pos += font_size;
	MOV        R16, R6
	LDI        R17, 0
	ADD        R16, R4
	ADC        R17, R5
	MOVW       R4, R16
;comms_demo.c,240 :: 		for(j = 0x00; j < 0x08; j++)
	MOV        R16, R23
	SUBI       R16, 255
	MOV        R23, R16
;comms_demo.c,255 :: 		}
; j end address is: 23 (R23)
	JMP        L_print_symbol230
L_print_symbol231:
;comms_demo.c,257 :: 		y_pos -= (font_size << 0x03);
	MOV        R16, R6
	LDI        R17, 0
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	MOVW       R0, R16
	MOVW       R16, R4
	SUB        R16, R0
	SBC        R17, R1
	MOVW       R4, R16
;comms_demo.c,258 :: 		x_pos += font_size;
	MOV        R16, R6
	LDI        R17, 0
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;comms_demo.c,238 :: 		for(i = 0x00; i < 0x05; i++)
	MOV        R16, R22
	SUBI       R16, 255
	MOV        R22, R16
;comms_demo.c,259 :: 		}
; back_colour end address is: 20 (R20)
; i end address is: 22 (R22)
	JMP        L_print_symbol227
L_print_symbol228:
;comms_demo.c,260 :: 		}
L_end_print_symbol:
	POP        R29
	POP        R28
	RET
; end of _print_symbol
