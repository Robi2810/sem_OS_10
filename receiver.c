#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int received_bit = -1;
volatile int received_number = 0;
volatile int bits_received = 0;

// Обработчик SIGUSR1 - устанавливает received_bit в 0
void sigusr1_handler(int signum) {
    received_bit = 0;
}

// Обработчик SIGUSR2 - устанавливает received_bit в 1
void sigusr2_handler(int signum) {
    received_bit = 1;
}

int main() {
    struct sigaction sa_usr1, sa_usr2;

    sa_usr1.sa_handler = sigusr1_handler;
    sa_usr2.sa_handler = sigusr2_handler;
    sigemptyset(&sa_usr1.sa_mask);
    sigemptyset(&sa_usr2.sa_mask);
    sa_usr1.sa_flags = 0;
    sa_usr2.sa_flags = 0;

    // Установка обработчиков сигналов
    if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1 || sigaction(SIGUSR2, &sa_usr2, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for the sender...\n");

    // Ожидание побитового приема числа
    while (bits_received < 32) {
        pause();
        // Обновление принятого числа
        received_number |= (received_bit << bits_received);
        bits_received++;
    }

    printf("Received number: %d\n", received_number);

    return 0;
}
