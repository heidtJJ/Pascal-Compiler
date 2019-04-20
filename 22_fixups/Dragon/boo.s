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
boo_foo_coo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	16(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	20(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$12, %ebx
	movl	%ebx, %esi
	leave
	ret
.boo_foo_coo:
	.size	boo_foo_coo, .-boo_foo_coo
	.globl	main
	.type	main, @function
boo_foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
# Putting regs on the stack.
	pushq	%rdi
	pushq	%rcx
	pushq	%rbx
# Done putting regs on the stack.
	movl	$1, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$2, %ebx
	movl	%ebx, %eax
	movl	%eax, -36(%rbp)
	movl	$0, %esi
	call	boo_foo_coo
# Restoring regs on the stack.
	movq	0(%rsp), %rbx
	movq	4(%rsp), %rcx
	movq	8(%rsp), %rdi
	addq	$12, %rsp
# Done restoring regs on the stack.
	movl	%esi, %ebx
	movl	%ebx, -12(%rbp)
	movl	-12(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
