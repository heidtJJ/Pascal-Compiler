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
	movl	$6, %ebx
	movl	%ebx, -12(%rbp)
	movl	$1, %ebx
	movl	%ebx, -8(%rbp)
	jmp	.L1
.L0:
	movl	-8(%rbp), %ebx
	addl	$1, %ebx

	movl	%ebx, -8(%rbp)
	movl	-12(%rbp), %ebx
	addl	$1, %ebx

	movl	%ebx, -12(%rbp)
.L1:
	movl	-8(%rbp), %ebx
	cmpl	$4, %ebx
	setle	%al
	movzbl	%al, %ebx

	cmpl	$1, %ebx
	je	.L0
	movl	-12(%rbp), %ebx
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
