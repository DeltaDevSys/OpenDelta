#!/usr/bin/env python3

import subprocess
import sys

def install_packages():
    packages = [
        'clang',   
        'nasm',    
        'lua',     
    ]

    if subprocess.run(['id', '-u'], capture_output=True, text=True).stdout.strip() != '0':
        print("Этот скрипт необходимо запускать с правами суперпользователя (sudo)")
        sys.exit(1)

    print("Обновление базы данных пакетов и синхронизация с репозиторием...")
    distro = int(input("choose your distro or distro-base: \n"))
    print("1.arch, arch-based;  2.debian, debian-based.")
    if distro == 1:
        try:
            subprocess.run(['pacman', '-Syu'], check=True)
        except subprocess.CalledProcessError:
            print("Ошибка при обновлении базы данных пакетов")
            sys.exit(1)
    elif distro == 2:
        try:
            subprocess.run(['apt', 'update'], check=True)
        except subprocess.CalledProcessError:
            print("Ошибка при обновлении базы данных пакетов")
            sys.exit(1)
    else:
        print("выберите только между перечисленные")

    print("Установка пакетов...")
    base_distro = int(input("выберите ваш дистрибутив или дистро которые идут на основе перечисленных ниже: "))
    print("1.arch and arch-based;  2.debian debian-based;")
    if base_distro == 1:
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

    elif base_distro == 2:
        try:
            result = subprocess.run(['apt', 'install'] + packages,
                                    check=True,
                                    capture_output=True,
                                    text=True)
            print("Все пакеты успешно установлены")
            for package_2 in packages:
                    print(f"- {packages}")
        except subprocess.CalledProcessError as e:
            print("ошибка при установки пакетов: ")
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
