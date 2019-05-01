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
boo_foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$80, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -28(%rbp)
	movl	56(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	60(%rbp), %eax
	movl	%eax, -12(%rbp)
	movq	-28(%rbp), %rax
	movl	-16(%rax), %ebx
	addl	$1, %ebx
	movl	%ebx, -16(%rbp)
	movl	-16(%rbp), %ebx
	subl	$1, %ebx
	movl	-16(%rbp), %ecx
	addl	$1, %ecx
	imull	%ecx, %ebx
	addl	$1, %ebx
	movl	%ebx, -20(%rbp)
	movl	-20(%rbp), %ebx
	movl	%ebx, %esi
	leave
	ret
.boo_foo:
	.size	boo_foo, .-boo_foo
	.globl	main
	.type	main, @function
boo_moo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$96, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -40(%rbp)
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
	movl	$8, %ebx
	movl	-52(%rbp, %rbx, 4), %ebx
	movl	%ebx, -28(%rbp)
	movl	-28(%rbp), %ebx
	subl	$1, %ebx
	movl	-28(%rbp), %ecx
	addl	$1, %ecx
	imull	%ecx, %ebx
	addl	$1, %ebx
	movl	%ebx, -32(%rbp)
	movl	-32(%rbp), %ebx
	movl	%ebx, %esi
	leave
	ret
.boo_moo:
	.size	boo_moo, .-boo_moo
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
	movl	-8(%rbp), %ebx
	addl	$1, %ebx
	movl	%ebx, %esi
	leave
	ret
.boo_bar:
	.size	boo_bar, .-boo_bar
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$112, %rsp # lowering the stack pointer.
	movq	48(%rbp), %rax
	movq	%rax, -44(%rbp)
	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-8(%rbp), %ebx
	addl	$1, %ebx
	movl	%ebx, -16(%rbp)
	movl	-8(%rbp), %ebx
	movl	%ebx, -84(%rbp)
	movl	$7, %ebx
	movl	-84(%rbp), %ecx
	movl	%ecx, -64(%rbp, %rbx, 4)
	# Putting current return value to temporary location before function call.
	movl	%esi, -72(%rbp)
	movq	%rbp, %rax
	movq	%rax, -112(%rbp)
	# Putting current return value to temporary location before function call.
	movl	%esi, -72(%rbp)
	movq	%rbp, %rax
	movq	%rax, -112(%rbp)
	movl	$6, %ebx
	movl	%ebx, %eax
	movl	%eax, -104(%rbp)
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_bar
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	movl	%esi, %ebx
	# Restoring current return value to temporary location after function call.
	movl	-72(%rbp), %esi
	movl	-64(%rbp, %rbx, 4), %ebx
	movl	%ebx, %eax
	movl	%eax, -104(%rbp)
	movl	-16(%rbp), %ebx
	movl	%ebx, %eax
	movl	%eax, -100(%rbp)
	pushq	%rdi
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
	call	boo_foo
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$32, %rsp # raising the stack pointer.
	movl	%esi, %ebx
	# Restoring current return value to temporary location after function call.
	movl	-72(%rbp), %esi
	movl	%ebx, -12(%rbp)
	movl	-12(%rbp), %ebx
	movl	%esi, -64(%rbp)
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf

	movl	-64(%rbp), %esi
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
