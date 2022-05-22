from tkinter import Tk, Label, Entry, Button   # importuje biblioteke tkinter


glowne_okno = Tk()                              # glowne okno
glowne_okno.title('Oblicz zysk ze sprzedaży!')  # tytuł
glowne_okno.geometry('800x400')                # rozmiar okna


# rozmieszczenie elementów w glownym oknie programu



puste_miejsce_0 = Label(glowne_okno, text=' ')           # pierwsza kolumna nazwa wartości
puste_miejsce_0.grid(column=1, row=0)
zakup = Label(glowne_okno, text='Cena NETTO zakupionego towaru:', font = ("Times New Roman", 11), justify= 'left')
zakup.grid(column=1, row=1)
puste_miejsce_1 = Label(glowne_okno, text='  ')
puste_miejsce_1.grid(column=1, row=2)
vat = Label(glowne_okno, text='Stawka VAT:', font = ("Times New Roman", 11), justify= 'left')
vat.grid(column=1, row=3)
puste_miejsce_2 = Label(glowne_okno, text='  ')
puste_miejsce_2.grid(column=1, row=4)
minimalna_prowizja = Label(glowne_okno, text='Minimalna kwota prowizji od sprzedaży:', font = ("Times New Roman", 11), justify= 'left')
minimalna_prowizja.grid(column=1, row=5)
puste_miejsce_3 = Label(glowne_okno, text='  ')
puste_miejsce_3.grid(column=1, row=6)
prowizja = Label(glowne_okno, text='Prowizja od sprzedaży:', font = ("Times New Roman", 11), justify= 'left')
prowizja.grid(column=1, row=7)
puste_miejsce_4 = Label(glowne_okno, text='  ')
puste_miejsce_4.grid(column=1, row=8)
sprzedaz = Label(glowne_okno, text='Kwota sprzedaży BRUTTO:', font = ("Times New Roman", 11), justify= 'left')
sprzedaz.grid(column=1, row=9)
puste_miejsce_5 = Label(glowne_okno, text='  ')
puste_miejsce_5.grid(column=1, row=10)
podatek_dochod = Label(glowne_okno, text='Podatek od dochodu:', font = ("Times New Roman", 11), justify= 'left')
podatek_dochod.grid(column=1, row=11)

puste_miejsce_29 = Label(glowne_okno, text='')
puste_miejsce_29.grid(column=1, row=12)



puste_miejsce_6 = Label(glowne_okno, text='   ')   # druga kolumna wpisywanie wartości
puste_miejsce_6.grid(column=2, row=0)
wartosc_towaru_netto = Entry(glowne_okno, width=10,  font = ("Times New Roman", 11))
wartosc_towaru_netto.grid(column=2, row=1)
puste_miejsce_7 = Label(glowne_okno, text='   ')
puste_miejsce_7.grid(column=2, row=2)
wartosc_vat = Entry(glowne_okno, textvariable='0', width=10, font = ("Times New Roman", 11))
wartosc_vat.grid(column=2, row=3)
puste_miejsce_8 = Label(glowne_okno, text='   ')
puste_miejsce_8.grid(column=2, row=4)
wartosc_prowizji_minimalnej = Entry(glowne_okno, width=10, font = ("Times New Roman", 11))
wartosc_prowizji_minimalnej.grid(column=2, row=5)
puste_miejsce_9 = Label(glowne_okno, text='   ')
puste_miejsce_9.grid(column=2, row=6)
wartosc_prowizji = Entry(glowne_okno, width=10, font = ("Times New Roman", 11))
wartosc_prowizji.grid(column=2, row=7)
puste_miejsce_10 = Label(glowne_okno, text='   ')
puste_miejsce_10.grid(column=2, row=8)
wartosc_sprzedaz_brutto = Entry(glowne_okno, width=10, font = ("Times New Roman", 11))
wartosc_sprzedaz_brutto.grid(column=2, row=9)
puste_miejsce_11 = Label(glowne_okno, text='   ')
puste_miejsce_11.grid(column=2, row=10)
wartosc_podatku = Entry(glowne_okno, width=10, font = ("Times New Roman", 11))
wartosc_podatku.grid(column=2, row=11)
puste_miejsce_12 = Label(glowne_okno, text='   ')
puste_miejsce_12.grid(column=2, row=12)

puste_miejsce_13 = Label(glowne_okno, text= '  ')             # trzecia kolumna jednostki 
puste_miejsce_13.grid(column=3, row=0)
jednostka_miejsce_14 = Label(glowne_okno, text= 'zł', font = ("Times New Roman", 11))
jednostka_miejsce_14.grid(column=3, row=1)
puste_miejsce_15 = Label(glowne_okno, text= '  ')
puste_miejsce_15.grid(column=3, row=2)
jednostka_miejsce_16 = Label(glowne_okno, text= '%', font = ("Times New Roman", 11))
jednostka_miejsce_16.grid(column=3, row=3)
puste_miejsce_17 = Label(glowne_okno, text= '  ')
puste_miejsce_17.grid(column=3, row=4)
jednostka_miejsce_18 = Label(glowne_okno, text= 'zł', font = ("Times New Roman", 11))
jednostka_miejsce_18.grid(column=3, row=5)
puste_miejsce_19 = Label(glowne_okno, text= '  ')
puste_miejsce_19.grid(column=3, row=6)
jednostka_miejsce_20 = Label(glowne_okno, text= '%', font = ("Times New Roman", 11))
jednostka_miejsce_20.grid(column=3, row=7)   
puste_miejsce_21 = Label(glowne_okno, text= '  ')
puste_miejsce_21.grid(column=3, row=8)
jednostka_miejsce_22 = Label(glowne_okno, text= 'zł', font = ("Times New Roman", 11))
jednostka_miejsce_22.grid(column=3, row=9)
puste_miejsce_23 = Label(glowne_okno, text= '  ')
puste_miejsce_23.grid(column=3, row=10)
jednostka_miejsce_24 = Label(glowne_okno, text= '%', font = ("Times New Roman", 11))
jednostka_miejsce_24.grid(column=3, row=11)
    
 #*************************  

# funkcja jaka zostanie wywołana w momencie kliknięcia przyciku 'oblicz'
def oblicz():

    for x in range(0, 11):                # wyczyszczenie napisów po prawej stronie okna aby wprowadzić nowe dane napisy
            odstep_0 = Label(glowne_okno, text= '                                                                                           ')
            odstep_0.grid(column=4, row=x)

    
    a = wartosc_towaru_netto.get()     
    a = a.replace(',', '.')                # przecinki w liczbach z ułamkiem dziesiętnym będą zamieniane na kropki

    b = wartosc_vat.get()
    b = b.replace(',', '.')

    c = wartosc_sprzedaz_brutto.get()
    c = c.replace(',', '.')

    d = wartosc_prowizji_minimalnej.get()
    d = d.replace(',', '.')

    e = wartosc_prowizji.get()
    e = e.replace(',', '.')

    f = wartosc_podatku.get()
    f = f.replace(',', '.')

    try:                     # kontrola błędu. Wartości to mają być liczby i kropki, przecinki bez liter czy innych znaków
        a = float(a)
        b = float(b)
        c = float(c)
        d = float(d)
        e = float(e)
        f = float(f)
    except ValueError:
        odstep = Label(glowne_okno, text= '')     # pierwsza linia od góry jest pusta (estetyka)
        odstep.grid(column=1, row=13)
        komunikat_bledu_1 = Label(glowne_okno, text=' Uzupełnij wszystkie pola.  ')
        komunikat_bledu_1.grid(column=1, row=14)
        komunikat_bledu_2 = Label(glowne_okno, text=' Dane muszą zawierać wyłącznie liczby.')
        komunikat_bledu_2.grid(column=1, row=15)
        komunikat_bledu_2 = Label(glowne_okno, text=' Części dziesiętne oddziel ".", lub ",".')
        komunikat_bledu_2.grid(column=1, row=16)

        
        
    
        

        for x in range(3, 11):                # reszta lini pod spodem ma być pusta
            odstep_1 = Label(glowne_okno, text= '                                                                                               ')
            odstep_1.grid(column=4, row=x)



    wartosc_towaru_z_vat = 1 + b / 100
    wartosc_towaru_z_vat = a  # ustalenie wartości towaru brutto

    wartosc_towaru_sprzedana = c        # ustalenie wartości towaru sprzedanego

    podatek_vat = 1 + b / 100
    podatek_vat = wartosc_towaru_sprzedana - (wartosc_towaru_sprzedana / podatek_vat)
    podatek_vat = round(podatek_vat, 2) # zaokrąglanie do 2 miejsc po przecinku

    prowizja_minimalna = d           # ustalenie minimalnej prowizji
    
    prowizja_procentowa = e / 100
    prowizja_procentowa *= wartosc_towaru_sprzedana

    if prowizja_procentowa > prowizja_minimalna:    # warunek ustalający prowizję od sprzedaży
        prowizja_finalna = prowizja_procentowa
    else:
        prowizja_finalna = prowizja_minimalna

    prowizja_finalna_netto = prowizja_finalna / (1 + b / 100)

    prowizja_finalna_netto = round(prowizja_finalna_netto, 2)

    wartosc_towaru_sprzedana -= prowizja_finalna

    kwota_zysku_brutto = wartosc_towaru_sprzedana - wartosc_towaru_z_vat
    kwota_zysku_netto = kwota_zysku_brutto / (1 + b / 100)

    podatek_dochodowy = kwota_zysku_netto * (f / 100)
    podatek_dochodowy = round(podatek_dochodowy, 2)
    

    wynik = kwota_zysku_netto - podatek_dochodowy
    wynik = round(wynik, 2)
    
    

    zysk = Label(glowne_okno, text='   Dochód NETTO: {} zł.'.format(wynik), font = ("Times New Roman", 12))
    zysk.grid(column=4, row=1)

    puste_miejsce_25 = Label(glowne_okno, text='        ')
    puste_miejsce_25.grid(column=4, row=2)
    puste_miejsce_26 = Label(glowne_okno, text='        ')
    puste_miejsce_26.grid(column=4, row=3)

    koszty = Label(glowne_okno, text='Kwoty zawarte w cenie sprzedaży {} zł:'.format(c), font = ("Times New Roman", 11))
    koszty.grid(column=4, row=4)

    puste_miejsce_27 = Label(glowne_okno, text='       ')
    puste_miejsce_27.grid(column=4, row=5)

    cena_netto_towaru = Label(glowne_okno, text='Cena netto towaru: {} zł'.format(a), font = ("Times New Roman", 11))
    cena_netto_towaru.grid(column=4, row=6)

    kwota_vat = Label(glowne_okno, text='Podatek VAT: {} zł'.format(podatek_vat), font = ("Times New Roman", 11))
    kwota_vat.grid(column=4, row=7)

    kwota_podatku_dochodowego = Label(glowne_okno, text='Podatek dochodowy: {} zł'.format(podatek_dochodowy), font = ("Times New Roman", 11))
    kwota_podatku_dochodowego.grid(column=4, row=8)

    kwota_prowizji = Label(glowne_okno, text='Koszt sprzedaży netto: {} zł'.format(prowizja_finalna_netto), font = ("Times New Roman", 11))
    kwota_prowizji.grid(column=4, row=9)

    realny_zysk = Label(glowne_okno, text='Dochód: {} zł'.format(wynik), font = ("Times New Roman", 11))
    realny_zysk.grid(column=4, row=10)

#  ******** koniec funkcji obliczającej ********


oblicz = Button(glowne_okno, text='Oblicz!', font = ("Times New Roman", 14), command=oblicz)  # parametry przycisku 'oblicz'
oblicz.grid(column=2, row=13)







glowne_okno.mainloop()
