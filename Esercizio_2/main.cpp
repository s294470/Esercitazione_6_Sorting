#include <iostream>
#include <chrono>
#include <vector>
#include <unistd.h>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;

int main(int argc, char *argv[])
// argc = numero argometni passati in input +1 (indirizzo path)
// argv = array di puntatori formato stringa che contiene gli indirizzi delle cose messe in input
{

    double averagetMerge = 0;
    double averagetBubble = 0;

    for(unsigned int i = 1; i < argc; i++)  // ciclo sulle dimensioni date in input
    {
        // prendo la dimensione del vettore, che do in input, e creo 2 vettori
        int dimension = stoi(argv[i]);   // stoi dà errore, atoi dà 0 se la stringa non è leggibile
        vector<double> vectorMerge(dimension);  // creo i vettori della dimensione giusta
        vector<double> vectorBubble(dimension);

        srand(time(NULL)); //  inizializzo il generatore di numeri casuali con un seme diverso basato sul tempo corrente

        // genero gli elementi dei vettori randomicamente tra 0 e 1000
        for (unsigned int i = 0; i < dimension; i++)
        {
            vectorMerge[i] = rand()%1000;
            vectorBubble[i] = rand()%1000;
        }

        // richiamo gli algoritmi di sorting e cronometro la durata del processo di ognuno
        std::chrono::steady_clock::time_point mergeBegin = std::chrono::steady_clock::now();
        MergeSort(vectorMerge);
        std::chrono::steady_clock::time_point mergeEnd = std::chrono::steady_clock::now();
        double mergeDuration = std::chrono::duration_cast<std::chrono::microseconds> (mergeEnd-mergeBegin).count();

        std::chrono::steady_clock::time_point bubbleBegin = std::chrono::steady_clock::now();
        BubbleSort(vectorBubble);
        std::chrono::steady_clock::time_point bubbleEnd = std::chrono::steady_clock::now();
        double bubbleDuration = std::chrono::duration_cast<std::chrono::microseconds> (bubbleEnd-bubbleBegin).count();

        averagetMerge += mergeDuration;   // uso i contenitori meanMerge e meanBubble come somma per poi andare a dividere per il numero di vettori generati in totale
        averagetBubble += bubbleDuration;

        cout << "Size of vector: " << dimension << endl;     // stampo le info sul signolo vettore
        cout << "MergeSort duration: " << mergeDuration << " microseconds" << endl;
        cout << "BubbleSort duration: " << bubbleDuration << " microseconds" << endl;
        cout << endl;

    }

    averagetMerge = averagetMerge/(argc - 1);   // divido epr il numero di vettori generati, facendo dunque la media
    averagetBubble = averagetBubble/(argc - 1);

    cout << "Average time of MergeSort: " << averagetMerge << " microseconds" << endl;
    cout << "Average time of BubbleSort: " << averagetBubble << " microseconds" << endl;


    // Posso utilizzare questo codice sia per confrontare il tempo di esecuzione su vettori di lunghezze diverse, sia di lunghezze uguali (è possibile inserire n volte lo stesso numero in input). Sperimentando entrambe le modalità si ottiene che:
    // (*) per vettori di dimensioni piccole, il metodo Merge ha durata maggiore di Bubble (n^2/2)
    // (*) per vettori di dimensioni grandi, il metodo Bubble ha durata maggiore di Merge (nlogn)
    // (*) la media di Merge è in generale più bassa di Bubble

    return 0;
}

