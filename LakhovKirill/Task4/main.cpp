#include "include/FilmLibrary.h"

int main() {
    FilmLibrary library = FilmLibrary("film_library.db3","film-lib");
    library.start();
    return 0;
}
