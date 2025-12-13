#![no-std]
#![no-main]
#![feature(naked_functions)]
#![feature(asm_const)]

mod arch;          
mod memory;         
mod process;    
mod syscall;        
mod interrupt;      

use core::panic::PanicInfo;

struct Process {
    pid: u32,
    state: ProcessState,
    memory_map: MemoryMap,
}

enum ProcessState {
    Running,
    Sleeping,
    Stopped,
    Zombie,
}

struct Kernel {
    processes: Vec<Process>,
    current_pid: u32,
}

impl Kernel {
    fn new() -> Self {
        Kernel {
            processes: Vec::new(),
            current_pid: 0,
        }
    }

    fn create_process(&mut self) -> u32 {
        self.current_pid += 1;
        let new_process = Process {
            pid: self.current_pid,
            state: ProcessState::Running,
            memory_map: MemoryMap::new(),
        };
        self.processes.push(new_process);
        self.current_pid
    }

    fn run(&mut self) -> ! {
        loop {
            self.schedule();
            
            self.handle_interrupts();
        }
    }

    fn schedule(&mut self) {
        for process in &mut self.processes {
            match process.state {
                ProcessState::Running => {
                }
                ProcessState::Sleeping => {
                }
                _ => {}
            }
        }
    }

    fn handle_interrupts(&mut self) {
    }
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    let mut kernel = Kernel::new();
    kernel.run()
}
