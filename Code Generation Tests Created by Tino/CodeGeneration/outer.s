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
outer_middle_alpha:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$42, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movl	%ebx, -16(%rax)
	leave
	ret
.outer_middle_alpha:
	.size	outer_middle_alpha, .-outer_middle_alpha
	.globl	main
	.type	main, @function
outer_middle_beta:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	-8(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	outer_middle_alpha
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	leave
	ret
.outer_middle_beta:
	.size	outer_middle_beta, .-outer_middle_beta
	.globl	main
	.type	main, @function
outer_middle:
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
	movl	$0, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	outer_middle_beta
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	leave
	ret
.outer_middle:
	.size	outer_middle, .-outer_middle
	.globl	main
	.type	main, @function
outer:
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
	movl	%ebx, -16(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -60(%rbp)
	movq	%rbp, %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	$5, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-56(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	outer_middle
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-60(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -56(%rbp)
	movl	-16(%rbp), %ebx
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
.outer:
	.size	outer, .-outer
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	call	outer
	movl	$0, %eax
	leave
	ret
.main:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits