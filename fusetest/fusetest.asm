; Fuse regression testing harness

; Copyright 2007 Philip Kendall <philip-fuse@shadowmagic.org.uk>
	
; This program is licensed under the GNU General Public License. See the
; file `COPYING' for details

ORG 0xc000
	
main
PROC
	call interruptsync_init

	ld hl, _testdata

_test	ld a,(hl)
	cp 0x00
	jr z, _end

	call printstring
	inc hl
	push hl
	call _jumphl

	jr z, _pass
	ld b,a
	ld hl, _failstring1
	call printstring
	ld a,b
	call printa
	ld hl, _failstring2
	call printstring
	jr _next

_pass	ld hl, _passstring
	call printstring

_next	pop hl
	inc hl
	inc hl

	jr _test

_end	halt

_jumphl ld e,(hl)
	inc hl
	ld d,(hl)
	ex de,hl
	jp (hl)
	
_passstring defb '... passed', 0x0d, 0
_failstring1 defb '... failed (0x', 0
_failstring2 defb ')', 0x0d, 0

_testdata
	defb 'BIT n,(IX+d)', 0
	defw bitnixtest

	defb 'DAA', 0
	defw daatest

	defb 'LDIR', 0
	defw ldirtest

	defb 'Contended IN', 0
	defw contendedintest

	defb 0
	
ENDP

INCLUDE tests.asm
	
INCLUDE sync.asm
INCLUDE delay.asm
INCLUDE atiming.asm
INCLUDE print.asm

END	main