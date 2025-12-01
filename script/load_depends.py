#!/usr/bin/env python3

import subprocess
import sys

def install_packages():
    packages = [
        'clang',   
        'gcc',     
        'nasm',    
        'lua',     
        'rustc',   
        'cargo'    
    ]

    if subprocess.run(['id', '-u'], capture_output=True, text=True).stdout.strip() != '0':
        print("Этот скрипт необходимо запускать с правами суперпользователя (sudo)")
        sys.exit(1)

    print("Обновление базы данных пакетов и синхронизация с репозиторием...")
    try:
        subprocess.run(['pacman', '-Syu'], check=True)
    except subprocess.CalledProcessError:
        print("Ошибка при обновлении базы данных пакетов")
        sys.exit(1)

    print("Установка пакетов...")
    try:
        result = subprocess.run(['pacman', '-S', '--noconfirm'] + packages, 
                                 check=True, 
                                 capture_output=True, 
                                 text=True)
        print("Все пакеты успешно установлены:")
        for package in packages:
            print(f"- {package}")
    except subprocess.CalledProcessError as e:
        print("Ошибка при установке пакетов:")
        print(e.stderr)
        sys.exit(1)

def main():
    try:
        install_packages()
    except Exception as e:
        print(f"Произошла непредвиденная ошибка: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
