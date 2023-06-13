#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Event {
public:
    int eventId;
    string name;
    int availableTickets;
    string date;
    string time;
    string venue;
    double ticketPrice; // Penambahan atribut harga tiket

    Event(int eventId, string eventName, int availableTickets, string date, string time, string venue, double ticketPrice) {
        this->eventId = eventId;
        name = eventName;
        this->availableTickets = availableTickets;
        this->date = date;
        this->time = time;
        this->venue = venue;
        this->ticketPrice = ticketPrice;
    }
};

class User {
public:
    string username;
    string password;

    User(string username, string password) {
        this->username = username;
        this->password = password;
    }
};

class Ticket {
public:
    string eventName;
    string username;
    int quantity;

    Ticket(string eventName, string username, int quantity) {
        this->eventName = eventName;
        this->username = username;
        this->quantity = quantity;
    }
};

class Booking {
public:
    vector<Ticket> tickets;
    double totalPrice;

    void addTicket(Ticket ticket) {
        tickets.push_back(ticket);
    }

    void calculateTotalPrice(Event* event) {
        totalPrice = event->ticketPrice * tickets.size();
    }

    void displayReceipt(double paymentAmount) {
        double Harga = totalPrice * tickets[0].quantity;
        cout << "Kuitansi Pemesanan: " << endl;
        cout << "----------------------------------" << endl;
        for (const auto& ticket : tickets) {
            cout << "Event: " << ticket.eventName << endl;
            cout << "Jumlah Tiket: " << ticket.quantity << endl;
        }
        cout << "Total Harga: " << Harga  << endl;
        cout << "Total Pembayaran: " << paymentAmount << endl;
        if (paymentAmount > Harga) {
            double change = paymentAmount - Harga;
            cout << "Kembalian: " << change << endl;
        } else {
            cout << "Tidak ada kembalian." << endl;
        }
        cout << "----------------------------------" << endl;
    }
};

class BookingSystem {
public:
    vector<Event> events;
    vector<User> users;
    vector<Booking> bookings;

    void addEvent(Event event) {
        events.push_back(event);
    }

    void registerUser(User user) {
        users.push_back(user);
    }

    User* login(string username, string password) {
        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                return &user;
            }
        }
        return nullptr;
    }

    Event* findEventByNumber(int eventNumber) {
        if (eventNumber > 0 && eventNumber <= events.size()) {
            return &events[eventNumber - 1];
        }
        return nullptr;
    }

    bool bookTicket(User* user, Event* event, int quantity, double paymentAmount) {
        double totalPrice = event->ticketPrice * quantity;
        if (event->availableTickets >= quantity && paymentAmount >= totalPrice) {
            Ticket ticket(event->name, user->username, quantity);
            event->availableTickets -= quantity;
            Booking booking;
            booking.addTicket(ticket);
            booking.calculateTotalPrice(event);
            bookings.push_back(booking);

            double change = paymentAmount - totalPrice;
            if (change > 0) {
                cout << "Kembalian: " << change << endl;
            }
            return true;
        }
        return false;
    }

    void showEventDetails(Event* event) {
        cout << "Detail Event: " << endl;
        cout << "Event ID: " << event->eventId << endl;
        cout << "Nama Event: " << event->name << endl;
        cout << "Tanggal: " << event->date << endl;
        cout << "Waktu: " << event->time << endl;
        cout << "Tempat: " << event->venue << endl;
        cout << "Tiket Tersedia: " << event->availableTickets << endl;
        cout << "Harga Tiket: $ " << event->ticketPrice << endl;
    }
};

int main() {
    BookingSystem bookingSystem;

    // Menambahkan contoh event
    Event event1(1, "Konser Coldplay", 100, "2023-06-10", "19:00", "Venue A", 200.0);
    Event event2(2, "Konser Dewa", 100, "2023-06-15", "09:00", "Venue B", 150.0);
    Event event3(3, "Konser One OK Rock", 100, "2023-09-30", "19:00", "Venue C", 175.0);
    bookingSystem.addEvent(event1);
    bookingSystem.addEvent(event2);
    bookingSystem.addEvent(event3);

    // Mendaftarkan pengguna
    User user1("azka", "azka");
    User user2("user", "user");
    User user3("rangga", "rangga");
    User user4("afrizal", "afrizal");

    bookingSystem.registerUser(user1);
    bookingSystem.registerUser(user2);
    bookingSystem.registerUser(user3);
    bookingSystem.registerUser(user4);

    // Login pengguna
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    User* loggedInUser = bookingSystem.login(username, password);

    if (loggedInUser == nullptr) {
        cout << "Login gagal. Silakan coba lagi." << endl;
        return 0;
    }

    bool buyTicket = true;
    while (buyTicket) {
    	system("CLS");
        // Menampilkan pilihan event
        cout << "Daftar event: " << endl;
        for (int i = 0; i < bookingSystem.events.size(); i++) {
            cout << i + 1 << ". " << bookingSystem.events[i].name << endl;
        }
        int eventNumber;
        cout << "Masukkan nomor event yang ingin dilihat detailnya: ";
        cin >> eventNumber;
        Event* selectedEvent = bookingSystem.findEventByNumber(eventNumber);

        if (selectedEvent == nullptr) {
            cout << "Event tidak ditemukan." << endl;
            continue;
        }

        // Menampilkan detail event
        bookingSystem.showEventDetails(selectedEvent);

        // Memilih untuk membeli tiket atau tidak
        char choice;
        cout << "Apakah Anda ingin membeli tiket untuk event ini? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int quantity;
            cout << "Masukkan jumlah tiket yang ingin dibeli: ";
            cin >> quantity;
            double paymentAmount;
            cout << "Masukkan jumlah pembayaran: ";
            cin >> paymentAmount;
            bool success = bookingSystem.bookTicket(loggedInUser, selectedEvent, quantity, paymentAmount);
            if (success) {
                cout << "Tiket berhasil dibeli!" << endl;
                Booking& booking = bookingSystem.bookings.back();
                booking.displayReceipt(paymentAmount);
            } else {
                cout << "Tiket tidak tersedia atau pembayaran kurang." << endl;
            }
        }

        // Menanyakan apakah ingin membeli tiket event lain atau tidak
        cout << "Apakah Anda ingin membeli tiket event lain? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            buyTicket = false;
        }
    }

    return 0;
}
