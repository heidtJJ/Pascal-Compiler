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
	movq	%rbp, %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$1, %ebx
	movq	%rbp, %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movl	%ebx, -8(%rax)
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
	movl	$1, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$0, %esi
	call	boo_foo_coo
	movq	%rbp, %rax
	movq	(%rax), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$2, %ebx
	movq	%rbp, %rax
	movq	(%rax), %rax
	movl	%ebx, -8(%rax)
	leave
	ret
.boo_foo:
	.size	boo_foo, .-boo_foo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp # lowering the stack pointer.
	movl	$22, %ebx
	movl	%ebx, -8(%rbp)
	movl	$1, %ebx
	movl	%ebx, %eax
	movl	%eax, -32(%rbp)
	movl	$0, %esi
	call	boo_foo
	movl	-8(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
	movl	$3, %ebx
	movl	%ebx, -8(%rbp)
	movl	-8(%rbp), %ebx
	movl	%ebx, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf
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
