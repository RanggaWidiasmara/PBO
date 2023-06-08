#include <iostream>
#include <vector>

using namespace std;

class Event {
public:
    int eventId;
    string name;
    int availableTickets;
    string date;
    string time;
    string venue;

    Event(int eventId, string eventName, int availableTickets, string date, string time, string venue) {
        this->eventId = eventId;
        name = eventName;
        this->availableTickets = availableTickets;
        this->date = date;
        this->time = time;
        this->venue = venue;
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

    void addTicket(Ticket ticket) {
        tickets.push_back(ticket);
    }

    void displayReceipt() {
        cout << "Kuitansi Pemesanan: " << endl;
        cout << "----------------------------------" << endl;
        for (const auto& ticket : tickets) {
            cout << "Event: " << ticket.eventName << endl;
            cout << "Jumlah Tiket: " << ticket.quantity << endl;
            cout << "----------------------------------" << endl;
        }
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

    bool bookTicket(User* user, Event* event, int quantity) {
        if (event->availableTickets >= quantity) {
            Ticket ticket(event->name, user->username, quantity);
            event->availableTickets -= quantity;
            Booking booking;
            booking.addTicket(ticket);
            bookings.push_back(booking);
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
    }
};

int main() {
    BookingSystem bookingSystem;

    // Menambahkan contoh event
    Event event1(1, "Konser Coldplay", 100, "2023-06-10", "19:00", "Venue A");
    Event event2(2, "Konser Dewa", 100, "2023-06-15", "09:00", "Venue B");
    bookingSystem.addEvent(event1);
    bookingSystem.addEvent(event2);

    // Mendaftarkan pengguna
    User user1("azka", "azka");
    User user2("user", "user");
    bookingSystem.registerUser(user1);
    bookingSystem.registerUser(user2);

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
            bool success = bookingSystem.bookTicket(loggedInUser, selectedEvent, quantity);
            if (success) {
                cout << "Tiket berhasil dibeli!" << endl;
                Booking& booking = bookingSystem.bookings.back();
                booking.displayReceipt();
            } else {
                cout << "Tiket tidak tersedia." << endl;
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
