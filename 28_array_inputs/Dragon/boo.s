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
boo_MyProcedure:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -36(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	60(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	64(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	68(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	72(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	76(%rbp), %eax
	movl	%eax, -28(%rbp)
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
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	movl	-24(%rbp, %rbx, 4), %ebx
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
	movl	$96, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -60(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	-60(%rbp), %ecx
	movl	%ecx, -24(%rbp, %rbx, 4)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	movl	-24(%rbp, %rbx, 4), %ebx
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
	movl	-28(%rbp), %ebx
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
	movl	$69, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movl	%ebx, -60(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movq	-36(%rbp), %rax
	movl	-60(%rbp), %ecx
	movl	%ecx, -24(%rax, %rbx, 4)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1, %ebx
	movq	-36(%rbp), %rax
	movl	-24(%rax, %rbx, 4), %ebx
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
	movl	$1, %ebx
	movl	-24(%rbp, %rbx, 4), %ebx
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
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$999, %ebx
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
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$1001, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movq	-36(%rbp), %rax
	movl	%ebx, -8(%rax)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movl	$8008, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	movq	-36(%rbp), %rax
	movl	%ebx, -24(%rax)
	leave
	ret
.boo_MyProcedure:
	.size	boo_MyProcedure, .-boo_MyProcedure
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$96, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -32(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$12, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, -56(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$1, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	-56(%rbp), %ecx
	movl	%ecx, -24(%rbp, %rbx, 4)
	# Putting current return value to temporary location before expression.
	movl	%esi, -52(%rbp)
	movq	%rbp, %rax
	movq	%rax, -96(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$666, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -88(%rbp)
	movl	$3, %ebx
	movl	-24(%rbp, %rbx, 4), %eax
	movl	%eax, -84(%rbp)
	movl	$2, %ebx
	movl	-24(%rbp, %rbx, 4), %eax
	movl	%eax, -80(%rbp)
	movl	$1, %ebx
	movl	-24(%rbp, %rbx, 4), %eax
	movl	%eax, -76(%rbp)
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$2, %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	movl	%ebx, %eax
	movl	%eax, -72(%rbp)
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_MyProcedure
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	# Restoring current return value to temporary location after expression.
	movl	-52(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	$1, %ebx
	movl	-24(%rbp, %rbx, 4), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -36(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-36(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	-8(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -36(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-36(%rbp), %esi
	# Putting current return value to temporary location before expression.
	movl	%esi, -48(%rbp)
	movl	-24(%rbp), %ebx
	# Restoring current return value to temporary location after expression.
	movl	-48(%rbp), %esi
	# Putting current return value to temporary location printf.
	movl	%esi, -36(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	# Restoring current return value to temporary location after printf.
	movl	-36(%rbp), %esi
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
