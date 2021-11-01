; Game Boy Hardware definitions
; Based on existing hardware.inc
; Slightly more compacted and formatted how I like

if __RGBDS_MAJOR__ == 0 && __RGBDS_MINOR__ < 5
    fail "This version of 'hardware.inc' requires RGBDS version 0.5.0 or later."
endc

; If all of these are already defined, don't do it again.

    if !def(HARDWARE_INC)
def HARDWARE_INC equ 1

macro REV_CHECK_HARDWARE_INC
; NOTE: revision number changes must be added
; to second parameter in following line.
    if \1 > 4.2 ; Put revision number here
        warn    "Version \1 or later of 'hardware.inc' is required."
    endc
endm

def _VRAM           equ $8000 ; $8000-$9FFF
def _VARM8000       equ _VRAM
def _VRAM8800       equ _VRAM+$800
def _VRAM9000       equ _VRAM+$1000
def _SCRN0          equ $9800 ; $9800-$9BFF
def _SCRN1          equ $9C00 ; $9C00-$9FFF
def _SRAM           equ $A000 ; $A000-$BFFF
def _RAM            equ $C000 ; $C000-$CFFF / $C000-$DFFF
def _RAMBANK        equ $D000 ; $D000-$DFFF
def _OAMRAM         equ $FE00 ; $FE00-$FE9F
def _IO             equ $FF00 ; $FF00-$FF7F, $FFFF
def _AUD3WAVERAM    equ $FF30 ; $FF30-$FF3F
def _HRAM           equ $FF80 ; $FF80-$FFFE

; *** MBC5 Equates ***
def rRAMG           equ $0000 ; $0000-$1FFF
def rR0MB0          equ $2000 ; $2000-$2FFF
def rR0MB1          equ $3000 ; $3000-$3FFF - If more than 256 ROM banks are present
def rRAMB           equ $4000 ; $4000-$5FFF - Bit 3 enables rumble (if present)

; ******************************************************************************
; Custom registers
; ******************************************************************************

; P1 ($FF00)
; Register for reading joypad info (R/W)
def rPORT               equ $FF00
def PORT_OUT1           equ %00100000 ; P15 Out port, set to 0 to get buttons
def PORT_OUT2           equ %00010000 ; P14 Out port, set to 0 to get buttons
def PORT_IN3            equ %00001000 ; P13 In port
def PORT_IN2            equ %00000100 ; P12 In port
def PORT_IN1            equ %00000010 ; P11 In port
def PORT_IN0            equ %00000001 ; P10 In port

; SB ($FF01)
; Serial Transfer Data (R/W)
def rTRANSFER           equ $FF01

; SC ($FF02)
; Serial I/O Control
def rSERIAL             equ $FF02
def SERIALF_START       equ %10000000 ; Transfer Start Flag (1=Transfer in progress or requested)
def SERIALF_SPEED       equ %00000010 ; Clock Speed (0=Normal, 1=Fast) ** CGB Mode Only **
def SERIALF_SOURCE      equ %00000001 ; Shift Clock (0=External, 1=Internal Clock)

def SERIALB_START       equ 7
def SERIALB_SPEED       equ 1
def SERIALB_SOURCE      equ 0

; DIV ($FF04)
; Divider register (R/W)
def rDIV                equ $FF04

; TIMA ($FF05)
; Timer counter (R/W)
def rTIMA               equ $FF05

; TMA ($FF06)
; Timer modulo (R/W)
def rTMA                equ $FF06

; TAC ($FF07)
; Timer control (R/W)
def rTAC                equ $FF07
def TACF_START          equ %00000100
def TACF_STOP           equ %00000000
def TACF_4KHZ           equ %00000000
def TACF_16KHZ          equ %00000011
def TACF_65KHZ          equ %00000010
def TACF_262KHZ         equ %00000001

; IF ($FF0F)
; Interrupt flag
def rIF                 equ $FF0F

; AUD1SWEEP/NR10 ($FF10)
; Sweep register (R/W)
; 
; Bit 6-4:      Sweep Time
; Bit 3:        Sweep Increase/Decrease
;                   0: Addition     (frequency increases?)
;                   1: Subtraction  (frequency decreases?)
; Bit 2-0:      Number of sweep shif (#0-7)
; Sweep Time:   (n*7.8ms)
def rNR10               equ $FF10
def rAUD1SWEEP          equ rNR10
def AUD1SWEEP_UP        equ %00000000
def AUD1SWEEP_DOWN      equ %00001000

; AUD1LEN/NR11 ($FF11)
; Sound length/Wave pattern duty (R/W)
;
; Bit 7-6:  Wave Pattern Duty (00=12.5%, 01=25%, 10=50%, 11=75%)
; Bit 5-0:  Sound length data (#0-63)
def rNR11               equ $FF11
def rAUD1LEN            equ rNR11

; AUD1ENV/NR12 ($FF12)
; Envelope (R/W)
;
; Bit 7-4:  Initial value of envelope
; Bit 3:    Envelope UP/DOWN
;               0: Decrease
;               1: Range of increase
; Bit 2-0:  Number of envelope sweep (#0-7)
def rNR12               equ $FF12
def rAUD1ENV            equ rNR12

; AUD1LOW/NR13 ($FF13)
; Frequency low byte (W)
def rNR13               equ $FF13
def rAUD1LOW            equ rNR13

; AUD1HIGH/NR14 ($FF14)
; Frequency high byte (W)
def rNR14               equ $FF14
def rAUD1HIGH           equ rNR14

; AUD2LEN/NR21 ($FF16)
; Sound length/Wave pattern duty (R/W)
;
; See AUD1LEN for more info
def rNR21               equ $FF16
def rAUD2LEN            equ rNR21

; AUD2ENV/NR22 ($FF17)
; Envelope (R/W)
;
; See AUD1ENV for more info
def rNR22               equ $FF17
def rAUD2ENV            equ rNR22

; AUD2LOW/NR23 ($FF18)
; Frequency low byte (W)
def rNR23               equ $FF18
def rAUD2LOW            equ rNR23

; AUD2HIGH/NR24 ($FF19)
; Frequency high byte (W)
def rNR24               equ $FF19
def rAUD2HIGH           equ rNR24

; AUD3ENA/NR30 ($FF1A)
; Sound on/off (R/W)
;
; Bit 7:    Sound on/off (1=on, 0=off)
def rNR30               equ $FF1A
def rAUD3ENA            equ rNR30
def AUD3ENA_OFF         equ %00000000
def AUD3ENA_ON          equ %10000000

; AUD3LEN/NR31 ($FF1B)
; Sound length (R/W)
;
; Bit 7-0:  Sound length
def rNR31               equ $FF1B
def rAUD3LEN            equ rNR31

; AUD3LEVEL/NR32 ($FF1C)
; Select output level
;
; Bit 6-5:  Select output level
;           00: 0/1 (mute)
;           01: 1/1
;           10: 1/2
;           11: 1/4
def rNR32               equ $FF1C
def rAUD3LEVEL          equ rNR32
def AUD3LEVEL_MUTE      equ %00000000
def AUD3LEVEL_100       equ %00100000
def AUD3LEVEL_50        equ %01000000
def AUD3LEVEL_25        equ %01100000

; AUD3LOW/NR33 ($FF1D)
; Frequency low byte (W)
def rNR33               equ $FF1D
def rAUD3LOW            equ rNR33

; AUD3HIGH/NR34 ($FF1E)
; Frequency high byte (W)
def rNR34               equ $FF1E
def rAUD3HIGH           equ rNR34

; AUD4LEN/NR41 ($FF20)
; Sound length (R/W)
;
; Bit 5-0:  Sound length data (#0-63)
def rNR41               equ $FF20
def rAUD4LEN            equ rNR41

; AUD4ENV/NR42 ($FF21)
; Envelope (R/W)
;
; See AUD1ENV for more info
def rNR42               equ $FF21
def rAUD4ENV            equ rNR42

; AUD4POLY/NR43 ($FF22)
; Polynomial counter (R/W)
;
; Bit 7-4:  Selection of the shift clock frequency of the (scf)
;           polynomial counter (0000-1101)
;           freq=drf*1/2^scf (not sure)
; Bit 3:    Selection of the polynomial counter's step
;               0: 15 steps
;               1: 7 steps
; Bit 2-0:  Selection of the dividing ratio of frequencies (drf)
;               000: f/4
;               001: f/8
;               010: f/16
;               011: f/24
;               100: f/32
;               101: f/40
;               110: f/48
;               111: f/56
;           f = 4.194304 MHz
def rNR43               equ $FF22
def rAUD4POLY           equ rNR43
def AUD4POLY_15STEP     equ %00000000
def AUD4POLY_7STEP      equ %00001000

; AUD4GO/NR44 ($FF23)
; Bit 7:    Initial (when set, sound restarts)
; Bit 6:    Counter/consecutive selection
def rNR44               equ $FF23
def rAUD4GO             equ rNR44

; AUDVOL/NR50 ($FF24)
; Channel control / On-Off / Volume (R/W)
;
; Bit 7:    Vin->SO2 On/Off (left)
; Bit 6-4:  SO2 output level (left speaker) (#0-7)
; Bit 3:    Vin->SO1 On/Off (right)
; Bit 2-0:  SO1 output level (right speaker) (#0-7)
def rNR50               equ $FF24
def rAUDVOL             equ rNR50
def AUDVOL_VIN_LEFT     equ %10000000 ; SO2
def AUDVOL_VIN_RIGHT    equ %00001000 ; SO2

; AUDTERM/NR51 ($FF25)
; Selection of sound output terminal (R/W)
;
; Bit 7:    Output channel 4 to SO2 terminal (left)
; Bit 6:    Output channel 3 to SO2 terminal (left)
; Bit 5:    Output channel 2 to SO2 terminal (left)
; Bit 4:    Output channel 1 to SO2 terminal (left)
; Bit 3:    Output channel 4 to SO1 terminal (right)
; Bit 2:    Output channel 3 to SO1 terminal (right)
; Bit 1:    Output channel 2 to SO1 terminal (right)
; Bit 0:    Output channel 1 to SO1 terminal (right)
def rNR51               equ $FF25
def rAUDTERM            equ rNR51
def AUDTERM_4_LEFT      equ %10000000
def AUDTERM_3_LEFT      equ %01000000
def AUDTERM_2_LEFT      equ %00100000
def AUDTERM_1_LEFT      equ %00010000
def AUDTERM_4_RIGHT     equ %00001000
def AUDTERM_3_RIGHT     equ %00000100
def AUDTERM_2_RIGHT     equ %00000010
def AUDTERM_1_RIGHT     equ %00000001

; AUDENA/NR52 ($FF26)
; Sound on/off (R/W)
;
; Bit 7:    All sound on/off (sets ALL audio regs to 0!) (R/W)
; Bit 3:    Sound 4 ON flag (R)
; Bit 2:    Sound 3 ON flag (R)
; Bit 1:    Sound 2 ON flag (R)
; Bit 0:    Sound 1 ON flag (R)
def rNR52               equ $FF26
def rAUDENA             equ rNR52
def AUDENA_ON           equ %10000000
def AUDENA_OFF          equ %00000000 ; Sets ALL audio regs to 0!

; LCDC ($FF40)
; LCD Control (R/W)
def rLCDC               equ $FF40
def LCDCF_OFF           equ %00000000 ; LCD Control Operation
def LCDCF_ON            equ %00000000 ; LCD Control Operation
def LCDCF_WIN9800       equ %00000000 ; Window Tile Map Display Select
def LCDCF_WIN9C00       equ %00000000 ; Window Tile Map Display Select
def LCDCF_WINOFF        equ %00000000 ; Window Display
def LCDCF_WINON         equ %00000000 ; Window Display
def LCDCF_BG8800        equ %00000000 ; BG & Window Tile Data Select
def LCDCF_BG8000        equ %00000000 ; BG & Window Tile Data Select
def LCDCF_BG9800        equ %00000000 ; BG Tile Map Display Select
def LCDCF_BG9C00        equ %00000000 ; BG Tile Map Display Select
def LCDCF_OBJ8          equ %00000000 ; OBJ Construction
def LCDCF_OBJ16         equ %00000000 ; OBJ Construction
def LCDCF_OBJOFF        equ %00000000 ; OBJ Display
def LCDCF_OBJON         equ %00000000 ; OBJ Display
def LCDCF_BGOFF         equ %00000000 ; BG Display
def LCDCF_BGON          equ %00000000 ; BG Display
; Window Character Data Select follows BG

; STAT ($FF41)
; LCD Status (R/W)
def rSTAT               equ $FF41
def STATF_LYC           equ %01000000 ; LYC==LY Coincidence (Selectable)
def STATF_MODE10        equ %00100000 ; Mode 10
def STATF_MODE01        equ %00010000 ; Mode 01 (V-Blank)
def STATF_MODE00        equ %00001000 ; Mode 00 (H-Blank)
def STATF_LYCF          equ %00000100 ; Coincidence Flag
def STATF_HBL           equ %00000000 ; H-Blank
def STATF_VBL           equ %00000001 ; H-Blank
def STATF_OAM           equ %00000010 ; OAM-RAM is used by system
def STATF_LCD           equ %00000011 ; Both OAM and VRAM used by system
def STATF_BUSY          equ %00000010 ; When set, VRAM access is unsafe

def STATB_LYC           equ 6
def STATB_MODE10        equ 5
def STATB_MODE01        equ 4
def STATB_MODE00        equ 3
def STATB_LYCF          equ 2
def STATB_BUSY          equ 1

; SCY ($FF42)
; Scroll Y (R/W)
def rSCY                equ $FF42

; SCX ($FF43)
; Scroll X (R/W)
def rSCX                equ $FF43

; LY ($FF44)
; LCDC Y-Coordinate (R)
; Values range from 0-153. 144-153 is the VBlank period.
def rLY                 equ $FF44

; LYC ($FF45)
; LY Compare (R/W)
; When LY==LYC, STATF_LYCF will be set in STAT
def rLYC                equ $FF45

; DMA ($FF46)
; DMA Transfer and Start Address (W)
def rDMA                equ $FF46

; BGP ($FF47)
; BG Palette Data (W)
;
; Bit 7-6:  Intensity for %11
; Bit 5-4:  Intensity for %10
; Bit 3-2:  Intensity for %01
; Bit 1-0:  Intensity for %00
def rBGP                equ $FF47

; OBP0 ($FF48)
; Object Palette 0 Data (W)
def rOBP0               equ $FF48

; OBP1 ($FF49)
; Object Palette 1 Data (W)
def rOBP1               equ $FF49

; WINY ($FF4A)
; Window Y Position (R/W)
;
; 0 <= WINY <= 143
; When WINY==0, the window is displayed from the top edge of the LCD screen.
def rWINY               equ $FF4A

; WINX ($FF4B)
; Window X Position (R/W)
;
; 7 <= WINX <= 166
; When WINX==7, the window is displayed from the left edge of the LCD screen.
; Values of 0-6 and 166+ are unreliable due to hardware bugs
def rWINX               equ $FF4B
def WINX_OFS            equ 7 ; add to a screen position to get a WINX position

; SPEED ($FF4D)
; Select CPU Speed (R/W)
def rKEY1               equ $FF4D
def rSPEED              equ rKEY1
def KEY1F_DBLSPEED      equ %10000000 ; 0=Normal Speed, 1=Double Speed (R)
def KEY1F_PREPARE       equ %00000001 ; 0=No, 1=Prepare (R/W)

; VBK ($FF4F)
; Select Video Ram Bank (R/W)
;
; Bit 0:    Bank Specification (0: Specify Bank 0; 1: Specify Bank 1)
def rVBK                equ $FF4F

; HDMA1 ($FF51)
; High byte for Horizontal Blanking/General Purpose DMA source address (W)
; CGB Mode Only
def rHDMA1              equ $FF51

; HDMA2 ($FF52)
; Low byte for Horizontal Blanking/General Purpose DMA source address (W)
; CGB Mode Only
def rHDMA2              equ $FF52

; HDMA3 ($FF53)
; High byte for Horizontal Blanking/General Purpose DMA destination address (W)
; CGB Mode Only
def rHDMA3              equ $FF53

; HDMA4 ($FF54)
; Low byte for Horizontal Blanking/General Purpose DMA destination address (W)
; CGB Mode Only
def rHDMA4              equ $FF54

; HDMA5 ($FF55)
; Transfer length (in tiles minus 1)/mode/start for Horizontal Blanking, General Purpose DMA (R/W)
; CGB Mode Only
def rHDMA5              equ $FF55
def HDMA5_MODE_GP       equ %00000000 ; General Purpose DMA (W)
def HDMA5_MODE_HBL      equ %10000000 ; HBlank DMA (W)
; -- Once DMA has started, use HDMA5F_BUSY to check when the transfer is complete --
def HDMA5_BUSY          equ %10000000 ; 0=Busy (DMA still in progress), 1=Transfer complete (R)

; RP ($FF56)
; Infrared Communications Port (R/W)
; CGB Mode Only
def rRP                 equ $FF56
def RPF_ENREAD          equ %11000000
def RPF_DATAIN          equ %00000010 ; 0=Receiving IR Signal, 1=Normal
def RPF_WRITE_HI        equ %00000001
def RPF_WRITE_LO        equ %00000000

; BCPS ($FF68)
; Background Color Palette Specification (R/W)
def rBCPS               equ $FF68
def BCPSF_AUTOINC       equ %10000000 ; Auto Increment (0=Disabled, 1=Increment after writing)

; BCPD ($FF69)
; Background Color Palette Data (R/W)
def rBCPD               equ $FF69

; OCPS ($FF6A)
; Object Color Palette Specification (R/W)
def rOCPS               equ $FF6A
def OCPSF_AUTOINC       equ %10000000 ; Auto Increment (0=Disabled, 1=Increment after writing)

; OCPD ($FF6B)
; Object Color Palette Data (R/W)
def rOCPD               equ $FF6B

; SMBK/SVBK ($FF70)
; Select Main RAM Bank (R/W)
;
; Bit 2-0:  Bank Specification (0-1: Specify Bank 1, 2-7: Specify Banks 2-7)
def rSVBK               equ $FF70
def rSMBK               equ rSVBK

; PCM12 ($FF76)
; Sound channel 3 & 4 PCM amplitude (R)
;
; Bit 7-4:  Copy of sound channel 2's PCM amplitude
; Bit 3-0:  Copy of sound channel 1's PCM amplitude
def rPCM34              equ $FF76

; PCM34 ($FF77)
; Sound channel 3 & 4 PCM amplitude (R)
;
; Bit 7-4:  Copy of sound channel 4's PCM amplitude
; Bit 3-0:  Copy of sound channel 3's PCM amplitude
def rPCM34              equ $FF77

; IE register ($FFFF)
; Interrupt Enable (R/W)
def rIE                 equ $FFFF
def IEF_HILO            equ %00010000 ; Transition from high to low of pins P10-P13
def IEF_SERIAL          equ %00001000 ; Serial I/O transfer end
def IEF_TIMER           equ %00000100 ; Timer Overflow
def IEF_STAT            equ %00000010 ; STAT
def IEF_VBLANK          equ %00000001 ; V-Blank

def IEB_HILO            equ 4 ; Transition from high to low of pins P10-P13
def IEB_SERIAL          equ 3 ; Serial I/O transfer end
def IEB_TIMER           equ 2 ; Timer Overflow
def IEB_STAT            equ 1 ; STAT
def IEB_VBLANK          equ 0 ; V-Blank

; ******************************************************************************
; Flags common to multiple sound channels
; ******************************************************************************
; Square wave duty cycle
; Can be used with AUD1LEN and AUD2LEN
; See AUD1LEN for more info
def AUDLEN_DUTY_12_5    equ %00000000 ; 12.5%
def AUDLEN_DUTY_25      equ %01000000 ; 25%
def AUDLEN_DUTY_50      equ %10000000 ; 50%
def AUDLEN_DUTY_75      equ %11000000 ; 75%

; Audio envelope flags
; Can be used with AUD1ENV, AUD2ENV, and AUD4ENV
; See AUD1ENV for more info
def AUDENV_UP           equ %00001000
def AUDENV_DOWN         equ %00000000

; Audio trigger flags
; Can be used with AUD1HIGH, AUD2HIGH, and AUD4HIGH
; See AUD1HIGH for more info
def AUDHIGH_RESTART     equ %10000000
def AUDHIGH_LENGTH_ON   equ %01000000
def AUDHIGH_LENGTH_OFF  equ %00000000

; ******************************************************************************
; CPU values on bootup (a=type, b=qualifier)
; ******************************************************************************
def BOOTUP_A_DMG    equ $01 ; Dot Matrix Game
def BOOTUP_A_CGB    equ $11 ; Color Game Boy
def BOOTUP_A_MGB    equ $FF ; Mini Game Boy (Game Boy Pocket) 

; If A==BOOTUP_A_CGB, bit 0 in b can be checked to determin if running on a
; real CGB or another system running in GBC mode
def BOOTUP_B_CGB    equ %00000000
def BOOTUP_B_AGB    equ %00000001 ; GBA, GBA SP, Game Boy Player, or New GBA SP

; ******************************************************************************
; Cartridge related
; ******************************************************************************
; $0143 Color Game Boy compatibility code
def CART_COMPATIBLE_DMG             equ $00
def CART_COMPATIBLE_DMG_GBC         equ $80
def CART_COMPATIBLE_GBC             equ $C0

; $0146 Game Boy / Super Game Boy indicator
def CART_INDICATOR_GB               equ $00
def CART_INDICATOR_SGB              equ $03

; $0147 Cartridge type
def CART_ROM                        equ $00
def CART_ROM_MBC1                   equ $01
def CART_ROM_MBC1_RAM               equ $02
def CART_ROM_MBC1_RAM_BAT           equ $03
def CART_ROM_MBC2                   equ $05
def CART_ROM_MBC2_BAT               equ $06
def CART_ROM_RAM                    equ $08
def CART_ROM_RAM_BAT                equ $09
def CART_ROM_MM01                   equ $0B
def CART_ROM_MM01_RAM               equ $0C
def CART_ROM_MM01_RAM_BAT           equ $0D
def CART_ROM_MBC3_BAT_RTC           equ $0F
def CART_ROM_MBC3_RAM_BAT_RTC       equ $10
def CART_ROM_MBC3                   equ $11
def CART_ROM_MBC3_RAM               equ $12
def CART_ROM_MBC3_RAM_BAT           equ $13
def CART_ROM_MBC5                   equ $19
def CART_ROM_MBC5_BAT               equ $1A
def CART_ROM_MBC5_RAM_BAT           equ $1B
def CART_ROM_MBC5_RUMBLE            equ $1C
def CART_ROM_MBC5_RAM_RUMBLE        equ $1D
def CART_ROM_MBC5_RAM_BAT_RUMBLE    equ $1E
def CART_ROM_MBC7_RAM_BAT_GYRO      equ $22
def CART_ROM_POCKET_CAMERA          equ $FC
def CART_ROM_BANDAI_TAMA5           equ $FD
def CART_ROM_HUDSON_HUC3            equ $FE
def CART_ROM_HUDSON_HUC1            equ $FF

; $0148 ROM size
; Measured below in kilobytes
def CART_ROM_32KB                   equ $00 ; 2 banks
def CART_ROM_64KB                   equ $01 ; 4 banks
def CART_ROM_128KB                  equ $02 ; 8 banks
def CART_ROM_256KB                  equ $03 ; 16 banks
def CART_ROM_512KB                  equ $04 ; 32 banks
def CART_ROM_1024KB                 equ $05 ; 64 banks
def CART_ROM_2048KB                 equ $06 ; 128 banks
def CART_ROM_4096KB                 equ $07 ; 256 banks
def CART_ROM_8192KB                 equ $08 ; 512 banks
def CART_ROM_1152KB                 equ $52 ; 72 banks
def CART_ROM_1280KB                 equ $53 ; 80 banks
def CART_ROM_1536KB                 equ $54 ; 96 banks

; $0149 SRAM size
def CART_SRAM_NONE                  equ 0
def CART_SRAM_2KB                   equ 1 ; 1 incomplete bank
def CART_SRAM_8KB                   equ 2 ; 1 bank
def CART_SRAM_32KB                  equ 3 ; 4 banks
def CART_SRAM_128KB                 equ 4 ; 16 banks

def CART_SRAM_ENABLE                equ $0A
def CART_SRAM_DISABLE               equ $00

; $014A Destination code
def CART_DEST_JAPANESE              equ $00
def CART_DEST_NON_JAPANESE          equ $01

; ******************************************************************************
; Keypad related
; ******************************************************************************
def PADF_DOWN   equ $80
def PADF_UP     equ $40
def PADF_LEFT   equ $20
def PADF_RIGHT  equ $10
def PADF_START  equ $08
def PADF_SELECT equ $04
def PADF_B      equ $02
def PADF_A      equ $01

def PADB_DOWN   equ $7
def PADB_UP     equ $6
def PADB_LEFT   equ $5
def PADB_RIGHT  equ $4
def PADB_START  equ $3
def PADB_SELECT equ $2
def PADB_B      equ $1
def PADB_A      equ $0

; ******************************************************************************
; Screen related
; ******************************************************************************
def SCRN_X      equ 160 ; Width of screen in pixels
def SCRN_Y      equ 144 ; Height of screen in pixels
def SCRN_X_B    equ 20 ; Width of screen in bytes 
def SCRN_Y_B    equ 18 ; Height of screen in bytes

def SCRN_VX     equ 256 ; Virtual width of screen in pixels
def SCRN_VY     equ 256 ; Virtual height of screen in pixels
def SCRN_VX_B   equ 32  ; Virtual width of screen in bytes 
def SCRN_VY_B   equ 32  ; Virtual height of screen in bytes 

; ******************************************************************************
; OAM related
; ******************************************************************************
; OAM attributes
; Each entry in OAM RAM is 4 bytes (sizeof_OAM_ATTRS)
rsreset
def OAMA_Y              rb 1 ; y pos plus 16
def OAMA_X              rb 1 ; y pos plus 16
def OAMA_TILEID         rb 1 ; y pos plus 16
def OAMA_FLAGS          rb 1 ; y pos plus 16
def sizeof_OAM_ATTRS    rb 0

def OAM_Y_OFS           equ 16 ; Add to a screen-relative Y position to get an OAM Y position
def OAM_X_OFS           equ 8  ; Add to a screen-relative Y position to get an OAM Y position

def OAM_COUNT           equ 40 ; Number of OAM entries in OAM RAM

; Flags
def OAMF_PRI            equ %10000000 ; Priority
def OAMF_YFLIP          equ %01000000 ; Y flip
def OAMF_XFLIP          equ %00100000 ; X flip
def OAMF_PAL0           equ %00000000 ; Palette number; 0,1 (DMG)
def OAMF_PAL1           equ %00010000 ; Palette number; 0,1 (DMG)
def OAMF_BANK0          equ %00000000 ; Bank number; 0,1 (GBC)
def OAMF_BANK1          equ %00001000 ; Bank number; 0,1 (GBC)

def OAMF_PALMASK        equ %00000011 ; Palette (GBC)

def OAMB_PRI            equ 7 ; Priority
def OAMB_YFLIP          equ 6 ; Y flip
def OAMB_XFLIP          equ 5 ; X flip
def OAMB_PAL1           equ 4 ; Palette number; 0,1 (DMG)
def OAMB_BANK1          equ 3 ; Bank number; 0,1 (GBC)

; ******************************************************************************
; Nintendo scrolling logo
; (Code won't work on a real Game Boy if these bytes are altered)
; ******************************************************************************
macro NINTENDO_LOGO
    db  $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D
    db  $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
    db  $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E
endm

; vim: filetype=rgbds
