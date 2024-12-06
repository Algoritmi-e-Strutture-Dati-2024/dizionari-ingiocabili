[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/4-uGPtLY)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=17459240&assignment_repo_type=AssignmentRepo)
# Dizionario Esteso

## Descrizione del Progetto

Implementa una classe in C++ chiamata **`DizionarioEsteso`**, che rappresenta un dizionario basato su una tabella hash. La classe supporta operazioni base per la gestione delle coppie `<chiave, valore>` e offre funzionalità per gestire le collisioni.

## Funzionalità

1. **Gestione delle Coppie `<chiave, valore>`**
   - **Inserisci**: Aggiunge una coppia `<chiave, valore>` al dizionario. (é giá implementata nel codice base)
   - **Cancella**: Rimuove una coppia dato il valore della chiave. 
   - **Recupera**: Restituisce il valore associato a una chiave specifica. (é giá implementata nel codice base)
   - **Appartiene**: Verifica se una chiave è presente nel dizionario.
   - **Stampa**: Stampa il contenuto del dizionario in un formato leggibile. (é giá implementata nel codice base)

2. **Hashing Chiuso** 
  Le collisioni sono gestite tramite la ricerca di posizioni alternative. É possibile scegliere tra Linear Probing e Double Hashing.
   - La funzione di hash è basata sulla somma dei valori ASCII dei caratteri della stringa, modulo la dimensione della tabella (é giá implementata nel codice base):
     ```cpp
     int hashFunction(const std::string& key) const {
         int hash = 0;
         for (char ch : key) {
             hash += static_cast<int>(ch);
         }
         return hash % TABLE_SIZE;
     }
     ```
   -  Implementare **findSlot** che viene chimata dopo che la posizione restituita da hashFunction é giá piena. Prende in input l'indice restituito da hashFunction giá pieno e:
         - Double hasching: calcola il modulo della divisione per la grandezza della tabella, cioé 100.
         - Linear Probing: scansiona table partendo dalla posizione in input fino a trovare una posizione libera e la restituisce in output.
    -  Modificare la funzione di Inserisci: In caso di collisione (quindi la cella in cui inserire é giá occupata) calcola la nuova posizione in cui inserire l'elemento richiamando la funzione **findSlot**.
    -  Modificare le funzioni di Cancella, Modifica, Recupera e Appartiene: se nella posizione restituita dall'hashFunction non é presente la chiave cercata:
         - Double hasching: richiamare **findSlot** sul valore restituito dadall'hashFunction per trovare la posizione corretta in cui é inserita la chiave cercata
         - Linear Probing: scansionare tutte le celle successive a quella restituita dadall'hashFunction fino a trovare una piena (se la chiave é uguale a quella cercata continuo con il metodo, altrimenti do errore di chiave non esistente)
     
3. **Main**
   Modificare il main utilizzando i nuovi metodi implementati e aggiungendo uno o piú casi di collisione. Inserire le stampe necessarie per mostrare il corretto funzionamento dei metodi implementati.

## Dettagli Tecnici

Struttura della Classe
La classe utilizza i template per permettere l'uso di tipi generici come valori. La struttura della tabella hash è un array di coppie <chiave, valore> con un indicatore di occupazione.

Esempio di firma della classe:

 ```cpp
template <typename T>
class DizionarioEsteso {
private:
    static const int TABLE_SIZE = 10; // Dimensione della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false; // Indica se lo slot è occupato
    };

    Entry table[TABLE_SIZE]; // Tabella hash

    int hashFunction(const std::string key) const;

    // Funzione per trovare la posizione corretta (gestisce il linear probing o quadratic probing o double hashing)
    int findSlot(const std::string key) const;

public:

    void inserisci(const std::string key, const T value);
    void cancella(const std::string key);
    T recupera(const std::string key) const;
    bool appartiene(const std::string key) const;

    void stampa() const;
};
 ```
