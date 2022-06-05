from tkinter import Tk, Canvas, Label, PhotoImage, Button, Entry
import requests
import json



location = "Śnieżka"               # set the measurement location
location_displayed = location     # location_displayed value is display on screen
location = location.casefold()
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
API = (downloaded.text)       # varriable "a" is contains needed API data
API = str(API)
b = json.loads(API)
print(b)
print(type(b))
print(b['stacja'])

temperature = b['temperatura']
total_precipitation = b['suma_opadu']
wind_speed = b['predkosc_wiatru']
wind_direction = b['kierunek_wiatru']
pressure = b['cisnienie']
humidity = b['wilgotnosc_wzgledna']
date = b['data_pomiaru']
date += '   '
hour = b['godzina_pomiaru']
hour += ':00'

update_time = date + hour


main_window = Tk()
main_window.title('Weather Indicator')
main_window.geometry("=950x630")
main_window.overrideredirect(0)
main_window.tk_setPalette(background='white')


background = PhotoImage(file="rain_picture_10.png")
location_icon = PhotoImage(file="location_day_0.png")
sun_0 = PhotoImage(file="sun_0.png")
sun_1 = PhotoImage(file="sun_1.png")
rain_0 = PhotoImage(file="rain_1.png")
rain_1 = PhotoImage(file='rain_2.png')
cloud_0 = PhotoImage(file="cloud.png")
thermometer_icon = PhotoImage(file="thermometer.png")
wind_icon = PhotoImage(file="wind_icon.png")
wind_direction_icon = PhotoImage(file="wind_direction_icon.png")
humidity_icon = PhotoImage(file="humidity_icon.png")
pressure_icon = PhotoImage(file="pressure_icon.png")
total_precipitation_icon = PhotoImage(file="precipitation_icon.png")
#update = PhotoImage(file="update.png")

my_canvas = Canvas(main_window, width=950, height=630)
my_canvas.pack(fill="both", expand=True)
my_canvas.create_image(950, 630, image= background, anchor="se")

my_canvas.create_image(400, 3, image= location_icon, anchor="nw")
my_canvas.create_text(450, 10, text=location_displayed, font=("Helvetica",30), fill="#000000", anchor="nw")

my_canvas.create_image(5, 5, image= rain_0, anchor="nw")    # weather icon

my_canvas.create_image(5, 180, image= thermometer_icon, anchor="nw")
my_canvas.create_text(35, 190, text="{}°C".format(temperature), font=("Helvetica", 25), fill="#000000", anchor="nw")

my_canvas.create_image(5, 250, image= wind_icon, anchor='nw')
my_canvas.create_text(40, 254, text="{}m/s".format(wind_speed), font=("Helvetica",20), fill="#000000", anchor="nw")

my_canvas.create_image(5, 300, image= wind_direction_icon, anchor='nw')
my_canvas.create_text(30, 305, text="{}°".format(wind_direction), font=("Helvetica",20), fill="#000000", anchor="nw")

my_canvas.create_image(5, 350, image= humidity_icon, anchor='nw')
my_canvas.create_text(40, 355, text=" {}%".format(humidity), font=("Helvetica",20), fill="#000000", anchor="nw")

my_canvas.create_image(5, 400, image= pressure_icon, anchor='nw')
my_canvas.create_text(35, 404, text="{} hPa".format(pressure), font=("Helvetica",18), fill="#000000", anchor="nw")

my_canvas.create_image(5, 450, image= total_precipitation_icon, anchor='nw')
my_canvas.create_text(30, 454, text="{}mm".format(total_precipitation), font=("Helvetica",20), fill="#000000", anchor="nw")

my_canvas.create_text(10, 500, text="Weather data: IMGW Poland.", font=("Helvetica",8), fill="#000000", anchor="nw")
my_canvas.create_text(10, 520, text="Update at: {}".format(update_time), font=("Helvetica",8), fill="#000000", anchor="nw")





search_entry = Entry(main_window, background='white', width='17')                                      # ENTRY
search_entry.place(x=5, y=580)

def download_data():
    a = search_entry.get()
    print(a)
    link = 'https://danepubliczne.imgw.pl/api/data/synop/station/{}'.format(a)
    downloaded = requests.get(link)
    print(downloaded)

search_button = Button(main_window, background='white', borderwidth=1, text=' Search  location ', command=download_data)     # button SEARCH
search_button.place(x=5, y=550)





#img_label = Label(image=update)
#img_label.pack(pady=20)

#update_button = Button(main_window, image=update, borderwidth=0)
#update_button.pack(pady=20)
#update_button_window = my_canvas.create_window(10, 800, anchor="nw", window=img_label )




#button_1 = Button(main_window, text='AKTUALNIE:')



#button_1_window = my_canvas.create_window(3, 3, anchor="nw", window=button_1)




# my_label = Label(main_window, image=background)
# my_label.place(x=0, y=0, relwidth=1, relheight=1)


#image = Canvas(main_window, bg="blue", height=50, width=50)

#image.pack()
main_window.mainloop()