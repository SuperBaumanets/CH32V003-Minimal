#!/bin/bash

PORT="$1"
SPEED="$2"

if [ ! -e "$PORT" ]; then
    echo "Порт $PORT не существует."
    exit 1
fi

if [ ! -w "$PORT" ]; then
    echo "Нет прав на запись к порту $PORT."
    exit 1
fi

stty -F "$PORT" -g > "/tmp/stty_backup_$$" 2>/dev/null

stty -F "$PORT" raw -echo -echoe -echok -icanon -isig -ixon opost -onlcr -icrnl min 1 time 0 speed "$SPEED"

if [ $? -eq 0 ]; then
    echo "Текущие настройки порта $PORT:"
    stty -F "$PORT" -a
else
    echo "Ошибка при настройке порта."
    exit 1
fi