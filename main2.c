#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 50
#define MAX_THEATERS 10
#define MAX_USERS 100
#define MAX_SEATS 26
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
} Movie;

typedef struct
{
    int id;
    char name[50];
    char availableSeats[MAX_SEATS];
} Theater;

typedef struct
{
    int id;
    char username[50];
    char password[50];
} User;

typedef struct
{
    int id;
    int movieId;
    int theaterId;
    int userId;
    char seatNumber;
    float ticketPrice;
} Booking;

Movie movies[MAX_MOVIES];
Theater theaters[MAX_THEATERS];
User users[MAX_USERS];
Booking bookings[MAX_BOOKINGS];

int movieCount = 0;
int theaterCount = 0;
int userCount = 0;
int bookingCount = 0;

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
        int compare = strcmp(movies[mid].title, title);
        if (compare == 0)
        {
            return mid;
        }
        else if (compare < 0)
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

void sortMoviesById()
{
    for (int i = 0; i < movieCount - 1; i++)
    {
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if (movies[j].id > movies[j + 1].id)
            {
                Movie id = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = id;
            }
        }
    }
}

void sortTheaterById()
{
    for (int i = 0; i < theaterCount - 1; i++)
    {
        for (int j = 0; j < theaterCount - i - 1; j++)
        {
            if (theaters[j].id > theaters[j + 1].id)
            {
                Theater id = theaters[j];
                theaters[j] = theaters[j + 1];
                theaters[j + 1] = id;
            }
        }
    }
}

void sortBookingById()
{
    for (int i = 0; i < bookingCount - 1; i++)
    {
        for (int j = 0; j < bookingCount - i - 1; j++)
        {
            if (bookings[j].id > bookings[j + 1].id)
            {
                Booking id = bookings[j];
                bookings[j] = bookings[j + 1];
                bookings[j + 1] = id;
            }
        }
    }
}

void sortUserById()
{
    for (int i = 0; i < userCount - 1; i++)
    {
        for (int j = 0; j < userCount - i - 1; j++)
        {
            if (users[j].id > users[j + 1].id)
            {
                User id = users[j];
                users[j] = users[j + 1];
                users[j + 1] = id;
            }
        }
    }
}

int findTheater(int id)
{
    int left = 0, right = theaterCount - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (theaters[mid].id == id)
        {
            return mid;
        }
        else if (theaters[mid].id < id)
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

int findBooking(int id)
{
    {
        int left = 0, right = bookingCount - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (bookings[mid].id == id)
            {
                return mid;
            }
            else if (bookings[mid].id < id)
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

    if (userCount < MAX_USERS)
    {
        User newUser;
        newUser.id = userCount;
        strcpy(newUser.username, username);
        strcpy(newUser.password, "");
        users[userCount++] = newUser;
        return userCount - 1;
    }
    else
    {
        printf("Kapasitas pengguna penuh!\n");
        return -1;
    }
}

void addMovie()
{
    if (movieCount >= MAX_MOVIES)
    {
        printf("Kapasitas film penuh\n");
        return;
    }
    Movie newMovie;
    printf("ID Film: ");
    scanf("%d", &newMovie.id);
    printf("Judul film: ");
    scanf(" %[^\n]", newMovie.title);
    printf("Genre: ");
    scanf(" %[^\n]", newMovie.genre);
    printf("Durasi (menit): ");
    scanf("%f", &newMovie.duration);
    printf("Batas usia: ");
    scanf("%d", &newMovie.ageRating);
    printf("Total tiket: ");
    scanf("%d", &newMovie.totalTickets);
    newMovie.availableTickets = newMovie.totalTickets;
    movies[movieCount++] = newMovie;
    printf("Film berhasil ditambahkan\n");
}

void editMovie()
{
    char title[100];
    printf("Masukkan judul film yang ingin diubah: ");
    scanf(" %[^\n]", title);

    int index = binarySearchMovies(title);
    if (index == -1)
    {
        printf("Film tidak ditemukan\n");
        return;
    }
    printf("Masukkan judul baru: ");
    scanf(" %[^\n]", movies[index].title);
    printf("Masukkan genre baru: ");
    scanf(" %[^\n]", movies[index].genre);
    printf("Masukkan durasi (menit): ");
    scanf("%f", &movies[index].duration);
    printf("Masukkan batas usia: ");
    scanf("%d", &movies[index].ageRating);
    printf("Masukkan total tiket: ");
    scanf("%d", &movies[index].totalTickets);
    movies[index].availableTickets = movies[index].totalTickets;

    printf("Film berhasil diperbarui\n");
}

void deleteMovie()
{
    char title[100];
    printf("Masukkan judul film yang ingin dihapus: ");
    scanf(" %[^\n]", title);
    int index = binarySearchMovies(title);
    if (index == -1)
    {
        printf("Film tidak ditemukan\n");
        return;
    }
    for (int i = index; i < movieCount - 1; i++)
    {
        movies[i] = movies[i + 1];
    }
    movieCount--;
    printf("Film berhasil dihapus\n");
}

void tableFormat(char type)
{
    if (type == 't')
    {
        printf("+-----+----------------------+-----------------+----------------------------+\n");
    }
    else if (type == 'm')
    {
        printf("+-----+----------------------+------------+--------+-------------+------------------+\n");
    }
}

void displayTheaters()
{
    printf("\n=== Daftar Theater ===\n");
    tableFormat('t');
    printf("| %-3s | %-20s | %-15s | %-26s |\n", "ID", "Nama", "Jumlah Kursi", "Kursi Tersedia");
    tableFormat('t');

    for (int i = 0; i < theaterCount; i++)
    {
        printf("| %-3d | %-20s | %-15d | %-20s |\n",
               theaters[i].id,
               theaters[i].name,
               MAX_SEATS,
               theaters[i].availableSeats);
    }

    tableFormat('t');
}

void displayMovies()
{
    sortMoviesById();
    printf("\n=== Daftar Film ===\n");
    tableFormat('m');
    printf("| %-3s | %-20s | %-10s | %-6s | %-11s | %-16s |\n",
           "ID", "Judul", "Genre", "Durasi", "Batas Usia", "Tiket Tersedia");
    tableFormat('m');

    for (int i = 0; i < movieCount; i++)
    {
        printf("| %-3d | %-20s | %-10s | %-6.1f | %-11d | %-16d |\n",
               movies[i].id,
               movies[i].title,
               movies[i].genre,
               movies[i].duration,
               movies[i].ageRating,
               movies[i].availableTickets);
    }

    tableFormat('m');
}

void addTheater()
{
    if (theaterCount >= MAX_THEATERS)
    {
        printf("Kapasistas theater penuh\n");
        return;
    }

    Theater newTheater;
    printf("ID Teater: ");
    scanf("%d", &newTheater.id);
    printf("Nama Teater: ");
    scanf(" %[^\n]", newTheater.name);

    initializeSeats(&newTheater);
    theaters[theaterCount++] = newTheater;
    printf("Theater berhasil ditambahkan\n");
}

void displayAvailableSeats(int theaterId)
{
    sortTheaterById();
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

void bookTicket(char *username)
{
    char movieTitle[100], seatChoice;
    int theaterId;

    displayMovies();
    printf("Masukkan judul film: ");
    scanf(" %[^\n]", movieTitle);
    int movieIndex = binarySearchMovies(movieTitle);
    if (movieIndex == -1)
    {
        printf("Film tidak ditemukan\n");
        return;
    }
    displayTheaters();
    printf("Masukkan ID theater: ");
    scanf("%d", &theaterId);
    sortTheaterById();
    int theaterIndex = findTheater(theaterId);
    if (theaterIndex == -1)
    {
        printf("Theater tidak ditemukan\n");
        return;
    }
    displayAvailableSeats(theaterId);
    printf("Pilih kursi: ");
    scanf(" %c", &seatChoice);
    sortUserById();
    int userIndex = findUser(username);
    if (userIndex == -1)
    {
        printf("User tidak ditemukan\n");
        return;
    }
    for (int i = 0; i < MAX_SEATS; i++)
    {
        if (theaters[theaterIndex].availableSeats[i] == seatChoice)
        {
            Booking newBooking;
            newBooking.id = bookingCount + 1;
            newBooking.movieId = movieIndex;
            newBooking.theaterId = theaterIndex;
            newBooking.userId = userIndex;
            newBooking.seatNumber = seatChoice;
            newBooking.ticketPrice = 30000.00;
            theaters[theaterIndex].availableSeats[i] = '-';
            movies[movieIndex].availableTickets--;
            bookings[bookingCount++] = newBooking;
            printf("Tiket berhasil dibooking!\n");
            printf("Detail Booking:\n");
            printf("Film: %s\n", movies[movieIndex].title);
            printf("Theater: %s\n", theaters[theaterIndex].name);
            printf("Kursi: %c\n", seatChoice);
            printf("Harga: Rp %.2f\n", newBooking.ticketPrice);
            return;
        }
        else
        {
            printf("Kursi tidak tersedia atau sudah dipesan.\n");
        }
    }
}

void displayBookingHistory(char *username)
{
    int userIndex = findUser(username);
    if (userIndex == -1)
    {
        printf("Pengguna tidak ditemukan.\n");
        return;
    }

    printf("\nRiwayat Pemesanan untuk %s:\n", username);

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].userId == userIndex)
        {
            printf("| ID Tiket: %d | Film: %s | Theater: %s | Kursi: %c | Harga: %.2f |\n",
                   bookings[i].id,
                   movies[bookings[i].movieId].title,
                   theaters[bookings[i].theaterId].name,
                   bookings[i].seatNumber,
                   bookings[i].ticketPrice);
        }
    }
}

void cancelTicket(char *username)
{
    int bookingId;
    displayBookingHistory(username);
    printf("Masukkan ID tiket yang ingin dibatalkan: ");
    scanf("%d", &bookingId);
    sortBookingById();
    int bookingIndex = findBooking(bookingId);
    if (bookingIndex == -1)
    {
        printf("Tiket tidak ditemukan.\n");
        return;
    }

    int theaterId = bookings[bookingIndex].theaterId;
    char seatNumber = bookings[bookingIndex].seatNumber;
    int movieIndex = bookings[bookingIndex].movieId;

    for (int i = 0; i < MAX_SEATS; i++)
    {
        if (theaters[theaterId].availableSeats[i] == '-')
        {
            theaters[theaterId].availableSeats[i] = seatNumber;
            break;
        }
    }

    movies[movieIndex].availableTickets++;

    for (int i = bookingIndex; i < bookingCount - 1; i++)
    {
        bookings[i] = bookings[i + 1];
    }
    bookingCount--;

    printf("Tiket dengan ID %d berhasil dibatalkan.\n", bookingId);
}

void adminMenu()
{
    int choice;
    do
    {
        printf("\n=== Selamat Datang Admin ===\n");
        printf("1. Tambah Film\n");
        printf("2. Edit Film\n");
        printf("3. Hapus Film\n");
        printf("4. Tampilkan Daftar Film\n");
        printf("5. Tampilkan Daftar Theater\n");
        printf("6. Tambah Teater\n");
        printf("7. Keluar\n");
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
            displayTheaters();
            break;
        case 6:
            addTheater();
            break;
        case 7:
            printf("Keluar dari menu admin.\n");
            return;
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (1);
}

void userMenu(char *username)
{
    int choice;
    do
    {
        printf("\n=== Selamat Datang %s di Bioskop 212 ===\n", username);
        printf("1. Lihat Daftar Film\n");
        printf("2. Pesan Tiket\n");
        printf("3. Batalkan Tiket\n");
        printf("4. Lihat Riwayat Pemesanan\n");
        printf("5. Lihat Daftar Theater\n");
        printf("6. Kembali ke Menu Utama\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayMovies();
            break;
        case 2:
            bookTicket(username);
            break;
        case 3:
            cancelTicket(username);
            break;
        case 4:
            displayBookingHistory(username);
            break;
        case 5:
            displayTheaters();
            break;
        case 6:
            printf("Keluar dari menu user.");
            return;

        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (1);
}

int login()
{
    char username[50], password[50];
    int choice;
    do
    {
        printf("\n=== Selamat Datang di Bioskop 212 ===\n");
        printf("1. Login Admin\n");
        printf("2. Login Penonton\n");
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
            if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
            {
                adminMenu();
            }
            else
            {
                printf("username atau password salah");
            }
            break;
        case 2:
            printf("Username: ");
            scanf(" %[^\n]", username);
            userMenu(username);
            break;
        case 3:
            printf("Exit.");
            return 0;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (1);
}

int main()
{
    login();
    return 0;
}