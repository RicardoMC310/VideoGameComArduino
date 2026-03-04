.org 0x0000
.extern loop_kernel
.extern setup_kernel

_start:
    rcall setup_kernel

_loop:
    rcall loop_kernel

    rjmp _loop