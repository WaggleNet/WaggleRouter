import png
from pathlib import Path


def convert_line(all_bytes):
    result = []
    counter = 0
    buffer = 0
    for b in all_bytes:
        if counter == 8:
            result.append(buffer)
            counter = 0
            buffer = 0
        buffer *= 2
        if b:
            buffer += 1
        counter += 1
    if counter:
        buffer *= (2**(8-counter))
        result.append(buffer)
    return result


def convert_image(path):
    f = open(path, 'rb')
    r = png.Reader(f)
    width, height, rows, _ = r.read()
    result = []
    for row in rows:
        result.extend(convert_line(row))
    name = 'UI_'+Path(path).name.split('.')[0].upper()
    s = 'const uint8_t %s [] PROGMEM = {%s};\n' % (
        name, ', '.join(map(str, result))
    )
    print('Exported: %s' % name)
    return s, name


hdata = ['#pragma once\n', '#include <Arduino.h>\n', '\n']
cdata = ['#include "lcd_ui.h"', '\n']
for i in Path('.').glob('*.png'):
    s, name = convert_image(i)
    cdata.append(s)
    hdata.append('extern const uint8_t {} [];\n'.format(name))

with open('../src/lcd_ui.h', 'w') as fp:
    fp.writelines(hdata)

with open('../src/lcd_ui.cpp', 'w') as fp:
    fp.writelines(cdata)
