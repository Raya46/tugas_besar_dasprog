#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 50
#define MAX_THEATERS 10
#define MAX_SEATS 26
#define MAX_USERS 100
#define MAX_BOOKINGS 500

typedef struct
{
    int id;
    char title[100];
    char genre[50];
    float duration;
    int ageRating;
    int totalTickets;
    int availableTickets;
    char showtimes[7][5]; // Jadwal tayang per hari (max 5 slot per hari)
} Movie;

typedef struct
{
    int id;
    char name[50];
    int totalSeats;
    char availableSeats[MAX_SEATS];
} Theater;

typedef struct
{
    int id;
    char username[50];
    char password[50];
    char email[100];
} User;

typedef struct
{
    int id;
    int movieId;
    int theaterId;
    int userId;
    char seatNumber;
    float ticketPrice;
    char bookingDate[20];
} Booking;

Movie movies[MAX_MOVIES];
Theater theaters[MAX_THEATERS];
User users[MAX_USERS];
Booking bookings[MAX_BOOKINGS];

int movieCount = 0;
int theaterCount = 0;
int userCount = 0;
int bookingCount = 0;

// Fungsi Utilitas
void initializeSeats(Theater *theater)
{
    for (int i = 0; i < MAX_SEATS; i++)
    {
        theater->availableSeats[i] = 'A' + i;
    }
}

int binarySearchMovies(char *title)
{
    int left = 0, right = movieCount - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int cmp = strcmp(movies[mid].title, title);
        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

void sortMoviesByTitle()
{
    for (int i = 0; i < movieCount - 1; i++)
    {
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if (strcmp(movies[j].title, movies[j + 1].title) > 0)
            {
                Movie temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
}

int findTheater(int id)
{
    for (int i = 0; i < theaterCount; i++)
    {
        if (theaters[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int findUser(char *username)
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return i;
        }
    }
    return -1;
}

int findBooking(int id)
{
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// Fungsi Manajemen Film
void addMovie()
{
    if (movieCount >= MAX_MOVIES)
    {
        printf("Kapasitas film penuh!\n");
        return;
    }

    Movie newMovie;
    printf("ID Film: ");
    scanf("%d", &newMovie.id);
    printf("Judul Film: ");
    scanf(" %[^\n]", newMovie.title);
    printf("Genre: ");
    scanf(" %[^\n]", newMovie.genre);
    printf("Durasi (jam): ");
    scanf("%f", &newMovie.duration);
    printf("Batas Usia: ");
    scanf("%d", &newMovie.ageRating);
    printf("Total Tiket: ");
    scanf("%d", &newMovie.totalTickets);
    newMovie.availableTickets = newMovie.totalTickets;
    memset(newMovie.showtimes, 0, sizeof(newMovie.showtimes));

    movies[movieCount++] = newMovie;
    printf("Film berhasil ditambahkan!\n");
}

void editMovie()
{
    char title[100];
    printf("Masukkan judul film yang ingin diubah: ");
    scanf(" %[^\n]", title);

    int index = binarySearchMovies(title);
    if (index == -1)
    {
        printf("Film tidak ditemukan.\n");
        return;
    }

    printf("Judul Baru: ");
    scanf(" %[^\n]", movies[index].title);
    printf("Genre Baru: ");
    scanf(" %[^\n]", movies[index].genre);
    printf("Durasi Baru (jam): ");
    scanf("%f", &movies[index].duration);
    printf("Batas Usia Baru: ");
    scanf("%d", &movies[index].ageRating);
    printf("Total Tiket Baru: ");
    scanf("%d", &movies[index].totalTickets);
    movies[index].availableTickets = movies[index].totalTickets;

    printf("Film berhasil diperbarui!\n");
}

void deleteMovie()
{
    char title[100];
    printf("Masukkan judul film yang ingin dihapus: ");
    scanf(" %[^\n]", title);

    int index = binarySearchMovies(title);
    if (index == -1)
    {
        printf("Film tidak ditemukan.\n");
        return;
    }

    for (int i = index; i < movieCount - 1; i++)
    {
        movies[i] = movies[i + 1];
    }
    movieCount--;
    printf("Film berhasil dihapus.\n");
}

void displayMovies()
{
    sortMoviesByTitle();
    printf("\n=== Daftar Film ===\n");
    for (int i = 0; i < movieCount; i++)
    {
        printf("ID: %d | Judul: %s | Genre: %s | Durasi: %.1f jam | Batas Usia: %d | Tiket Tersedia: %d\n",
               movies[i].id, movies[i].title, movies[i].genre,
               movies[i].duration, movies[i].ageRating, movies[i].availableTickets);
    }
}

// Fungsi Manajemen Teater
void addTheater()
{
    if (theaterCount >= MAX_THEATERS)
    {
        printf("Kapasitas teater penuh!\n");
        return;
    }

    Theater newTheater;
    printf("ID Teater: ");
    scanf("%d", &newTheater.id);
    printf("Nama Teater: ");
    scanf(" %[^\n]", newTheater.name);
    printf("Total Kursi: ");
    scanf("%d", &newTheater.totalSeats);

    initializeSeats(&newTheater);
    theaters[theaterCount++] = newTheater;
    printf("Teater berhasil ditambahkan!\n");
}

// Fungsi Pemesanan Tiket
void displayAvailableSeats(int theaterId)
{
    int index = findTheater(theaterId);
    if (index == -1)
    {
        printf("Teater tidak ditemukan.\n");
        return;
    }

    printf("\nKursi Tersedia: ");
    for (int i = 0; i < MAX_SEATS; i++)
    {
        if (theaters[index].availableSeats[i] != '-')
        {
            printf("%c ", theaters[index].availableSeats[i]);
        }
    }
    printf("\n");
}

void bookTicket()
{
    char movieTitle[100], username[50], seatChoice;
    int theaterId;

    printf("Masukkan judul film: ");
    scanf(" %[^\n]", movieTitle);
    int movieIndex = binarySearchMovies(movieTitle);
    if (movieIndex == -1)
    {
        printf("Film tidak ditemukan.\n");
        return;
    }

    printf("Masukkan ID teater: ");
    scanf("%d", &theaterId);
    int theaterIndex = findTheater(theaterId);
    if (theaterIndex == -1)
    {
        printf("Teater tidak ditemukan.\n");
        return;
    }

    displayAvailableSeats(theaterId);
    printf("Pilih kursi: ");
    scanf(" %c", &seatChoice);

    printf("Masukkan username: ");
    scanf(" %[^\n]", username);
    int userIndex = findUser(username);
    if (userIndex == -1)
    {
        printf("Pengguna tidak ditemukan.\n");
        return;
    }

    // Validasi dan proses pemesanan
    // Implementasi lengkap akan mencakup pengecekan kursi,
    // pembuatan booking, dll.
}

void cancelTicket()
{
    int bookingId;
    printf("Masukkan ID tiket yang ingin dibatalkan: ");
    scanf("%d", &bookingId);

    int bookingIndex = findBooking(bookingId);
    if (bookingIndex == -1)
    {
        printf("Tiket tidak ditemukan.\n");
        return;
    }

    // Implementasi proses pembatalan tiket
}

void viewBookingHistory()
{
    char username[50];
    printf("Masukkan username: ");
    scanf(" %[^\n]", username);

    int userIndex = findUser(username);
    if (userIndex == -1)
    {
        printf("Pengguna tidak ditemukan.\n");
        return;
    }

    printf("\nRiwayat Pemesanan untuk %s:\n", username);
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].userId == users[userIndex].id)
        {
            printf("ID Tiket: %d | Film: %s | Teater: %d | Kursi: %c | Tanggal: %s\n",
                   bookings[i].id, movies[bookings[i].movieId].title,
                   theaters[bookings[i].theaterId].id, bookings[i].seatNumber,
                   bookings[i].bookingDate);
        }
    }
}

// Menu Admin
void adminMenu()
{
    int choice;
    do
    {
        printf("\n=== Menu Admin ===\n");
        printf("1. Tambah Film\n");
        printf("2. Edit Film\n");
        printf("3. Hapus Film\n");
        printf("4. Tampilkan Daftar Film\n");
        printf("5. Tambah Teater\n");
        printf("6. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMovie();
            break;
        case 2:
            editMovie();
            break;
        case 3:
            deleteMovie();
            break;
        case 4:
            displayMovies();
            break;
        case 5:
            addTheater();
            break;
        case 6:
            printf("Keluar dari menu admin.\n");
            return;
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (1);
}

// Menu Pengguna
void userMenu()
{
    int choice;
    do
    {
        printf("\n=== Menu Pengguna ===\n");
        printf("1. Lihat Daftar Film\n");
        printf("2. Pesan Tiket\n");
        printf("3. Batalkan Tiket\n");
        printf("4. Lihat Riwayat Pemesanan\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMovies();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            cancelTicket();
            break;
        case 4:
            viewBookingHistory();
            break;
        case 5:
            printf("Kembali ke menu utama.\n");
            return;
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (1);
}

// Menu Utama dan Fungsi Login
int login()
{
    char username[50], password[50];
    int choice;
    do
    {
        printf("\n=== Reservasi Bioskop ===\n");
        printf("1. Login Admin\n");
        printf("2. Login Pengguna\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Username Admin: ");
            scanf(" %[^\n]", username);
            printf("Password Admin: ");
            scanf(" %[^\n]", password);
            // Validasi login admin
            adminMenu();
            break;
        case 2:
            printf("Username: ");
            scanf(" %[^\n]", username);
            // Validasi login pengguna
            userMenu();
            break;
        case 3:
            printf("Keluar dari sistem.\n");
            return 0;
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (1);
}

int main()
{
    login();
    return 0;
}