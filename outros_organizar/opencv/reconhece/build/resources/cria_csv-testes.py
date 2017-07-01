#!/usr/bin/env python

import sys
import os.path
import io

# This is a tiny script to help you creating a CSV file from a face
# database with a similar hierarchie:
#
#  philipp@mango:~/facerec/data/at$ tree
#  .
#  |-- README
#  |-- s1
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  |-- s2
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  ...
#  |-- s40
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print "usage: create_csv <base_path>"
        sys.exit(1)
def t():
    BASE_PATH= "fotos"
    SEPARATOR=";"
    label = 0
    data = []
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            print (subdirname)
            subject_path = os.path.join(dirname, subdirname)
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s" % (subject_path, filename)

                data.append([abs_path, SEPARATOR, str(label), '\n'])
                label = label + 1
    with open('resources/fotos.csv', 'w') as f:
        for d in data:
            f.write(''.join(d))
    f.close()
