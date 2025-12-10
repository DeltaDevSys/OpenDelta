#![no_std]      
#![no_main]     

#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    unsafe {
        syscall3(1, 1, message.as_ptr() as usize, message.len());
        syscall3(60, 0, 0, 0);  
    }
}

#[inline(always)]
unsafe fn syscall3(nr: usize, a1: usize, a2: usize, a3: usize) -> usize {
    let ret: usize;
    core::arch::asm!(
        "syscall",
        inlout("rax") nr => ret,
        in("rdi") a1,
        in("rsi") a2,
        in("rdx") a3,
        options(nostack)
    );
    ret
}

static message: &[u8] = b"Hello OpenDelta\n";
