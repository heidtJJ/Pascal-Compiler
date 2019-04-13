	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$8, %rsp # lowering the stack pointer.
	movl	$13, %eax  # moved register values
	movl	%eax, -4(%rbp)  # moved register values
	movl	$12, %eax  # moved register values
	movl	%eax, -8(%rbp)  # moved register values
	movl	-4(%rbp), %eax  # moved register values
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %eax  # moved register values
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	-4(%rbp), %eax  # moved register values
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %eax  # moved register values
	movl	%eax, -4(%rbp)  # moved register values
	movl	-4(%rbp), %eax  # moved register values
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	leave
	ret
.boo:
	.size	boo, .-boo
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	call	boo
	movl	$0, %eax
	leave
	ret
.main:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits
