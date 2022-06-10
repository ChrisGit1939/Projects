import requests
import json

while True:
    print('')
    print('Press CTRL + C to EXIT')
    print('')
    location = input('Write location: ')
    location_displayed = location     # location_displayed value is display on screen
    location = location.casefold()       #remove diacritics, spaces, and capital letters
    location = location.replace(' ', '')
    location = location.replace('ą', 'a')
    location = location.replace('ć', 'c')
    location = location.replace('ę', 'e')
    location = location.replace('ł', 'l')
    location = location.replace('ó', 'o')
    location = location.replace('ś', 's')
    location = location.replace('ź', 'z')
    location = location.replace('ż', 'z')

    link = 'https://danepubliczne.imgw.pl/api/data/synop/station/{}'.format(location)
    downloaded = requests.get(link)
    API = (downloaded.text)       # varriable  is contains needed API data
    data = json.loads(API)



    status = downloaded.status_code

    if status == 200:


        try:       # error control data of TEMPERATURE
            temperature_value = float(data['temperatura'])      # checking measurement value is float type
            temperature_value = str(temperature_value)

        except TypeError:
            temperature_value = ' -- '

        try:          # error control data of WIND SPEED
            wind_speed = float(data['predkosc_wiatru'])    # checking measurement value is float type
            wind_speed = str(wind_speed)

        except TypeError:
            wind_speed = ' -- ' 

        try:          # error control data of WIND DIRECTION
            wind_direction = float(data['kierunek_wiatru'])    # checking measurement value is float type
            wind_direction = str(wind_direction)

        except TypeError:
            wind_direction = ' -- ' 

        try:          # error control data of HUMIDITY
            humidity_value = float(data['wilgotnosc_wzgledna'])    # checking measurement value is float type
            if humidity_value > 50.0:
                weather = 'Cloudy'
            else:
                weather = 'Clear Sky'
            humidity_value = str(humidity_value)

        except TypeError:
            humidity_value = str(humidity_value)
            weather = 'Error Data'

        try:        # error control data of PRECIPITATION
            precipitation_value = float(data['suma_opadu'])   # checking measurement value is float type
            if precipitation_value > 0.1:
                weather = 'Rainy'
            precipitation_value = str(precipitation_value)

        except TypeError:
            precipitation_value = ' -- '
            weather = 'Error Data'
            


        try:       # error control data of PRESSURE
            pressure_value = float(data['cisnienie'])    # checking measurement value is float type
            pressure_value = str(pressure_value)
        except TypeError:
            pressure_value = ' -- '
        
        print(' ________________________________________')
        print('|')
        print('| Downloaded data from IMGW Poland')
        print('|')
        print('| Location: ' + data['stacja'])
        print('| Weather: ' + weather)
        print('| Temperature: ' + temperature_value + '°C' )
        print('| Wind: ' + wind_speed + 'm/s, ' + '  direction: ' + wind_direction + '°')
        print('| Humidity: ' + humidity_value + '%')
        print('| Precipitation total: ' + precipitation_value + 'mm')
        print('| Atmospheric pressure: ' + pressure_value + 'hPa')
        print('| Date of measurement: '+ data['data_pomiaru'] + ' ' + data['godzina_pomiaru'] + ':00')
        print('|________________________________________')

    if status == 404:
        print('')
        print('Location not recognized.')
        print('')
        
        link_2 = 'https://danepubliczne.imgw.pl/api/data/synop'
        downloaded_2 = requests.get(link_2)
    
        status_2 = downloaded_2.status_code
        if status_2 == 405: 
            print('ERROR CONNECT')
            
            
            
    
        if status_2 == 200:
            API_2 = (downloaded_2.text)
            data_2 = json.loads(API_2)
            print('Available locations: {}'.format(len(data_2)))
            print('')
            
            for xx in data_2:
                print(xx['stacja'])
    
