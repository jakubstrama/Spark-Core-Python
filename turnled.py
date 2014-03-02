#!/usr/bin/python

import sys, requests


token = "YOUR-ACCESS-TOKEN"
deviceNumber = "DEVICE-ID"
auth = {'Authorization': 'Bearer ' + token}
coreUrl = "https://api.spark.io/v1/devices/" + deviceNumber + "/"
colors = ["red", "blue", "green", "yellow", "white", "all"]
states = ["on", "off"]


def turnLED(state, color):
    function = "blink"
    params = state + "," + color
    data = {'args': params}
    devInfo = requests.post(coreUrl + function, headers=auth, data=data).json()

    if devInfo["return_value"] == 200:
        print "LED %s turned %s" % (color, state)


def turnAll(state):
    function = ""
    if state == "off":
        function = "allOff"
    elif state == "on":
        function = "allOn"

    devInfo = requests.post(coreUrl + function, headers=auth).json()

    if devInfo["return_value"] == 200:
        print "All LEDs turned %s!" % state


def main():
    if len(sys.argv) < 2:
        print "This Program takes exactly 2 parameters\n 'color' and 'state' \n exactly in this order, eg. 'python turnled.py red on'"
        return

    color = str(sys.argv[1]).lower()
    state = str(sys.argv[2]).lower()

    if state not in states:
        print "State '%s' is not allowed, allowed states: " % state
        for state in states:
            print state
        return
    elif color not in colors:
        print "LED color '%s' is not allowed, allowed colors:" % color
        for color in colors:
            print color
        return

    if color == "all":
        turnAll(state)
        return

    turnLED(state, color)


if __name__ == '__main__': main()




