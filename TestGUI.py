import PySimpleGUI as sg
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(4, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(5, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(6, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(12, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(13, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(16, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(17, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(18, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(19, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(20, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(21, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(22, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(23, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(24, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(25, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(26, GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(27, GPIO.OUT,initial=GPIO.LOW)

sg.theme('BlueMono')

# ----------- Create the 3 layouts this Window will display -----------
layout1 = [[sg.Text('WELCOME TO MY GREATEST INVENTION',size=(50,1),font=("Verdana",26))],
        [sg.Button('START',key='-START-',size=(50,4)),  sg.Button('PAUSE',key='-PAUSE-', size=(50,4))],
        [sg.Button('RESET',key='-RESET-',size=(50,4)),  sg.Button('RELOAD',key='-RELOAD-', size=(50,4))],
        [sg.Button('MANUAL MODE',key='-MANU-',size=(110,4))],[sg.Button('CLOSE',key='-CLOSE-',size=(110,4))]]


layout2 = [[sg.RealtimeButton('RAISE FRONT',key='-RAISE1-',size=(50,4)),sg.RealtimeButton('LOWER FRONT',key='-LOWER1-',size=(50,4))],
        [sg.RealtimeButton('RAISE BACK',key='-RAISE2-',size=(50,4)),sg.RealtimeButton('LOWER BACK',key='-LOWER2-',size=(50,4))],
        [sg.RealtimeButton('LIFT SAMPLES',key='-RAISE3-',size=(50,4)),sg.RealtimeButton('LOWER SAMPLES',key='-LOWER3-',size=(50,4))],
        [sg.RealtimeButton('PLATFORM FORWARD',key='-FORWARD1-',size=(50,4)),  sg.RealtimeButton('PLATFORM BACK',key= '-BACK1-',size=(50,4))],
        [sg.Button('BACK',key='-BACK-',size=(110,4))]]


# ----------- Create actual layout using Columns and a row of Buttons
layout = [[sg.Column(layout1, key='-COL1-'), sg.Column(layout2, visible=False, key='-COL2-')]]

window = sg.Window('Swapping the contents of a window', layout, size=(800,480), element_justification="center",finalize=True)
window.Maximize()
layout = 1  # The currently visible layout
while True:
    event, values = window.read()
    print(event, values)
    if event in (None, '-CLOSE-'):
        GPIO.output(4,GPIO.LOW)
        GPIO.output(5,GPIO.LOW)
        GPIO.output(6,GPIO.LOW)
        break
    if event == '-BACK-':
        manualMode = False
        window[f'-COL{layout}-'].update(visible=False)
        layout = 1
        window[f'-COL{layout}-'].update(visible=True)
        GPIO.output(12,GPIO.LOW)
    elif event == '-MANU-':
        GPIO.output(4,GPIO.LOW)
        GPIO.output(12,GPIO.HIGH)
        manualMode = True
        window[f'-COL{layout}-'].update(visible=False)
        layout = 2
        window[f'-COL{layout}-'].update(visible=True)
    if event =='-START-':
        GPIO.output(24,GPIO.HIGH)
    elif event =='-PAUSE-':
        GPIO.output(24,GPIO.LOW)
    elif event =='-RESET-':
        GPIO.output(25,GPIO.HIGH)
        time.sleep(.1)
        GPIO.output(5,GPIO.LOW)
    elif event =='-RELOAD-':
        GPIO.output(26,GPIO.HIGH)
        time.sleep(.1)
        GPIO.output(26,GPIO.LOW)
    elif manualMode==True and event =='-RAISE1-':
        GPIO.output(13,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(13,GPIO.LOW)
    elif manualMode==True and event =='-RAISE2-':
        GPIO.output(16,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(16,GPIO.LOW)
    elif manualMode==True and event =='-RAISE3-':
        GPIO.output(17,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(17,GPIO.LOW)
    elif manualMode==True and event =='-LOWER1-':
        GPIO.output(18,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(18,GPIO.LOW)
    elif manualMode==True and event =='-LOWER2-':
        GPIO.output(19,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(19,GPIO.LOW)
    elif manualMode==True and event =='-LOWER3-':
        GPIO.output(20,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(20,GPIO.LOW)
    elif manualMode==True and event =='-FORWARD1-':
        GPIO.output(21,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(21,GPIO.LOW)
    elif manualMode==True and event =='-BACK1-':
        GPIO.output(22,GPIO.HIGH)
        time.sleep(.25)
        GPIO.output(22,GPIO.LOW)
window.close()