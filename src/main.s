; Nintendo Logo wobble test
section "HEADER", ROM0[$0100]
    nop
    jp wobble_main
    ; ROM header
    db $CE,$ED,$66,$66,$CC,$0D,$00,$0B
	db $03,$73,$00,$83,$00,$0C,$00,$0D
	db $00,$08,$11,$1F,$88,$89,$00,$0E
	db $DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
	db $BB,$BB,$67,$63,$6E,$0E,$EC,$CC
    db $DD,$DC,$99,$9F,$BB,$B9,$33,$3E
    db "MetaGB", $00
    ; Entry
section "MetaGB", ROM0[$0150]
wobble_main:
    ; E is our lookup table offset
    ld e, $00
    ; Initialize H to the
    ; MSB of WOBBLE_DATA
    ld h, $20
wobble_loop:
    ; B will be the scanline that
    ; we want to transform
    ld b, $00
.inner_loop:
    ; Load current scanline position
    ; and compare to B
    ldh a, [$44]
    cp b
    jr nz, .inner_loop
    ld a, b
    inc b
    add a, e
    and $1F
    ; Use current scanline position
    ; and LUT offset to calculate
    ; the index into lookup table
    ; idx = (scanline + lut_offset) & 0x1F
    ld l, a
    ld a, [hl]
    ; add a, e
    ; scroll_x = lut[idx]
    ldh [$43], a
    ld a, l
    add a, $04
    and $1F
    ld l, a
    ld a, [hl]
    ; idx = (idx + 9) & 0x1F
    ; scroll_y = lut[idx]
    ldh [$42], a
    ldh [$42], a
    ldh a, [$44]
    ; Finally, check if  we've
    ; reached vblank to break
    ; the loop
    cp $90
    jr nz, .inner_loop
    ; Increment lookup table offset
    inc e
    jr wobble_loop

    ; Simple sine wave lookup table
section "WOBBLE_DATA", ROM0[$2000]
    db $00,$00,$01,$01,$02,$02,$02,$02
	db $02,$02,$02,$02,$01,$01,$00,$00
	db $00,$00,$FF,$FF,$FE,$FE,$FE,$FE
	db $FE,$FE,$FE,$FE,$FF,$FF,$00,$00
