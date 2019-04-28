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
	subq	$96, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -60(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -76(%rbp)
	movl	-12(%rbp), %ebx
	imull	-12(%rbp), %ebx

	# Restoring current return value to temporary location after expression.
	movl	-76(%rbp), %esi
	movl	%ebx, -84(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -76(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-76(%rbp), %esi
	movl	-84(%rbp), %ecx
	movl	%ecx, -56(%rbp, %rbx, 4)
	# Putting current return value to temporary location before expression.
	movl	%esi, -76(%rbp)
	movl	-12(%rbp), %ebx
	addl	$1, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-76(%rbp), %esi
	movl	%ebx, -12(%rbp)
	leave
	ret
.boo:
	.size	boo, .-boo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$144, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -100(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -116(%rbp)
	movl	-12(%rbp), %ebx
	movl	-56(%rbp, %rbx, 4), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-116(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -104(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-104(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -116(%rbp)
	movl	-12(%rbp), %ebx
	addl	$1, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-116(%rbp), %esi
	movl	%ebx, -12(%rbp)
	leave
	ret
.boo:
	.size	boo, .-boo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$176, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -140(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	# Putting current return value to temporary location before expression.
	movl	%esi, -156(%rbp)
	movl	$0, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-156(%rbp), %esi
	movl	%ebx, -12(%rbp)
