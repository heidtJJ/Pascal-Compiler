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
boo_gcd:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -20(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	60(%rbp), %eax
	movl	%eax, -12(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-12(%rbp), %ebx
	cmpl	$0, %ebx
	setz	%al
	movzbl	%al, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	cmpl	$0, %ebx
	je	.L0
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-8(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %esi
	jmp	.L1
.L0:
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	# Putting current return value to temporary location before function call.
	movl	%esi, -48(%rbp)
	movq	-20(%rbp), %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-8(%rbp), %ebx
	movl	-12(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	%ebx, %eax
	cltd
	idivl	-44(%rbp)
	movl	%edx, %ebx

	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -68(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_gcd
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	movl	%esi, %ebx
	# Restoring current return value to temporary location after function call.
	movl	-48(%rbp), %esi
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %esi
.L1:
	leave
	ret
.boo_gcd:
	.size	boo_gcd, .-boo_gcd
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -20(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	# Putting current return value to temporary location before function call.
	movl	%esi, -48(%rbp)
	movq	%rbp, %rax
	movq	%rax, -80(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-8(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	-12(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -68(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_gcd
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	movl	%esi, %ebx
	# Restoring current return value to temporary location after function call.
	movl	-48(%rbp), %esi
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
