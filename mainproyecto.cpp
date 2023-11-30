#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

struct Contacto {
    std::string nombre;
    std::string numeroTelefono;
    std::string redSocial;
    std::string icono;
    std::string direccion;
    int frecuenciaAcceso;

    Contacto(const std::string& n, const std::string& telefono, const std::string& red,
             const std::string& ic, const std::string& dir)
        : nombre(n), numeroTelefono(telefono), redSocial(red), icono(ic), direccion(dir), frecuenciaAcceso(0) {}
};

class NodoBST {
public:
    Contacto contacto;
    NodoBST* izquierda;
    NodoBST* derecha;

    NodoBST(const Contacto& c) : contacto(c), izquierda(nullptr), derecha(nullptr) {}
};

class ArbolBST {
private:
    NodoBST* raiz;
 
public:
    ArbolBST() : raiz(nullptr) {}

    void agregarContacto(const Contacto& contacto) {
        raiz = agregarRecursivo(raiz, contacto);
    }

    void eliminarContacto(const std::string& nombre) {
        raiz = eliminarRecursivo(raiz, nombre);
    }

    Contacto* buscarContacto(const std::string& nombre) {
        return buscarRecursivo(raiz, nombre);
    }

    void mostrarContactosOrdenados() {
        mostrarRecursivo(raiz);
    }
    
    void mostrarContactosPorFrecuencia() {
    std::vector<Contacto> contactosOrdenados;
    obtenerContactosOrdenados(raiz, contactosOrdenados, true);

    for (const auto& contacto : contactosOrdenados) {
        if (contacto.frecuenciaAcceso > 0) {
            mostrarContacto(contacto);
        }
    }
    }


    void mostrarContacto(const Contacto& contacto) {
        std::cout << "Nombre: " << contacto.nombre << std::endl;
        std::cout << "Número de Teléfono: " << contacto.numeroTelefono << std::endl;
        std::cout << "Red Social: " << contacto.redSocial << std::endl;
        std::cout << "Icono: " << contacto.icono << std::endl;
        std::cout << "Dirección: " << contacto.direccion << std::endl;
        std::cout << "Frecuencia de Acceso: " << contacto.frecuenciaAcceso << std::endl;
        std::cout << "----------------------" << std::endl;
    }

private:
    NodoBST* agregarRecursivo(NodoBST* nodo, const Contacto& contacto) {
        if (nodo == nullptr) {
            return new NodoBST(contacto);
        }

        if (contacto.nombre < nodo->contacto.nombre) {
            nodo->izquierda = agregarRecursivo(nodo->izquierda, contacto);
        } else if (contacto.nombre > nodo->contacto.nombre) {
            nodo->derecha = agregarRecursivo(nodo->derecha, contacto);
        }

        return nodo;
    }

    NodoBST* eliminarRecursivo(NodoBST* nodo, const std::string& nombre) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (nombre < nodo->contacto.nombre) {
            nodo->izquierda = eliminarRecursivo(nodo->izquierda, nombre);
        } else if (nombre > nodo->contacto.nombre) {
            nodo->derecha = eliminarRecursivo(nodo->derecha, nombre);
        } else {
            if (nodo->izquierda == nullptr) {
                NodoBST* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                NodoBST* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }

            NodoBST* sucesor = encontrarMinimo(nodo->derecha);
            nodo->contacto = sucesor->contacto;
            nodo->derecha = eliminarRecursivo(nodo->derecha, sucesor->contacto.nombre);
        }

        return nodo;
    }

    Contacto* buscarRecursivo(NodoBST* nodo, const std::string& nombre) {
        if (nodo == nullptr || nodo->contacto.nombre == nombre) {
            return (nodo != nullptr) ? &(nodo->contacto) : nullptr;
        }

        if (nombre < nodo->contacto.nombre) {
            return buscarRecursivo(nodo->izquierda, nombre);
        } else {
            return buscarRecursivo(nodo->derecha, nombre);
        }
    }

    void mostrarRecursivo(NodoBST* nodo) {
        if (nodo != nullptr) {
            mostrarRecursivo(nodo->izquierda);
            mostrarContacto(nodo->contacto);
            mostrarRecursivo(nodo->derecha);
        }
    }

    NodoBST* encontrarMinimo(NodoBST* nodo) {
        while (nodo->izquierda != nullptr) {
            nodo = nodo->izquierda;
        }
        return nodo;
    }
    void obtenerContactosOrdenados(NodoBST* nodo, std::vector<Contacto>& contactos, bool ordenarPorFrecuencia) {
        if (nodo != nullptr) {
            obtenerContactosOrdenados(nodo->izquierda, contactos, ordenarPorFrecuencia);
            contactos.push_back(nodo->contacto);
            obtenerContactosOrdenados(nodo->derecha, contactos, ordenarPorFrecuencia);
        }

        if (ordenarPorFrecuencia) {
            std::sort(contactos.begin(), contactos.end(), [](const Contacto& a, const Contacto& b) {
                return a.frecuenciaAcceso > b.frecuenciaAcceso;
            });
        }
    }
};

class LibretaContactos {
private:
    
    std::vector<Contacto> indiceRapido;
    std::queue<std::vector<Contacto>> colaCopiaSeguridad;
    int contarContactos() const {
        return indiceRapido.size();
    }
    


public:

    ArbolBST contactosBST;
    
    void agregarContacto() {
        std::string nombre, numeroTelefono, redSocial, icono, direccion;

        std::cout << "Ingrese el nombre: ";
        std::getline(std::cin, nombre);

        std::cout << "Ingrese el número de teléfono: ";
        std::getline(std::cin, numeroTelefono);

        std::cout << "Ingrese la red social: ";
        std::getline(std::cin, redSocial);

        std::cout << "Ingrese el icono: ";
        std::getline(std::cin, icono);

        std::cout << "Ingrese la dirección: ";
        std::getline(std::cin, direccion);

        Contacto nuevoContacto(nombre, numeroTelefono, redSocial, icono, direccion);
        contactosBST.agregarContacto(nuevoContacto);
        indiceRapido.push_back(nuevoContacto);

        std::cout << "Contacto agregado exitosamente." << std::endl;
    }

    void eliminarContacto(const std::string& nombre) {
        auto encontrado = contactosBST.buscarContacto(nombre);
        if (encontrado != nullptr) {
            contactosBST.eliminarContacto(nombre);
            indiceRapido.erase(
                std::remove_if(indiceRapido.begin(), indiceRapido.end(),
                               [nombre](const Contacto& c) { return c.nombre == nombre; }),
                indiceRapido.end());

            std::cout << "Contacto eliminado exitosamente." << std::endl;
        } else {
            std::cout << "Contacto no encontrado." << std::endl;
        }
    }
    
    void guardarContactosEnArchivo(const std::string& nombreArchivo) const {   //
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        for (const auto& contacto : indiceRapido) {
            archivo << "Nombre: " << contacto.nombre << std::endl;
            archivo << "Número de Teléfono: " << contacto.numeroTelefono << std::endl;
            archivo << "Red Social: " << contacto.redSocial << std::endl;
            archivo << "Icono: " << contacto.icono << std::endl;
            archivo << "Dirección: " << contacto.direccion << std::endl;
            archivo << "Frecuencia de Acceso: " << contacto.frecuenciaAcceso << std::endl;
            archivo << "----------------------" << std::endl;
        }

        std::cout << "Contactos guardados en el archivo: " << nombreArchivo << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar contactos." << std::endl;
    }
}


    void buscarContacto(const std::string& nombre) {
    auto encontrado = contactosBST.buscarContacto(nombre);
    if (encontrado != nullptr) {
        encontrado->frecuenciaAcceso++;

        std::cout << "Contacto encontrado:" << std::endl;
        contactosBST.mostrarContacto(*encontrado);
    } else {
        std::cout << "Contacto no encontrado." << std::endl;
    }
    }

    void mostrarTotalContactos() {
        int total = contarContactos();
        std::cout << "Total de contactos: " << total << std::endl;
    }

    void mostrarPorInicial(char inicial) {
    std::cout << "Contactos cuyos nombres comienzan con '" << inicial << "':" << std::endl;

    // Convertir la inicial a minúscula para que la comparación sea insensible a mayúsculas y minúsculas
    inicial = std::tolower(inicial);

    for (const auto& contacto : indiceRapido) {
        // Convertir la primera letra del nombre a minúscula para la comparación
        char primeraLetra = std::tolower(contacto.nombre.front());

        if (primeraLetra == inicial) {
            contactosBST.mostrarContacto(contacto);
        }
    }
    }

    
   

    void realizarCopiaSeguridad() {
    colaCopiaSeguridad.push(indiceRapido);

    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo para la copia de seguridad: ";
    std::getline(std::cin, nombreArchivo);

    guardarContactosEnArchivo(nombreArchivo);
}


    void visualizarFrecuentes() {
    std::cout << "Lista de contactos ordenada por frecuencia (frecuencia > 0):" << std::endl;
    contactosBST.mostrarContactosPorFrecuencia();
    }


    void limpiarBuffer() {
        std::cin.clear(); // Limpia el estado del flujo
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta el contenido del búfer
    }

    
};

int main() {
    LibretaContactos libreta;
    char opcion;
    std::string nombreAEliminar, nombreABuscar;

    do {
        std::cout << "Seleccione una operacion:" << std::endl;
        std::cout << "1. Agregar un contacto\n2. Buscar un contacto\n3. Eliminar un contacto\n";
        std::cout << "4. Mostrar contactos ordenados\n5. Mostrar total de contactos\n";
        std::cout << "6. Mostrar contactos por inicial\n7. Realizar copia de seguridad\n";
        std::cout << "8. Visualizar contactos frecuentes\n9. Salir\n";
        std::cout << "Ingrese su eleccion: ";
        std::cin >> opcion;
        libreta.limpiarBuffer(); // Limpiar el búfer después de la lectura del carácter

        switch (opcion) {
            case '1':
                libreta.agregarContacto();
                break;
            case '2':
            std::cout << "Ingrese el nombre a buscar: ";
                std::getline(std::cin, nombreABuscar);
                libreta.buscarContacto(nombreABuscar);
                break;
                
            case '3':
            std::cout << "Ingrese el nombre a eliminar: ";
                std::getline(std::cin, nombreAEliminar);
                libreta.eliminarContacto(nombreAEliminar);
                break;
                
            case '4':
                std::cout << "Lista de contactos ordenada:" << std::endl;
                libreta.contactosBST.mostrarContactosOrdenados();
                break;
            case '5':
                libreta.mostrarTotalContactos();
                break;
            case '6': {
                char inicial;
                std::cout << "Ingrese la inicial: ";
                std::cin >> inicial;
                libreta.mostrarPorInicial(inicial);
                break;
            }
            case '7':
                libreta.realizarCopiaSeguridad();
                break;
            case '8':
             std::cout << "Lista de contactos ordenada por frecuencia:" << std::endl;
             libreta.contactosBST.mostrarContactosPorFrecuencia();
             break;
            case '9':
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }
    } while (opcion != '9');

    return 0;
}
