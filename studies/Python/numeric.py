def metoda_polawiania(a_wejsc, b_wejsc, epsilon):
    krok = 0
    znaleziona_wartosc = 0
    a = a_wejsc
    b = b_wejsc
    while znaleziona_wartosc == 0:
        c = (a+b)/2
        krok += 1
        fc = c**5 + c + 2022
        if abs(b-a) < epsilon:
            znaleziona_wartosc = c
        else:
            fa = a**5 + a + 2022
            if fa * fc < 0:
                b = c
            else:
                a = c
    return znaleziona_wartosc, krok

def metoda_siecznych(a_wejsc, b_wejsc, epsilon):
    krok = 0
    znaleziona_wartosc = 0
    a = a_wejsc
    b = b_wejsc
    while znaleziona_wartosc == 0:
        fa = a**5 + a + 2022
        fb = b**5 + b + 2022
        c = b - ((fb*(b-a))/(fb-fa))
        krok += 1
        if abs(b-a) < epsilon:
            znaleziona_wartosc = c
        else:
            a = b
            b = c
    return znaleziona_wartosc, krok

def warunek(a, b):
    x = a**5 + a + 2022
    y = b**5 + b + 2022
    if x * y < 0:
        return True
    else:
        return False

if __name__ == "__main__":
    warunek_zadania = False
    epsilon = 0
    print("Funkcja: x^5 + x + 2022")
    while epsilon <= 0:
        print("Wprowadz dokladnosc przyblizenia epsilon:")
        epsilon = float(input())
        if epsilon <= 0:
            print("Bledna wartosc epsilona. Prosze wprowadzic ponownie")

    while warunek_zadania == False:
        print("Wprowadz lewy koniec przedzialu a:")
        a_wejsc = int(input())
        print("Wprowadz prawy koniec przedzialu b:")
        b_wejsc = int(input())
        warunek_zadania = warunek(a_wejsc, b_wejsc)
        if warunek_zadania == False:
            print("Przedzial nie spelnia warunku f(a) * f(b) < 0. Prosze wprowadzic ponownie")
    wartosc_polowienia, krok_polowienia = metoda_polawiania(a_wejsc, b_wejsc, epsilon)
    wartosc_siecznych, krok_siecznych = metoda_siecznych(a_wejsc, b_wejsc, epsilon)
    print("Przyblizenie miejsca zerowego")
    print("")
    print("Metoda polowienia:")
    print(f"Liczba krokow:{krok_polowienia}, znaleziona_wartosc:{wartosc_polowienia}")
    print()
    print("Metoda siecznych:")
    print(f"Liczba krokow:{krok_siecznych}, znaleziona_wartosc:{wartosc_siecznych}")