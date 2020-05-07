#include <iostream>
#include "include/Cinema.h"
#include "include/TicketOffice.h"

int main() {
    Cinema cinema = Cinema("cinema.db3");
    TicketOffice office = TicketOffice(cinema, true);
    office.start();
    return 0;
}
