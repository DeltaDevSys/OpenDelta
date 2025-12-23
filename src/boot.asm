section .data
    kernel_path db '/home/deltadev/open-delta/kernel/', 0
    kernel_path_len equ $ - kernel_path

    error_msg db '[ошибка]: ядро не найдено', 15
    error_msg_len equ $ - error_msg

    success_msg db '[инфо]: ядро успешно загружено', 15
    success_msg_len equ $ - success_msg

section .text
    global _start

_start:
    mov eax, 33     
    mov ebx, kernel_path
    mov ecx, 0      
    int 0x80

    test eax, eax
    jnz kernel_not_found

    mov eax, 11     
    mov ebx, kernel_path
    mov ecx, 0      
    mov edx, 0      
    int 0x80

    jmp exit_success

kernel_not_found:
    mov eax, 4      
    mov ebx, 2      
    mov ecx, error_msg
    mov edx, error_msg_len
    int 0x80

    mov eax, 1      
    mov ebx, 1      
    int 0x80

exit_success:
    mov eax, 4      
    mov ebx, 1      
    mov ecx, success_msg
    mov edx, success_msg_len
    int 0x80

    mov eax, 1      
    xor ebx, ebx    
    int 0x80

