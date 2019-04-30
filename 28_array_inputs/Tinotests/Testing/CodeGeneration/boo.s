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
boo_moo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp # lowering the stack pointer.
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movq	%rbp, %rax
	movq	(%rax), %rax
	leaq	-8(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	# Putting current return value to temporary location before expression.
	movl	%esi, -24(%rbp)
	movq	%rbp, %rax
	movq	(%rax), %rax
	movl	-8(%rax), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-24(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -12(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-12(%rbp), %esi
	leave
	ret
.boo_moo:
	.size	boo_moo, .-boo_moo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$48, %rsp # lowering the stack pointer.
	# Putting current return value to temporary location before expression.
	movl	%esi, -32(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	# Putting current return value to temporary location before expression.
	movl	%esi, -28(%rbp)
	movl	$0, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-28(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -48(%rbp)
	call	boo_moo
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$16, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-32(%rbp), %esi
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
