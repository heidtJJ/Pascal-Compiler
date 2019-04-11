	.text
	.globl	main
	.type	main, @function
moo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp # lowering the stack pointer.
	leave
	ret
.moo:
	.size	moo, .-moo
	.globl	main
	.type	main, @function
boo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp # lowering the stack pointer.
	leave
	ret
.boo:
	.size	boo, .-boo
	.globl	main
	.type	main, @function
foo:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$4, %rsp # lowering the stack pointer.
	leave
	ret
.foo:
	.size	foo, .-foo
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$28, %rsp # lowering the stack pointer.
	leave
	ret
.main:
	.size	main, .-main
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	call	main
	movl	$0, %eax
	leave
	ret
.main:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits
