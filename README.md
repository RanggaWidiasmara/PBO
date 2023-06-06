# PBO
Object Oriented Programming lecture

**# Final Project For End Of Semester Exam**

**Topic : Ticket Booking System**
explanation :
The goal of this project is to create a ticket booking system that allows users to reserve and purchase tickets for events such as movies, concerts, or sports games. The system will be designed using OOP principles to provide a flexible and scalable architecture.

Here's a breakdown of some key classes and their functionalities:

1. Event: Represents an individual event for which tickets are available. It contains attributes such as event ID, name, date, time, venue, and ticket availability. The Event class provides methods for adding, updating, and retrieving event details.

2. Ticket: Represents an individual ticket for an event. It contains attributes such as ticket ID, event details, seat number, price, and availability. The Ticket class provides methods for booking and purchasing tickets, as well as retrieving ticket information.

3. User: Represents a user of the ticket booking system. It contains attributes such as username, password, and contact information. The User class provides methods for user authentication and managing user-related information.

4. Booking: Represents a booking made by a user for one or more tickets. It contains information such as the user, event, tickets booked, booking date, and booking status. The Booking class provides methods for creating, updating, and canceling bookings, as well as retrieving booking details.

5. BookingSystem: The main class that brings all the components together. It manages the events, tickets, users, and bookings. It provides methods for user registration, login/logout, browsing events, checking ticket availability, booking and purchasing tickets, and managing bookings.

Additional features you can consider adding include seat selection for events with assigned seating, multiple ticket types (e.g., VIP, General), discounts or promotions, and the ability for users to view their booking history.

By using OOP principles, you can encapsulate the data and behavior within each class, making the code modular and reusable. You can also incorporate error handling and validation mechanisms to ensure that users can only book available tickets and prevent invalid operations.

Remember to consider potential scalability and performance issues, especially if dealing with a large number of events and ticket bookings. Database integration can be used to persist data and enhance the system's performance.

This project provides a foundation for building a comprehensive ticket booking system, and you can expand on these ideas to further enhance its functionality and user experience.
