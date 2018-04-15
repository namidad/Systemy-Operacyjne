# Systemy-Operacyjne

Wymagania funkcjonalne

Program ma przy użyciu biblioteki ncurses podzielić okno terminala na 4 części. W każdej z nich, oddzielny wątek powinien poruszać skończonej długości wężem (jak w kultowej grze Snake) błądzącym losowo w granicach danej części. Dodatkowe funkcjonalności pozostają kwestią otwartą i każdy może je dowolnie wprowadzać.
Wymagania formalne

    użycie C++ 11 lub C oraz POSIX Threads
    tworzenie i uruchamianie watkow (std::thread)
    poprawne kończenie wątków i zamykanie aplikacji (zamknięcie wszystkich wątków przed zamknięciem wątku glownego)
    użycie biblioteki ncurses
    poprawna synchronizacja dostępu wątków do bilbioteki ncurses przy użyciu podstawowego mechanizmu synchronizacji w postaci std::mutex (plus opcjonalnie wrappery typu std::lock_guard itp.)
