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
foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	20(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %ebx

	imull	$10, %ebx

	movl	%ebx, %esi
	movl	$4, %ebx
	movl	%ebx, -12(%rbp)
	movl	-12(%rbp), %ebx
	movl	%ebx, %esi
	leave
	ret
.foo:
	.size	foo, .-foo
	.globl	main
	.type	main, @function
coo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	$22, %ebx
	movl	%ebx, -8(%rbp)
	movl	-8(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	leave
	ret
.coo:
	.size	coo, .-coo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-8(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$1, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$0, %esi
	call	coo
	movl	-8(%rbp), %ebx
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
