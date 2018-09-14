import websocket
import json
from datetime import datetime

country_codes = dict()
country_codes["US"] = 0
country_codes["GB"] = 1
country_codes["CN"] = 2
country_codes["DE"] = 3
country_codes["RU"] = 4
country_codes["IE"] = 5
country_codes["FR"] = 6
country_codes["CA"] = 7
country_codes["ES"] = 8
country_codes["SK"] = 9
country_codes["NL"] = 10
country_codes["ZA"] = 11


def getUTCTimestamp():
    return datetime.utcnow()


def doDump():
    prevDate = getUTCTimestamp().date()
    f = open('fortinet_dump_' + str(prevDate) + '.csv', 'a')
    ws = websocket.create_connection("ws://threatmap.fortiguard.com/ws", subprotocols=["wamp.2.json"])

    msg1 = ('[1,"threatmap",{"roles":{"caller":{"features":{"caller_identification":true,"progressive_call_results"' +
            ':true}},"callee":{"features":{"caller_identification":true,"pattern_based_registration":true,"shared_registration"' +
            ':true,"progressive_call_results":true,"registration_revocation":true}},"publisher":{"features":{"publisher_identification"' +
            ':true,"subscriber_blackwhite_listing":true,"publisher_exclusion":true}},"subscriber":{"features":{"' +
            'publisher_identification":true,"pattern_based_subscription":true,"subscription_revocation":true}}}}]')

    msg2 = '[32,6361223091442090,{},"ips"]'

    ws.send(msg1)
    ws.send(msg2)

    count = 0
    try:
        while ws.connected:
            try:
                if count == 2:
                    dump = json.loads(ws.recv())[4][0]
                    timestamp = getUTCTimestamp()

                    # TODO str(dump['src']['countrycode']) if()

                    src = str(dump['src']['countrycode'])
                    dst = str(dump['dst']['countrycode'])

                    if src in country_codes.keys() and dst in country_codes.keys() and src!=dst:
                        data_string = (str(country_codes[src]) + " , " + str(country_codes[dst]))
                        if timestamp.date() > prevDate:
                            f.close()
                            f = open('fortinet_dump_' + str(timestamp.date()) + '.csv', 'a')
                            prevDate = timestamp.date()
                        f.write(data_string + "\n")
                        print(data_string)
                else:
                    ws.recv()

                if count < 2:
                    count += 1
            except Exception as e:
                print(e)
    finally:
        print('Closing file...')
        f.close()
        ws.close()


if __name__ == "__main__":
    while True:
        try:
            doDump()
        except Exception as e:
            print(e)
