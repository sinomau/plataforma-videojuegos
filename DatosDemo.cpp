#include <iostream>
#include "DatosDemo.h"

using namespace std;

void DatosDemo::addUsuario(UsuarioArchivo& a, const char* nom, const char* ape, const char* mail,
                           const char* user, const char* pass, int rol, float saldo, Fecha f) {
    Usuario u;
    u.cargar(a.obtenerNuevoId(), nom, ape, mail, user, pass, rol);
    u.setSaldo(saldo);
    u.setFechaRegistro(f);
    a.escribirDisco(u);
}

void DatosDemo::addCategoria(CategoriaArchivo& a, const char* nombre, const char* desc) {
    Categoria c;
    c.cargar(a.obtenerNuevoId(), nombre, desc);
    a.escribirDisco(c);
}

void DatosDemo::addDesarrollador(DesarrolladorArchivo& a, const char* nombre, const char* pais, int anio) {
    Desarrollador d;
    d.cargar(a.obtenerNuevoId(), nombre, pais, anio);
    a.escribirDisco(d);
}

void DatosDemo::addJuego(JuegoArchivo& a, const char* titulo, int idCat, int idDes, float precio, Fecha f) {
    Juego j;
    j.cargar(a.obtenerNuevoId(), titulo, idCat, idDes, precio, f);
    a.escribirDisco(j);
}

void DatosDemo::addCompra(CompraArchivo& a, int idUsuario, int idJuego, float importe, Fecha f) {
    Compra c;
    c.cargar(a.obtenerNuevoId(), idUsuario, idJuego, importe);
    c.setFechaCompra(f);
    a.escribirDisco(c);
}

void DatosDemo::addResenia(ReseniaArchivo& a, int idUsuario, int idJuego, int puntaje, const char* com, Fecha f) {
    Resenia r;
    r.cargar(a.obtenerNuevoId(), idUsuario, idJuego, puntaje, com, f);
    a.escribirDisco(r);
}

void DatosDemo::cargarDatosDemo() {
    UsuarioArchivo aUsu;
    if (aUsu.getCantidadRegistros() > 0) {
        cout << "Ya hay datos cargados. Borre los .dat si quiere regenerarlos." << endl;
        return;
    }

    CategoriaArchivo aCat;
    DesarrolladorArchivo aDes;
    JuegoArchivo aJue;
    CompraArchivo aCom;
    ReseniaArchivo aRes;

    // Usuarios (3 y 4 comparten fecha a proposito, para probar empates)
    addUsuario(aUsu, "Ana",       "Lopez",     "ana.lopez@plataforma.dev", "admin",      "1234", ROL_ADMIN,   0,     Fecha(15, 1, 2023));
    addUsuario(aUsu, "Leonel",    "Perez",     "leonel.perez@gmail.com",   "leo_perez",  "1234", ROL_USUARIO, 12500, Fecha(3, 3, 2023));
    addUsuario(aUsu, "Micaela",   "Gomez",     "mica.gomez@gmail.com",     "mica_gomez", "1234", ROL_USUARIO, 8300,  Fecha(22, 6, 2023));
    addUsuario(aUsu, "Tomas",     "Diaz",      "tomas.diaz@gmail.com",     "tomi_diaz",  "1234", ROL_USUARIO, 800,   Fecha(22, 6, 2023));
    addUsuario(aUsu, "Lucia",     "Fernandez", "lucia.fernandez@gmail.com","luciaf",     "1234", ROL_USUARIO, 21000, Fecha(9, 9, 2023));
    addUsuario(aUsu, "Mateo",     "Rodriguez", "mateo.rodriguez@hotmail.com","mateo_r",  "1234", ROL_USUARIO, 4500,  Fecha(14, 11, 2023));
    addUsuario(aUsu, "Sofia",     "Martinez",  "sofia.martinez@gmail.com", "sofi_m",     "1234", ROL_USUARIO, 15200, Fecha(27, 2, 2024));
    addUsuario(aUsu, "Nicolas",   "Sosa",      "nico.sosa@outlook.com",    "nico_sosa",  "1234", ROL_USUARIO, 600,   Fecha(18, 5, 2024));
    addUsuario(aUsu, "Valentina", "Romero",    "vale.romero@gmail.com",    "vale_romero","1234", ROL_USUARIO, 9800,  Fecha(30, 8, 2024));
    addUsuario(aUsu, "Agustin",   "Torres",    "agustin.torres@gmail.com", "agus_torres","1234", ROL_USUARIO, 33000, Fecha(12, 12, 2024));
    addUsuario(aUsu, "Camila",    "Acosta",    "cami.acosta@hotmail.com",  "cami_acosta","1234", ROL_USUARIO, 2750,  Fecha(8, 4, 2025));
    addUsuario(aUsu, "Joaquin",   "Benitez",   "joaquin.benitez@gmail.com","joaco_b",    "1234", ROL_USUARIO, 18400, Fecha(19, 7, 2025));
    addUsuario(aUsu, "Julieta",   "Suarez",    "juli.suarez@gmail.com",    "juli_suarez","1234", ROL_USUARIO, 7100,  Fecha(2, 10, 2025));
    addUsuario(aUsu, "Franco",    "Molina",    "franco.molina@outlook.com","franco_m",   "1234", ROL_USUARIO, 25000, Fecha(25, 1, 2026));
    addUsuario(aUsu, "Martina",   "Castro",    "marti.castro@gmail.com",   "marti_castro","1234", ROL_USUARIO, 11300, Fecha(11, 5, 2026));

    // Categorias
    addCategoria(aCat, "Accion",     "Combate, tiros y accion en tercera o primera persona");
    addCategoria(aCat, "RPG",        "Juegos de rol con progresion de personaje");
    addCategoria(aCat, "Aventura",   "Exploracion, puzzles e historia");
    addCategoria(aCat, "Deportes",   "Simuladores deportivos");
    addCategoria(aCat, "Carreras",   "Juegos de conduccion y velocidad");
    addCategoria(aCat, "Estrategia", "Planificacion, gestion y tacticas por turnos");
    addCategoria(aCat, "Terror",     "Survival horror y suspenso");

    // Desarrolladores
    addDesarrollador(aDes, "CD Projekt Red",   "Polonia",      2002);
    addDesarrollador(aDes, "FromSoftware",     "Japon",        1986);
    addDesarrollador(aDes, "Valve",            "Estados Unidos", 1996);
    addDesarrollador(aDes, "Mojang Studios",   "Suecia",       2009);
    addDesarrollador(aDes, "Rockstar Games",   "Estados Unidos", 1998);
    addDesarrollador(aDes, "Electronic Arts",  "Estados Unidos", 1982);
    addDesarrollador(aDes, "Capcom",           "Japon",        1979);
    addDesarrollador(aDes, "Square Enix",      "Japon",        1986);
    addDesarrollador(aDes, "Ubisoft",          "Francia",      1986);
    addDesarrollador(aDes, "Playground Games", "Reino Unido",  2010);
    addDesarrollador(aDes, "Firaxis Games",    "Estados Unidos", 1996);
    addDesarrollador(aDes, "Team Cherry",      "Australia",    2014);
    addDesarrollador(aDes, "ConcernedApe",     "Estados Unidos", 2011);

    // Juegos (titulo, categoria, desarrollador, precio, lanzamiento)
    addJuego(aJue, "The Witcher 3: Wild Hunt",    2, 1,  18999.00f, Fecha(19, 5, 2015));
    addJuego(aJue, "Elden Ring",                  2, 2,  29999.00f, Fecha(25, 2, 2022));
    addJuego(aJue, "Portal 2",                    3, 3,   6999.00f, Fecha(19, 4, 2011));
    addJuego(aJue, "Minecraft",                   3, 4,  12999.00f, Fecha(18, 11, 2011));
    addJuego(aJue, "Red Dead Redemption 2",       1, 5,  24999.00f, Fecha(26, 10, 2018));
    addJuego(aJue, "Grand Theft Auto V",          1, 5,  15999.00f, Fecha(17, 9, 2013));
    addJuego(aJue, "EA Sports FC 24",             4, 6,  27999.00f, Fecha(29, 9, 2023));
    addJuego(aJue, "Resident Evil 4",             7, 7,  26999.00f, Fecha(24, 3, 2023));
    addJuego(aJue, "Half-Life 2",                 1, 3,   4999.00f, Fecha(16, 11, 2004));
    addJuego(aJue, "Final Fantasy VII Remake",    2, 8,  24999.00f, Fecha(10, 4, 2020));
    addJuego(aJue, "Stardew Valley",              3, 13,  5999.00f, Fecha(26, 2, 2016));
    addJuego(aJue, "Assassins Creed Valhalla",    1, 9,  21999.00f, Fecha(10, 11, 2020));
    addJuego(aJue, "Dark Souls III",              2, 2,  14999.00f, Fecha(12, 4, 2016));
    addJuego(aJue, "Cyberpunk 2077",              2, 1,  22999.00f, Fecha(10, 12, 2020));
    addJuego(aJue, "Forza Horizon 5",             5, 10, 23999.00f, Fecha(9, 11, 2021));
    addJuego(aJue, "Civilization VI",             6, 11, 17999.00f, Fecha(21, 10, 2016));
    addJuego(aJue, "Left 4 Dead 2",               7, 3,   5999.00f, Fecha(17, 11, 2009));
    addJuego(aJue, "Hollow Knight",               3, 12,  7999.00f, Fecha(24, 2, 2017));

    // Compras (usuario, juego, importe, fecha)
    addCompra(aCom, 2, 1,  18999.00f, Fecha(10, 4, 2023));
    addCompra(aCom, 2, 9,   4999.00f, Fecha(10, 4, 2023));
    addCompra(aCom, 2, 6,  15999.00f, Fecha(2, 8, 2023));
    addCompra(aCom, 3, 3,   6999.00f, Fecha(1, 7, 2023));
    addCompra(aCom, 3, 4,  12999.00f, Fecha(15, 7, 2023));
    addCompra(aCom, 3, 11,  5999.00f, Fecha(3, 10, 2023));
    addCompra(aCom, 3, 2,  29999.00f, Fecha(14, 2, 2026));
    addCompra(aCom, 4, 6,  15999.00f, Fecha(5, 7, 2023));
    addCompra(aCom, 4, 17,  5999.00f, Fecha(20, 9, 2023));
    addCompra(aCom, 5, 2,  29999.00f, Fecha(12, 3, 2024));
    addCompra(aCom, 5, 18,  7999.00f, Fecha(12, 3, 2024));
    addCompra(aCom, 5, 13, 14999.00f, Fecha(28, 6, 2024));
    addCompra(aCom, 6, 5,  24999.00f, Fecha(5, 12, 2023));
    addCompra(aCom, 6, 14, 22999.00f, Fecha(24, 12, 2023));
    addCompra(aCom, 6, 7,  27999.00f, Fecha(15, 2, 2024));
    addCompra(aCom, 6, 18,  7999.00f, Fecha(8, 5, 2026));
    addCompra(aCom, 7, 8,  26999.00f, Fecha(14, 4, 2024));
    addCompra(aCom, 7, 11,  5999.00f, Fecha(2, 6, 2024));
    addCompra(aCom, 7, 3,   6999.00f, Fecha(19, 11, 2024));
    addCompra(aCom, 8, 12, 21999.00f, Fecha(3, 7, 2024));
    addCompra(aCom, 8, 15, 23999.00f, Fecha(21, 9, 2024));
    addCompra(aCom, 8, 1,  18999.00f, Fecha(29, 11, 2024));
    addCompra(aCom, 9, 16, 17999.00f, Fecha(10, 10, 2024));
    addCompra(aCom, 9, 4,  12999.00f, Fecha(10, 10, 2024));
    addCompra(aCom, 9, 10, 24999.00f, Fecha(15, 1, 2025));
    addCompra(aCom, 10, 2, 29999.00f, Fecha(20, 2, 2025));
    addCompra(aCom, 10, 14,22999.00f, Fecha(14, 3, 2025));
    addCompra(aCom, 10, 5, 24999.00f, Fecha(1, 8, 2025));
    addCompra(aCom, 11, 7, 27999.00f, Fecha(26, 4, 2025));
    addCompra(aCom, 11, 13,14999.00f, Fecha(9, 6, 2025));
    addCompra(aCom, 12, 8, 26999.00f, Fecha(30, 7, 2025));
    addCompra(aCom, 12, 17, 5999.00f, Fecha(15, 8, 2025));
    addCompra(aCom, 12, 9,  4999.00f, Fecha(3, 11, 2025));
    addCompra(aCom, 13, 18, 7999.00f, Fecha(10, 10, 2025));
    addCompra(aCom, 13, 1, 18999.00f, Fecha(5, 12, 2025));
    addCompra(aCom, 14, 2, 29999.00f, Fecha(2, 2, 2026));
    addCompra(aCom, 14, 12,21999.00f, Fecha(17, 3, 2026));
    addCompra(aCom, 14, 16,17999.00f, Fecha(20, 5, 2026));
    addCompra(aCom, 15, 14,22999.00f, Fecha(15, 5, 2026));
    addCompra(aCom, 15, 11, 5999.00f, Fecha(3, 7, 2026));
    addCompra(aCom, 15, 15,23999.00f, Fecha(9, 9, 2026));

    // Resenias (usuario, juego, puntaje, comentario, fecha)
    addResenia(aRes, 2, 1,  5, "Obra maestra, mundo enorme",             Fecha(20, 4, 2023));
    addResenia(aRes, 2, 6,  4, "Muy completo, todavia lo juego",         Fecha(20, 8, 2023));
    addResenia(aRes, 3, 3,  5, "Puzzles geniales y muy buen humor",      Fecha(10, 7, 2023));
    addResenia(aRes, 3, 4,  4, "Infinito para jugar con amigos",         Fecha(30, 7, 2023));
    addResenia(aRes, 4, 6,  4, "Buena historia y mucho para hacer",      Fecha(18, 7, 2023));
    addResenia(aRes, 5, 2,  5, "Dificil pero muy gratificante",          Fecha(30, 3, 2024));
    addResenia(aRes, 5, 18, 5, "Arte y musica increibles",               Fecha(15, 4, 2024));
    addResenia(aRes, 6, 5,  5, "Ambientacion increible",                 Fecha(20, 12, 2023));
    addResenia(aRes, 6, 14, 3, "Salio con bugs pero mejoro bastante",    Fecha(10, 1, 2024));
    addResenia(aRes, 6, 7,  2, "Cambia muy poco respecto al anterior",   Fecha(1, 3, 2024));
    addResenia(aRes, 7, 8,  5, "Remake excelente",                       Fecha(1, 5, 2024));
    addResenia(aRes, 8, 12, 3, "Largo y repetitivo por momentos",        Fecha(20, 8, 2024));
    addResenia(aRes, 8, 15, 4, "Graficos espectaculares",                Fecha(5, 10, 2024));
    addResenia(aRes, 9, 16, 4, "Muy adictivo, un turno mas y listo",     Fecha(30, 10, 2024));
    addResenia(aRes, 10, 2, 5, "El mejor juego que jugue este anio",     Fecha(15, 3, 2025));
    addResenia(aRes, 11, 7, 3, "Cumple, pero es caro",                   Fecha(20, 5, 2025));
    addResenia(aRes, 12, 17,4, "Ideal para jugar cooperativo",           Fecha(1, 9, 2025));
    addResenia(aRes, 13, 18,5, "Muy recomendable",                       Fecha(1, 11, 2025));
    addResenia(aRes, 14, 2, 4, "Gran desafio",                           Fecha(20, 2, 2026));
    addResenia(aRes, 15, 14,4, "Ahora esta muy pulido",                  Fecha(1, 6, 2026));

    cout << "Datos de demostracion cargados correctamente." << endl;
}
