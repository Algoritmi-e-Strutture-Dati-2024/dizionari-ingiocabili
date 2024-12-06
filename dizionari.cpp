#include <iostream>
#include <string>

template <typename T>
class DizionarioEsteso {
private:
    static const int TABLE_SIZE = 10; // Dimensione della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false; // Indica se la cella è occupata
    };

    Entry table[TABLE_SIZE]; // Tabella hash

    // Funzione di hash semplice che restituisce un indice per una chiave
    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash += static_cast<int>(ch); // Somma dei valori ASCII dei caratteri
        }
        return hash % TABLE_SIZE; // Prendiamo il modulo per ottenere un indice nella tabella
    }

    // Funzione per trovare un slot libero usando il linear probing
    int findSlot(int startIndex) const {
        int index = startIndex;
        while (table[index].isOccupied) { // Cerchiamo una cella libera
            index = (index + 1) % TABLE_SIZE; // Se troviamo una collisione, proviamo la posizione successiva
        }
        return index;
    }

public:
    // Inserisci una coppia chiave-valore
    void inserisci(const std::string& key, const T value) {
        int index = hashFunction(key); // Calcoliamo l'indice con la funzione di hash
        if (table[index].isOccupied) { // Se la cella è già occupata, usiamo linear probing
            index = findSlot(index);
        }
        table[index] = {key, value, true}; // Inseriamo la chiave e il valore
    }

    // Cancella la coppia associata alla chiave
    void cancella(const std::string& key) {
        int index = hashFunction(key);
        int startIndex = index; // Salviamo l'indice iniziale
        do {
            if (table[index].isOccupied && table[index].key == key) {
                table[index].isOccupied = false; // Rimuoviamo la chiave
                return;
            }
            index = (index + 1) % TABLE_SIZE; // Proviamo la cella successiva
        } while (index != startIndex); // Cicliamo finché non torniamo all'indice iniziale
    }

    // Recupera il valore associato alla chiave
    T recupera(const std::string& key) const {
        int index = hashFunction(key);
        int startIndex = index;
        do {
            if (table[index].isOccupied && table[index].key == key) {
                return table[index].value; // Restituiamo il valore
            }
            index = (index + 1) % TABLE_SIZE; // Proviamo la cella successiva
        } while (index != startIndex); // Cicliamo finché non torniamo all'indice iniziale
        throw std::runtime_error("Chiave non trovata"); // Se non troviamo la chiave
    }

    // Verifica se la chiave è presente nel dizionario
    bool appartiene(const std::string& key) const {
        int index = hashFunction(key);
        int startIndex = index;
        do {
            if (table[index].isOccupied && table[index].key == key) {
                return true; // La chiave è presente
            }
            index = (index + 1) % TABLE_SIZE; // Proviamo la cella successiva
        } while (index != startIndex); // Cicliamo finché non torniamo all'indice iniziale
        return false; // La chiave non è presente
    }

    // Stampa il contenuto della tabella hash
    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied) {
                std::cout << "[" << i << "] " << table[i].key << " : " << table[i].value << std::endl;
            } else {
                std::cout << "[" << i << "] - " << std::endl; // Slot vuoto
            }
        }
    }
};

// Funzione main per dimostrare il funzionamento
int main() {
    DizionarioEsteso<int> dizionario;
    
    // Inseriamo alcune coppie chiave-valore
    dizionario.inserisci("apple", 1);
    dizionario.inserisci("banana", 2);
    dizionario.inserisci("orange", 3);
    
    // Stampa il contenuto della tabella
    std::cout << "Contenuto del dizionario:<< std::endl";
    dizionario.stampa();

    // Testiamo il recupero di un valore
    try {
        std::cout << "Valore per 'banana': " << dizionario.recupera("banana") << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // Verifica se una chiave esiste nel dizionario
    std::cout << "Esiste 'orange'? " << (dizionario.appartiene("orange") ? "Sì" : "No") << std::endl;

    // Cancelliamo una chiave
    dizionario.cancella("banana");
    std::cout << "Dopo aver cancellato 'banana':<< std::endl";
    dizionario.stampa();

    return 0;
}
