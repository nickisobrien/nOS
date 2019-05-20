# macro defined for irq's that don't push an error code onto the stack
.macro isr_noerrcode num
	.global isr\num
	isr\num:
		cli
		pushl $0 # error code 0
		pushl $\num
		jmp isr_common_stub
.endm

# macro defined for irq's that push an error code onto the stack
.macro isr_errcode num
	.global isr\num
	isr\num:
		cli
		pushl $\num
		jmp isr_common_stub
.endm

# create a bunch of functions using the above macros
isr_noerrcode 0
isr_noerrcode 1
isr_noerrcode 2
isr_noerrcode 3
isr_noerrcode 4
isr_noerrcode 5
isr_noerrcode 6
isr_noerrcode 7
isr_errcode 8
isr_noerrcode 9
isr_errcode 10
isr_errcode 11
isr_errcode 12
isr_errcode 13
isr_errcode 14
isr_noerrcode 15
isr_noerrcode 16
isr_noerrcode 17
isr_noerrcode 18
isr_noerrcode 19
isr_noerrcode 20
isr_noerrcode 21
isr_noerrcode 22
isr_noerrcode 23
isr_noerrcode 24
isr_noerrcode 25
isr_noerrcode 26
isr_noerrcode 27
isr_noerrcode 28
isr_noerrcode 29
isr_noerrcode 30
isr_noerrcode 31

isr_noerrcode 32
isr_noerrcode 33

# This is the common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common_stub:
	pusha # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	movw $0x10, %ax # Load the Kernel Data Segment descriptor!
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movl %esp, %eax # Push us the stack
	pushl %eax
	call isr_handler
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	addl $8, %esp # Cleans up the pushed error code and pushed ISR number
	sti
	iret # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
