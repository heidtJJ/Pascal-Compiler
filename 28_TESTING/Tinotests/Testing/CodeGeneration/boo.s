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
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$303, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movq	-16(%rbp), %rax
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
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movq	%rbp, %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$202, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_bar_moo
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	leave
	ret
.boo_bar:
	.size	boo_bar, .-boo_bar
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -24(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	$0, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-56(%rbp), %esi
	movl	%ebx, -12(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-56(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -44(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-44(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -60(%rbp)
	movq	%rbp, %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	$101, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-56(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_bar
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-60(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-56(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -44(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-44(%rbp), %esi
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
