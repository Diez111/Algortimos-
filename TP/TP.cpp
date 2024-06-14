#include <iostream>
using namespace std;

struct Persona {
    int dni;
    int edad;
    char sexo;
    char nivelEstudios;
    char indicadorEstudios;
};

struct Familia {
    int id;
    char tipoVivienda;
    int numIntegrantes;
    Persona integrantes[10]; // Asumimos un máximo de 10 personas por familia
};

Familia encuestas[100]; // Asumimos un máximo de 100 familias
int numFamilias = 0;

void ingresarDatosPersona(Persona &persona) {
    cout << "DNI: ";
    cin >> persona.dni;
    cout << "Edad: ";
    cin >> persona.edad;
    cout << "Sexo (F/M): ";
    cin >> persona.sexo;
    cout << "Nivel de estudios (N/P/S/T/U): ";
    cin >> persona.nivelEstudios;
    cout << "Indicador de estudios (I/C): ";
    cin >> persona.indicadorEstudios;
}

void cargarEncuesta() {
    cout << "Ingresar datos de la encuesta (finaliza con id de familia igual a 0):" << endl;
    while (true) {
        Familia familia;
        cout << "Identificador de familia: ";
        cin >> familia.id;
        if (familia.id == 0) break;
        cout << "Tipo de vivienda (C/D): ";
        cin >> familia.tipoVivienda;
        cout << "Cantidad de integrantes: ";
        cin >> familia.numIntegrantes;
        for (int i = 0; i < familia.numIntegrantes; i++) {
            cout << "Integrante " << i + 1 << ":" << endl;
            ingresarDatosPersona(familia.integrantes[i]);
        }
        encuestas[numFamilias++] = familia;
    }
}

int contarEstudiosPrimariosCompletos() {
    int total = 0;
    for (int i = 0; i < numFamilias; i++) {
        for (int j = 0; j < encuestas[i].numIntegrantes; j++) {
            Persona persona = encuestas[i].integrantes[j];
            if (persona.nivelEstudios == 'P' && persona.indicadorEstudios == 'C') {
                total++;
            }
        }
    }
    return total;
}

int contarAnalfabetos() {
    int total = 0;
    for (int i = 0; i < numFamilias; i++) {
        for (int j = 0; j < encuestas[i].numIntegrantes; j++) {
            Persona persona = encuestas[i].integrantes[j];
            if (persona.edad > 10 && persona.nivelEstudios == 'N') {
                total++;
            }
        }
    }
    return total;
}

int contarTotalPersonas() {
    int total = 0;
    for (int i = 0; i < numFamilias; i++) {
        total += encuestas[i].numIntegrantes;
    }
    return total;
}

int sumarEdadTotal() {
    int totalEdad = 0;
    for (int i = 0; i < numFamilias; i++) {
        for (int j = 0; j < encuestas[i].numIntegrantes; j++) {
            totalEdad += encuestas[i].integrantes[j].edad;
        }
    }
    return totalEdad;
}

Familia familiaMayorIntegrantesDepartamento() {
    Familia mayorFamilia;
    int maxIntegrantes = 0;
    for (int i = 0; i < numFamilias; i++) {
        if (encuestas[i].tipoVivienda == 'D' && encuestas[i].numIntegrantes > maxIntegrantes) {
            maxIntegrantes = encuestas[i].numIntegrantes;
            mayorFamilia = encuestas[i];
        }
    }
    return mayorFamilia;
}

void contarNivelesEstudios(int &primarios, int &secundarios, int &terciarios, int &universitarios) {
    primarios = secundarios = terciarios = universitarios = 0;
    for (int i = 0; i < numFamilias; i++) {
        for (int j = 0; j < encuestas[i].numIntegrantes; j++) {
            Persona persona = encuestas[i].integrantes[j];
            switch (persona.nivelEstudios) {
                case 'P': primarios++; break;
                case 'S': secundarios++; break;
                case 'T': terciarios++; break;
                case 'U': universitarios++; break;
            }
        }
    }
}

void contarPorSexo(int &femenino, int &masculino) {
    femenino = masculino = 0;
    for (int i = 0; i < numFamilias; i++) {
        for (int j = 0; j < encuestas[i].numIntegrantes; j++) {
            Persona persona = encuestas[i].integrantes[j];
            if (persona.sexo == 'F') femenino++;
            else if (persona.sexo == 'M') masculino++;
        }
    }
}

void mostrarResultados() {
    int totalEstudiosPrimariosCompletos = contarEstudiosPrimariosCompletos();
    int totalAnalfabetos = contarAnalfabetos();
    int totalPersonas = contarTotalPersonas();
    int totalEdad = sumarEdadTotal();
    Familia mayorFamilia = familiaMayorIntegrantesDepartamento();

    int primarios, secundarios, terciarios, universitarios;
    contarNivelesEstudios(primarios, secundarios, terciarios, universitarios);

    int femenino, masculino;
    contarPorSexo(femenino, masculino);

    cout << "Cantidad de personas con estudios primarios completos: " << totalEstudiosPrimariosCompletos << endl;
    cout << "Porcentaje de analfabetismo: " << (double)totalAnalfabetos / totalPersonas * 100 << "%" << endl;
    cout << "Edad promedio de todas las personas: " << (double)totalEdad / totalPersonas << endl;
    cout << "Identificador de la familia con mayor cantidad de integrantes que viven en departamento: " << mayorFamilia.id << endl;
    cout << "Cantidad de encuestados con estudios primarios: " << primarios << endl;
    cout << "Cantidad de encuestados con estudios secundarios: " << secundarios << endl;
    cout << "Cantidad de encuestados con estudios terciarios: " << terciarios << endl;
    cout << "Cantidad de encuestados con estudios universitarios: " << universitarios << endl;
    cout << "Porcentaje de encuestados de sexo femenino: " << (double)femenino / totalPersonas * 100 << "%" << endl;
    cout << "Porcentaje de encuestados de sexo masculino: " << (double)masculino / totalPersonas * 100 << "%" << endl;
}

void menu() {
    int opcion;
    do {
        cout << "1. Cargar y procesar encuesta\n";
        cout << "2. Mostrar resultados\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch(opcion) {
            case 1:
                cargarEncuesta();
                break;
            case 2:
                mostrarResultados();
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 3);
}

int main() {
    menu();
    return 0;
}
