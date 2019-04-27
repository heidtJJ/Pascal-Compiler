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
boo_bar_moo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	$303, %ebx
	movq	%rbp, %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movl	%ebx, -12(%rax)
	leave
	ret
.boo_bar_moo:
	.size	boo_bar_moo, .-boo_bar_moo
	.globl	main
	.type	main, @function
boo_bar:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	$202, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$0, %esi
	call	boo_bar_moo
	leave
	ret
.boo_bar:
	.size	boo_bar, .-boo_bar
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	$0, %ebx
	movl	%ebx, -12(%rbp)
	movl	-12(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$101, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$0, %esi
	call	boo_bar
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
