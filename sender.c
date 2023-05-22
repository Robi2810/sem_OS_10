#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Функция отправки одного бита
void send_bit(int receiver_pid, int bit) {
    if (bit == 0) {
        // Отправка SIGUSR1 для бита 0
        kill(receiver_pid, SIGUSR1);
    } else {
        // Отправка SIGUSR2 для бита 1
        kill(receiver_pid, SIGUSR2);
    }
    usleep(100000);
}

int main() {
    int receiver_pid, number;

    // Вывод PID передатчика
    printf("Sender PID: %d\n", getpid());
    printf("Enter the receiver PID: ");
    // Ввод PID приемника
    scanf("%d", &receiver_pid);

    // Ввод числа для отправки
    printf("Enter the number to send: ");
    scanf("%d", &number);

    // Побитовая отправка числа
    for (int i = 0; i < 32; ++i) {
        send_bit(receiver_pid, (number >> i) & 1);
    }

    return 0;
}
