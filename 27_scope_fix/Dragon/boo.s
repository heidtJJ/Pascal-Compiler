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
	movq	%rax, -36(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -20(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$2, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -24(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$3, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -28(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-20(%rbp), %ebx
	movl	-24(%rbp), %ecx
	addl	-28(%rbp), %ecx

	imull	%ecx, %ebx

	movl	-20(%rbp), %ecx
	movl	-20(%rbp), %edi
	imull	-24(%rbp), %edi

	addl	-20(%rbp), %edi

	imull	%edi, %ecx

	addl	%ecx, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -8(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-8(%rbp), %ebx
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
