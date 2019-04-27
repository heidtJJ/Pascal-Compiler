	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
.LC1:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	$2, %ebx  # moved register values
	movl	%ebx, -12(%rbp)  # moved register values
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	$16, %ebx  # moved register values

	movl	-8(%rbp), %ecx  # moved register values

	movl	-12(%rbp), %edi  # moved register values

	imull	-12(%rbp), %edi

	movl	-8(%rbp), %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%edi, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %edi  # moved register values

	movl	%edi, %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ecx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ecx  # moved register values

	imull	-8(%rbp), %ecx

	movl	-8(%rbp), %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ecx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ecx  # moved register values

	movl	$1, %edi  # moved register values

	addl	$1, %edi

	imull	%edi, %ecx

	movl	%ecx, %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ebx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ebx  # moved register values

	movl	$20, %ecx  # moved register values

	imull	-8(%rbp), %ecx

	movl	-12(%rbp), %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ecx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ecx  # moved register values

	addl	%ecx, %ebx

	movl	-12(%rbp), %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ebx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ebx  # moved register values

	movl	$3, %ecx  # moved register values

	addl	-8(%rbp), %ecx

	movl	%ecx, %eax  # moved register values
	movl	%eax, -16(%rbp)  # moved register values
	movl	%ebx, %eax  # moved register values
	cltd
	idivl	-16(%rbp)
	movl	%eax, %ebx  # moved register values

	movl	%ebx, %esi
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
