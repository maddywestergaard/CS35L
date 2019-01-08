#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, filename, userinput, lis):
        if lis:
            self.lines = lis
        elif userinput:
            self.lines = userinput
        else:
            f = open(filename,'r')
            self.lines = f.readlines()
            f.close()
   
    def chooseline(self, lis):
        if lis:
            return random.choice(lis)
        else:
            return random.choice(self.lines)
    
def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION].. FILE

Shuffle lines of input."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-i", "--input-range",
                      action="store", dest="input_range",
                      help="Act as if input came from a file containing the range of unsigned decimal integers lo...hi, one per line")
    
    parser.add_option("-n", "--head-count",
                      action="store", dest="count", 
                      help="output at most count lines. default: all input lines are output")

    parser.add_option("-r", "--repeat", 
                      action="store_true", dest="repeat", default=False,
                      help="repeat output values, each line is randomly chosen from all inputs. This option is typically combined with --head-count; if --head-count is not given, shuf repeats indefinitely")

    options, args = parser.parse_args(sys.argv[1:])
    
    repeat = bool(options.repeat)

    listnums = []
    if options.input_range:
        a,b = options.input_range.split("-")
        j = int(a)
        while j is not int(b)+1:
            listnums.append(j)
            j+=1
    inputfile=[]
    try:
        input_file = args[0]
        if input_file is "-":
            raise error
    except:
        input_file=None
        s = raw_input()
        while s:
            inputfile.append(s)
            s = raw_input()
    
    if options.count:
        count = int(options.count)
        if count < 0:
            parser.error("negative count: {0}".
                         format(count))
        else:
            if inputfile:
                if count > len(inputfile):
                    count = len(inputfile)
            else:
                if count > len(open(input_file).readlines()):
                    count = len(open(input_file).readlines())
    else:
        count = -1;

    try:
        generator = shuf(input_file,inputfile, listnums)
        
        if repeat:
            i = 0;
            while i is not count:
                sys.stdout.write(str(generator.chooseline(listnums)))
                if listnums or inputfile:
                    sys.stdout.write("\n")
                    i+=1
        else:
            if not options.count:
                if listnums:
                    count = len(listnums)
                elif inputfile:
                    count = len(inputfile)
                else:
                    count=len(open(input_file).readlines())
            newlist = []
            for index in range(count):
                s = str(generator.chooseline(listnums))
                while s in newlist:
                    s = str(generator.chooseline(listnums))
                sys.stdout.write(s)
                if listnums or inputfile:
                    sys.stdout.write("\n")
                newlist.append(s)
    
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
    
    print

if __name__ == "__main__":
    main()



