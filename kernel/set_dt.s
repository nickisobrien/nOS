.global gdt_set
.global idt_set

# sets up gdt by passing lgdt formatted info about gdt
# and passes the new info to registers then moves cs register to new position
gdt_set:
	movl 4(%esp),%eax	# Get the pointer to the GDT, passed as a parameter.
	lgdt (%eax)			# Load the new GDT pointer

	movw $0x10, %ax		# 0x10 is the offset in the GDT to our data segment (8 bytes * 2 because null and code segment come first)
	movw %ax, %ds		# Load all data segment selectors
	movw %ax, %es		# Load all data segment selectors
	movw %ax, %fs		# Load all data segment selectors
	movw %ax, %gs		# Load all data segment selectors
	movw %ax, %ss		# Load all data segment selectors
	jmp  $0x08,$fin	 	# far jump to code segment (CS register) gdt and set instruction pointer (IP) to flush
						# the above line is how you can change the value in the cs register
fin:
	ret

# sets up idt by passing in lidt formatted info about idt
idt_set:
	movl 4(%esp), %eax	# Get the pointer to the IDT, passed as a parameter. 
	lidt (%eax)			# Load the IDT pointer.
	ret
