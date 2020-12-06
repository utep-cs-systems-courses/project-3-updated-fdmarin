	.arch msp430g2553
	.p2align 1,0
	.text			;jt is constant (in flash)


	.extern changed
	.extern led_changed
	.extern alternate
	.extern red_blink
	.extern toggle_green
	.extern dimLights
	.global state_advance

jt:
	.word case0		;jt[0]
	.word case1		;jt[1]
	.word case2		;jt[2]
	.word case3		;jt[3]

state_advance:
	;; range check on selector (changed)
	cmp.b #4, &changed	;changed-4 wont borrow if changed >3
	jhs end			;jmp if changed >3

	;; index into jt
	mov.b &changed,r13
	add.b  r13,r13		;r13 = 2*changed
	mov jt(r13),r0		;jmp jt[changed]

case0:
	call #alternate		;alternate()
	mov r12, &changed
	jmp end			;break

case1:
	call #red_blink		;red_blink()
	mov r12, &changed
	jmp end			;break

case2:
	call #toggle_green	;toggle_green()
	mov r12, &changed
	jmp end			;break

case3:
	call #dimLights		;dimLights()
	move r12, &changed	;break

end:
	mov r12, &led_changed	;led_changed=0
	call #led_update	;led_update()
	mov.b #1, r12		;return 0
	pop r0
