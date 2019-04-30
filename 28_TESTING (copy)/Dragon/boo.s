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
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -20(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -40(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-40(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-12(%rbp), %ebx
	addl	$1, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
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
	subq	$128, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -76(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	# Putting current return value to temporary location before expression.
	movl	%esi, -108(%rbp)
	movl	$1, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-108(%rbp), %esi
	movl	%ebx, -12(%rbp)
	jmp	.L1
.L0:
.L1:
	# Putting current return value to temporary location before expression.
	movl	%esi, -108(%rbp)
	movl	-12(%rbp), %ebx
	cmpl	-8(%rbp), %ebx
	setle	%al
	movzbl	%al, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-108(%rbp), %esi
	cmpl	$1, %ebx
	je	.L0
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
