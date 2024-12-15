#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan informasi lagu
struct Song {
    char title[100];
    char artist[100];
    int duration; // dalam detik
    struct Song *next;
};

// Struktur untuk Queue
struct Queue {
    struct Song *front;
    struct Song *rear;
    int size;
};

// Inisialisasi Queue
void initQueue(struct Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Fungsi untuk menambah lagu ke playlist
void enqueue(struct Queue *q, char *title, char *artist, int duration) {
    struct Song *newSong = (struct Song *)malloc(sizeof(struct Song));
    if (newSong == NULL) {
        printf("\nGagal menambahkan lagu karena memori tidak cukup!\n");
        return;
    }

    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;

    if (q->size == 0) {
        newSong->next = newSong; // pointed to itself for circular
        q->front = newSong;
        q->rear = newSong;
    } else {
        newSong->next = q->front;
        q->rear->next = newSong;
        q->rear = newSong;
    }
    q->size++;
    printf("\nLagu '%s' telah ditambahkan ke playlist!\n", title);
}

// Fungsi untuk memutar lagu berikutnya
void playNext(struct Queue *q) {
    if (q->size == 0) {
        printf("\nPlaylist kosong!\n");
        return;
    }

    printf("\nMemutar lagu: %s\n", q->front->title);
    printf("Artis: %s\n", q->front->artist);
    printf("Durasi: %d detik\n", q->front->duration);

    // Rotate the queue
    q->rear = q->front;
    q->front = q->front->next;
}

// Fungsi untuk menampilkan seluruh playlist
void displayPlaylist(struct Queue *q) {
    if (q->size == 0) {
        printf("\nPlaylist kosong!\n");
        return;
    }

    printf("\n=== Daftar Playlist ===\n");
    struct Song *current = q->front;
    int count = 1;

    do {
        printf("\n%d. Judul: %s", count, current->title);
        printf("\n   Artis: %s", current->artist);
        printf("\n   Durasi: %d detik", current->duration);
        current = current->next;
        count++;
    } while (current != q->front);

    printf("\n\nTotal lagu: %d\n", q->size);
}

// Fungsi untuk menghapus lagu dari playlist
void dequeue(struct Queue *q) {
    if (q->size == 0) {
        printf("\nPlaylist kosong!\n");
        return;
    }

    struct Song *temp = q->front;
    printf("\nMenghapus lagu '%s' dari playlist\n", temp->title);

    if (q->size == 1) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
        q->rear->next = q->front;
    }

    free(temp);
    q->size--;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    struct Queue playlist;
    initQueue(&playlist);
    int choice;
    char title[100], artist[100];
    int duration;

    while (1) {
        clearScreen();
        printf("\n================== BY KELOMPOK 9 | 2024 ================\n");
        printf("\n1. MUHAMMAD BAGUS SATRIO AJI 23081010258              |\n");
        printf("\n2. AKHMAD AZRUL ARSYADHANY   23081010281              |\n");
        printf("\n3. MUCHAMAD AKBAR DARMAWAN   23081010289              |\n");
        printf("\n4. ARGANTA BISMA PRATAMA     23081010291              |\n");
        printf("\n5. MUHAMMAD TRIAJI SUPANDI   23081010307              |\n");
        printf("\n================= PLAYLIST MUSIC =======================\n");

        printf("1. Tambah Lagu                                         |\n");
        printf("2. Putar Lagu Berikutnya                               |\n");
        printf("3. Tampilkan Playlist                                  |\n");
        printf("4. Hapus Lagu                                          |\n");
        printf("5. Keluar                                              |\n");
        printf("Masukkan Pilihan Anda:                                 |");

        printf("\n========================================================\n");

        if (scanf("%d", &choice) != 1) {
            printf("\nInput tidak valid! Masukkan angka.\n");
            while (getchar() != '\n'); // Membersihkan buffer
            continue;
        }

        getchar(); // Membersihkan newline di buffer

        switch (choice) {
            case 1:
                clearScreen();
                printf("\nMasukkan judul lagu: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;

                printf("Masukkan nama artis: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;

                printf("Masukkan durasi (detik): ");
                if (scanf("%d", &duration) != 1) {
                    printf("\nInput tidak valid untuk durasi!\n");
                    while (getchar() != '\n'); // Membersihkan buffer
                    continue;
                }

                enqueue(&playlist, title, artist, duration);
                break;

            case 2:
                clearScreen();
                playNext(&playlist);
                break;

            case 3:
                clearScreen();
                displayPlaylist(&playlist);
                break;

            case 4:
                clearScreen();
                dequeue(&playlist);
                break;

            case 5:
                clearScreen();
                printf("\nTerima kasih telah menggunakan program playlist musik!\n");
                exit(0);

            default:
                clearScreen();
                printf("\nPilihan tidak valid!\n");
        }

        printf("\nTekan ENTER untuk melanjutkan...");
        getchar();
    }

    return 0;
}
