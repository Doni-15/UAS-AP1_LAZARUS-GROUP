#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Deklarasi fungsi
void header();
void displayBoard();
void generatedBoard();
void guess(int baris_input, int kolom_input);
void gotoxy(int x, int y);
void poin(int jlh_poin);

// Konstanta ukuran papan dan jumlah bom
const int baris = 4;
const int kolom = 5;
const int bom = 2;
const int kotak_aman = (baris * kolom) - bom;

// Variabel global
char board[baris][kolom];
int data_isi[baris][kolom];
bool reveled[baris][kolom];
bool selesai = true;
int total_dibuka = 0;

int main() {
    system("cls");
    //srand(time(0)); // 1 2 & 2 0
    
    gotoxy(0, 6); 
    generatedBoard();  
    displayBoard();   
    
    int baris_input, kolom_input;
    while(selesai == true){
        gotoxy(0, 0); header();
        gotoxy(0, 4); cout << "Masukkan baris dan kolom (spasi): "; cin >> baris_input >> kolom_input;
        gotoxy(34, 4); cout << "                               ";
        
        guess(baris_input, kolom_input);
        displayBoard();

        poin(total_dibuka);
        Sleep(100); 
    }
    gotoxy(0, 18); system("pause");
}

// fungsi menampilkan header game
void header() {
    string n(60, '=');
    string n2(57, ' ');
    cout << n << " LOTRE GOSOK DIGITAL " << n << "\n\n";
    cout << n2 << "WELCOME TO E-LOTTERY GOSOK" << "\n\n";
}

// fungsi tampilkan papan ke layar
void displayBoard() {
    string isi = " ", enter = "\n\n";
    string spasi = "   ";

    for (int j = 0; j < kolom; j++) {
        isi += spasi + to_string(j);
    }
    isi += enter;

    for (int i = 0; i < baris; i++) {
        isi += to_string(i) + spasi;
        for (int j = 0; j < kolom; j++) {
            isi += board[i][j];
            isi += spasi;
        }
        isi += enter;
    }
    gotoxy(0, 7); cout << isi;
}

// fungsi acak posisi bom dan reset papan
void generatedBoard() {
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            data_isi[i][j] = 0;
            board[i][j] = '*';
            reveled[i][j] = false;
        }
    }

    int jumlah_bom = 0;
    while (jumlah_bom < bom) {
        int i = rand() % baris;
        int j = rand() % kolom;

        if (data_isi[i][j] == 0) {
            data_isi[i][j] = 1; 
            jumlah_bom++;
        }
    }
}

// fungsi proses tebakan pengguna dari inputannya
void guess(int baris_input, int kolom_input) {
    string status;

    if (baris_input < 0 || kolom_input < 0 || baris_input >= baris || kolom_input >= kolom) {
        status = "Posisi tidak valid! Di luar kotak.";
        Beep(1000, 500);
        gotoxy(0, 5); cout << status;
    }
    else if (reveled[baris_input][kolom_input]) {
        status = "Kotak ini sudah dibuka.";
        Beep(1000, 500);
        gotoxy(0, 5); cout << status;
    }
    else if (data_isi[baris_input][kolom_input] == 1) {
        board[baris_input][kolom_input] = 'X';
        Beep(1000, 500);
        status = "BOOM! Kamu kena bom. Game Over!";
        selesai = false;
    } 
    else {
        reveled[baris_input][kolom_input] = true;
        board[baris_input][kolom_input] = 'O';
        total_dibuka++;
        poin(total_dibuka);
        
        if (total_dibuka == kotak_aman) {
            gotoxy(0, 18); cout << "Selamat! Kamu berhasil membuka semua kotak aman!\n";
            selesai = true;
        } else {
            status = "Aman! Teruskan...";
            Beep(500, 100);
        }
    }
    gotoxy(0, 5); cout << status << "                         ";
}

// Fungsi tampilkan poin
void poin(int jlh_poin){
    gotoxy(0, 17); cout << "Point : " << jlh_poin << endl;
}

// Fungsi gotoxy
void gotoxy(int x, int y){
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}